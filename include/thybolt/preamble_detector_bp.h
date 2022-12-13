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

#ifndef INCLUDED_THYBOLT_PREAMBLE_DETECTOR_BP_H
#define INCLUDED_THYBOLT_PREAMBLE_DETECTOR_BP_H

#include <thybolt/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace thybolt {

    /*!
     * \brief <+description of block+>
     * \ingroup thybolt
     *
     */
    class THYBOLT_API preamble_detector_bp : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<preamble_detector_bp> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of thybolt::preamble_detector_bp.
       *
       * To avoid accidental use of raw pointers, thybolt::preamble_detector_bp's
       * constructor is in a private implementation
       * class. thybolt::preamble_detector_bp::make is the public interface for
       * creating new instances.
       */
      static sptr make(int pkt_len);
    };

  } // namespace thybolt
} // namespace gr

#endif /* INCLUDED_THYBOLT_PREAMBLE_DETECTOR_BP_H */

