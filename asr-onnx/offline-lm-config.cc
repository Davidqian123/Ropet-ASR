// asr-onnx/offline-lm-config.cc
//
 

#include "asr-onnx/offline-lm-config.h"

#include <string>

#include "asr-onnx/file-utils.h"
#include "asr-onnx/macros.h"

namespace sherpa_onnx {

void OfflineLMConfig::Register(ParseOptions *po) {
  po->Register("lm", &model, "Path to LM model.");
  po->Register("lm-scale", &scale, "LM scale.");
  po->Register("lm-num-threads", &lm_num_threads,
               "Number of threads to run the neural network of LM model");
  po->Register("lm-provider", &lm_provider,
               "Specify a provider to LM model use: cpu, cuda, coreml");
}

bool OfflineLMConfig::Validate() const {
  if (!FileExists(model)) {
    SHERPA_ONNX_LOGE("'%s' does not exist", model.c_str());
    return false;
  }

  return true;
}

std::string OfflineLMConfig::ToString() const {
  std::ostringstream os;

  os << "OfflineLMConfig(";
  os << "model=\"" << model << "\", ";
  os << "scale=" << scale << ")";

  return os.str();
}

}  // namespace sherpa_onnx
