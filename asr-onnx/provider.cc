// asr-onnx/provider.cc
//
 

#include "asr-onnx/provider.h"

#include <algorithm>
#include <cctype>

#include "asr-onnx/macros.h"

namespace sherpa_onnx {

Provider StringToProvider(std::string s) {
  std::transform(s.cbegin(), s.cend(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  if (s == "cpu") {
    return Provider::kCPU;
  } else if (s == "cuda") {
    return Provider::kCUDA;
  } else if (s == "coreml") {
    return Provider::kCoreML;
  } else if (s == "xnnpack") {
    return Provider::kXnnpack;
  } else if (s == "nnapi") {
    return Provider::kNNAPI;
  } else if (s == "trt") {
    return Provider::kTRT;
  } else if (s == "directml") {
    return Provider::kDirectML;
  } else {
    SHERPA_ONNX_LOGE("Unsupported string: %s. Fallback to cpu", s.c_str());
    return Provider::kCPU;
  }
}

}  // namespace sherpa_onnx
