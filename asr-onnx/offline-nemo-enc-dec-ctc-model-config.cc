// asr-onnx/offline-nemo-enc-dec-ctc-model-config.cc
//
 

#include "asr-onnx/offline-nemo-enc-dec-ctc-model-config.h"

#include "asr-onnx/file-utils.h"
#include "asr-onnx/macros.h"

namespace sherpa_onnx {

void OfflineNemoEncDecCtcModelConfig::Register(ParseOptions *po) {
  po->Register("nemo-ctc-model", &model,
               "Path to model.onnx of Nemo EncDecCtcModel.");
}

bool OfflineNemoEncDecCtcModelConfig::Validate() const {
  if (!FileExists(model)) {
    SHERPA_ONNX_LOGE("NeMo model: '%s' does not exist", model.c_str());
    return false;
  }

  return true;
}

std::string OfflineNemoEncDecCtcModelConfig::ToString() const {
  std::ostringstream os;

  os << "OfflineNemoEncDecCtcModelConfig(";
  os << "model=\"" << model << "\")";

  return os.str();
}

}  // namespace sherpa_onnx
