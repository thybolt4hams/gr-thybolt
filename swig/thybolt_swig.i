/* -*- c++ -*- */

#define THYBOLT_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "thybolt_swig_doc.i"

%{
#include "thybolt/preamble_detector_bp.h"
%}

%include "thybolt/preamble_detector_bp.h"
GR_SWIG_BLOCK_MAGIC2(thybolt, preamble_detector_bp);
