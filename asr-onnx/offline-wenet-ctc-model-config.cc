// asr-onnx/offline-wenet-ctc-model-config.cc
//
 

#include "asr-onnx/offline-wenet-ctc-model-config.h"

#include "asr-onnx/file-utils.h"
#include "asr-onnx/macros.h"

namespace sherpa_onnx {

void OfflineWenetCtcModelConfig::Register(ParseOptions *po) {
  po->Register(
      "wenet-ctc-model", &model,
      "Path to model.onnx from WeNet. Please see "
      "https://github.com/k2-fsa/sherpa-onnx/pull/425 for available models");
}

bool OfflineWenetCtcModelConfig::Validate() const {
  if (!FileExists(model)) {
    SHERPA_ONNX_LOGE("WeNet model: '%s' does not exist", model.c_str());
    return false;
  }

  return true;
}

std::string OfflineWenetCtcModelConfig::ToString() const {
  std::ostringstream os;

  os << "OfflineWenetCtcModelConfig(";
  os << "model=\"" << model << "\")";

  return os.str();
}

}  // namespace sherpa_onnx
