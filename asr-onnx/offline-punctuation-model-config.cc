// asr-onnx/offline-punctuation-model-config.cc
//
 

#include "asr-onnx/offline-punctuation-model-config.h"

#include "asr-onnx/file-utils.h"
#include "asr-onnx/macros.h"

namespace sherpa_onnx {

void OfflinePunctuationModelConfig::Register(ParseOptions *po) {
  po->Register("ct-transformer", &ct_transformer,
               "Path to the controllable time-delay (CT) transformer model");

  po->Register("num-threads", &num_threads,
               "Number of threads to run the neural network");

  po->Register("debug", &debug,
               "true to print model information while loading it.");

  po->Register("provider", &provider,
               "Specify a provider to use: cpu, cuda, coreml");
}

bool OfflinePunctuationModelConfig::Validate() const {
  if (ct_transformer.empty()) {
    SHERPA_ONNX_LOGE("Please provide --ct-transformer");
    return false;
  }

  if (!FileExists(ct_transformer)) {
    SHERPA_ONNX_LOGE("--ct-transformer %s does not exist",
                     ct_transformer.c_str());
    return false;
  }

  return true;
}

std::string OfflinePunctuationModelConfig::ToString() const {
  std::ostringstream os;

  os << "OfflinePunctuationModelConfig(";
  os << "ct_transformer=\"" << ct_transformer << "\", ";
  os << "num_threads=" << num_threads << ", ";
  os << "debug=" << (debug ? "True" : "False") << ", ";
  os << "provider=\"" << provider << "\")";

  return os.str();
}

}  // namespace sherpa_onnx
