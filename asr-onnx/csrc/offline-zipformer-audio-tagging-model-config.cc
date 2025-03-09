// asr-onnx/csrc/offline-zipformer-audio-tagging-model-config.cc
//
// Copyright (c)  2024  Xiaomi Corporation

#include "asr-onnx/csrc/offline-zipformer-audio-tagging-model-config.h"

#include "asr-onnx/csrc/file-utils.h"
#include "asr-onnx/csrc/macros.h"

namespace sherpa_onnx {

void OfflineZipformerAudioTaggingModelConfig::Register(ParseOptions *po) {
  po->Register("zipformer-model", &model,
               "Path to zipformer model for audio tagging");
}

bool OfflineZipformerAudioTaggingModelConfig::Validate() const {
  if (model.empty()) {
    SHERPA_ONNX_LOGE("Please provide --zipformer-model");
    return false;
  }

  if (!FileExists(model)) {
    SHERPA_ONNX_LOGE("--zipformer-model: '%s' does not exist", model.c_str());
    return false;
  }

  return true;
}

std::string OfflineZipformerAudioTaggingModelConfig::ToString() const {
  std::ostringstream os;

  os << "OfflineZipformerAudioTaggingModelConfig(";
  os << "model=\"" << model << "\")";

  return os.str();
}

}  // namespace sherpa_onnx
