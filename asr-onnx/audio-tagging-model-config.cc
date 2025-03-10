// asr-onnx/audio-tagging-model-config.cc
//
 

#include "asr-onnx/audio-tagging-model-config.h"
#include "asr-onnx/file-utils.h"
#include "asr-onnx/macros.h"

namespace sherpa_onnx {

void AudioTaggingModelConfig::Register(ParseOptions *po) {
  zipformer.Register(po);

  po->Register("ced-model", &ced,
               "Path to CED model. Only need to pass one of --zipformer-model "
               "or --ced-model");

  po->Register("num-threads", &num_threads,
               "Number of threads to run the neural network");

  po->Register("debug", &debug,
               "true to print model information while loading it.");

  po->Register("provider", &provider,
               "Specify a provider to use: cpu, cuda, coreml");
}

bool AudioTaggingModelConfig::Validate() const {
  if (!zipformer.model.empty() && !zipformer.Validate()) {
    return false;
  }

  if (!ced.empty() && !FileExists(ced)) {
    SHERPA_ONNX_LOGE("CED model file '%s' does not exist", ced.c_str());
    return false;
  }

  if (zipformer.model.empty() && ced.empty()) {
    SHERPA_ONNX_LOGE("Please provide either --zipformer-model or --ced-model");
    return false;
  }

  return true;
}

std::string AudioTaggingModelConfig::ToString() const {
  std::ostringstream os;

  os << "AudioTaggingModelConfig(";
  os << "zipformer=" << zipformer.ToString() << ", ";
  os << "ced=\"" << ced << "\", ";
  os << "num_threads=" << num_threads << ", ";
  os << "debug=" << (debug ? "True" : "False") << ", ";
  os << "provider=\"" << provider << "\")";

  return os.str();
}

}  // namespace sherpa_onnx
