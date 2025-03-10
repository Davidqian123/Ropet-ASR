// asr-onnx/fst-utils.h
//
 

#ifndef SHERPA_ONNX_CSRC_FST_UTILS_H_
#define SHERPA_ONNX_CSRC_FST_UTILS_H_

#include <string>

#include "fst/fstlib.h"

namespace sherpa_onnx {

fst::Fst<fst::StdArc> *ReadGraph(const std::string &filename);

}

#endif  // SHERPA_ONNX_CSRC_FST_UTILS_H_
