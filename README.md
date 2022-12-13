# **gr-thybolt preamble detector**
## Introduction
The Telemetry from Thybolt satellites Thybolt-1 and Thybolt-2 are encoded in CCSDS frame format. Upon demodulating the  2-FSK signal at 4800 BaudRate, operators will be able to view the sync word ‘PDOT’ followed by the CCSDS frame. 

</br>

Telemetry packet is divided into two parts, Sync Word/Preamble and CCSDS frame
<table style="border-collapse:collapse;border-spacing:0" class="tg"><thead><tr><th style="border-color:inherit;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;font-weight:normal;overflow:hidden;padding:10px 5px;text-align:left;vertical-align:top;word-break:normal" colspan="2">PDOT Preamble Detector Block </th><th style="border-color:inherit;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;font-weight:normal;overflow:hidden;padding:10px 5px;text-align:left;vertical-align:top;word-break:normal" colspan="2">Online Decoder </th></tr></thead><tbody><tr><td style="border-color:inherit;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;overflow:hidden;padding:10px 5px;text-align:left;vertical-align:top;word-break:normal">Sync Word &lt;AAAAAAAAAAAAAAAA&gt;</td><td style="border-color:inherit;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;overflow:hidden;padding:10px 5px;text-align:left;vertical-align:top;word-break:normal">Preamble &lt;D42D50444F54&gt;</td><td style="border-color:inherit;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;overflow:hidden;padding:10px 5px;text-align:left;vertical-align:top;word-break:normal" colspan="2">CCSDS Frames 510 Bytes</td></tr></tbody></table>
<em>*Sync Word and Preamble are represented in Hex format</em>

</br>

Amateur Radio Operators can use below mentioned **gr-thybolt** block to extract ccsds packet and upload it in **online decoder software** mentioned below to view decoded telemetry packet



</br>

***

</br>

## gr-thybolt | PDOT preamble detector block
PDOT preamble detector block is developed so users can use GNU Radio 3.8.0 with any supported SDR to detect the syncword, preamble and automatically retreive the required encoded packet in Message Debug Block. 

The Encoded packet will further have to be uploaded in the online decoding tool to view Telemetry data.

Currently the block is developed and tested for [Ubuntu 18.04.6 LTS](https://releases.ubuntu.com/18.04/) and [GNU Radio 3.8.0](https://www.gnuradio.org/news/2019-08-10-gnu-radio-v3-8-0-0-release/) and will soon be available in GNU Radio versions 3.9 and 3.10

**Block Details :**

- Parent : gr-thybolt
- Name : PDOT preamble detector
- Input : Bytes 
- Output : PDU print
- Default Packet Length : 510 (Thybolts' satellite telemetry packet length)

</br>
 
![plot](https://github.com/thybolt4hams/gr-thybolt/assets/PDOT-Preamble-detector.png)

<em>The above image is available in assests folder</em>
</br>

**Instructions to install :**

- mkdir build
- cd build/
- cmake ../
- make
- sudo make install
- sudo ldconfig


</br>

***

</br>

## Online Decoder Software 

**Link** : [thyboltmission.web.app](thyboltmission.web.app)

<br/> 
After fetching 510 bytes in Message Debug Block, upload the plain hex data in the website's text-feild to see decoded telemetry data

<br/> 

Detailed instructions with example are available on website.

</br>

***

</br>

## CCSDS Packet Decoding Sequence 

Total Packet Size after demodulation : 522 Bytes 

**Header** : Sync Word(AAAAAAAAAAAAAAAA) + Preamble(D42D50444F54) -> 12 Bytes 

**CCSDS Frame** : Convoluted Coding(1/2,7) -> 255 Bytes <br/>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Reed-Solomon(255,223) -> 32 Bytes<br/>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Data Link Layer -> 8 Bytes<br/>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Space Packet Protocol -> 6 Bytes<br/>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Telemetry Data -> 186 to 209 Bytes

</br>

***

</br>













