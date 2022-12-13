/* -*- c++ -*- */
/*
 * Copyright 2022 gnuradio.org.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "preamble_detector_bp_impl.h"

namespace gr {
  namespace thybolt {

    preamble_detector_bp::sptr
    preamble_detector_bp::make(int pkt_len = 510)
    {
      return gnuradio::get_initial_sptr
        (new preamble_detector_bp_impl(pkt_len));
    }


    /*
     * The private constructor
     */
    preamble_detector_bp_impl::preamble_detector_bp_impl(int pkt_len)
      : gr::block("preamble_detector_bp",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(0, 0, 0)),
              d_pkt_len(pkt_len),
              d_port(pmt::mp("out"))
    {
      set_output_multiple((pkt_len+4)*80); // Sufficiently large buffer being processed at a time 
      message_port_register_out(d_port);
      d_bytectr = 0;
      d_bitctr = 0;
      d_pktbuf = new unsigned char[pkt_len]; // Buffer to store packet data after preamble
    }

    /*
     * Our virtual destructor.
     */
    preamble_detector_bp_impl::~preamble_detector_bp_impl()
    {
      delete[] d_pktbuf;
    }

    void
    preamble_detector_bp_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
      unsigned ninputs = ninput_items_required.size();
      for (unsigned i=0; i<ninputs; i++)
        ninput_items_required[i] = noutput_items;
    }

    int
    preamble_detector_bp_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char bit;
      int i,j,n=0;
      int rows, cols; 
      unsigned char shiftRegister[32];
      bool preambleDetected = 0;

      rows = d_pkt_len / 16;
      //printf("Rows: %d", rows);
      cols = d_pkt_len - 16*rows; 
      //printf("Excess cols: %d", cols);
      
      while (n < noutput_items) { // Process all inputs to the general_work block call
        bit = *in;

        // Fill up shift register - 112 byte shift register & keep scrolling
        for (i=1;i<32;i++){
          shiftRegister[i-1] = shiftRegister[i];
        }
        shiftRegister[31] = bit;

        // Generate start capture signal when preamble condition is met
        if (shiftRegister[0] == 0x00 && shiftRegister[1] == 0x01 && shiftRegister[2] == 0x00 && shiftRegister[3] == 0x01 &&       // P
            shiftRegister[4] == 0x00 && shiftRegister[5] == 0x00 && shiftRegister[6] == 0x00 && shiftRegister[7] == 0x00 && 
            shiftRegister[8] == 0x00 && shiftRegister[9] == 0x01 && shiftRegister[10] == 0x00 && shiftRegister[11] == 0x00 &&     // D
            shiftRegister[12] == 0x00 && shiftRegister[13] == 0x01 && shiftRegister[14] == 0x00 && shiftRegister[15] == 0x00 &&
            shiftRegister[16] == 0x00 && shiftRegister[17] == 0x01 && shiftRegister[18] == 0x00 && shiftRegister[19] == 0x00 &&   // O
            shiftRegister[20] == 0x01 && shiftRegister[21] == 0x01 && shiftRegister[22] == 0x01 && shiftRegister[23] == 0x01 &&
            shiftRegister[24] == 0x00 && shiftRegister[25] == 0x01 && shiftRegister[26] == 0x00 && shiftRegister[27] == 0x01 &&   // T
            shiftRegister[28] == 0x00 && shiftRegister[29] == 0x01 && shiftRegister[30] == 0x00 && shiftRegister[31] == 0x00){
              preambleDetected = 1;
              printf("Preamble detected\n");
              in++; // Shift input pointer by 2 bits synthetically as observed in data
              //in++;
              continue;

            }

        // Start capturing byte data
        if (preambleDetected)
        {
          // Read byte data - shift register implementation
          //printf("%d",bit);
          d_pktbuf[d_bytectr] <<= 1;
          if (bit)
              d_pktbuf[d_bytectr] |= 0x01;
          d_bitctr++;
          if (d_bitctr == 8) { // Byte boundary
              d_bitctr = 0;
              d_bytectr++;
              //printf("Bytecount: %ld\t Byte: %x\n",d_bytectr-1, d_pktbuf[d_bytectr-1]);
          }
          if (d_bytectr == d_pkt_len){ // Packet boundary
            //printf("Packet complete\n");
            d_bytectr = 0;
            preambleDetected = 0; // Reset preambleDetected signal
            //pmt::pmt_t pdu(pmt::cons(pmt::PMT_NIL, pmt::make_blob(d_pktbuf, d_pkt_len)));
            //message_port_pub(d_port, pdu);
            /*printf("===============================\n");
            printf("Packet data in 16 character table format\n");
            printf("===============================\n");
            for (i=0;i<rows;i++){
              for (j=0;j<16;j++)
                printf("%x ",d_pktbuf[i*16+j]);
              printf("\n");
            }
            for(i=0;i<cols;i++){
              printf("%x ", d_pktbuf[rows*16+i]);
            }
            printf("\n");
            printf("===============================\n");*/

            printf("===============================\n");
            printf("Packet data in continuous format\n");
            printf("===============================\n");
            for (i=0;i<d_pkt_len;i++){
              printf("%x",d_pktbuf[i]);
            }
            printf("\n");
            printf("===============================\n");
          }
        }

        // Proceed to processing next samples
				in++; 
				n++;
      }
			
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace thybolt */
} /* namespace gr */

