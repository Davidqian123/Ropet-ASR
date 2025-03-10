// asr-onnx/online-lm.cc
//
 
 

#include "asr-onnx/online-lm.h"

#include <algorithm>
#include <utility>
#include <vector>

#include "asr-onnx/online-rnn-lm.h"

namespace sherpa_onnx {

std::unique_ptr<OnlineLM> OnlineLM::Create(const OnlineLMConfig &config) {
  return std::make_unique<OnlineRnnLM>(config);
}

}  // namespace sherpa_onnx
