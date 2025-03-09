// asr-onnx/csrc/offline-model-config.cc
//
// Copyright (c)  2023  Xiaomi Corporation
#include "asr-onnx/csrc/offline-model-config.h"

#include <string>

#include "asr-onnx/csrc/file-utils.h"
#include "asr-onnx/csrc/macros.h"

namespace sherpa_onnx {

void OfflineModelConfig::Register(ParseOptions *po) {

}

bool OfflineModelConfig::Validate() const {
  if (num_threads < 1) {
    SHERPA_ONNX_LOGE("num_threads should be > 0. Given %d", num_threads);
    return false;
  }

  if (!FileExists(tokens)) {
    SHERPA_ONNX_LOGE("tokens: '%s' does not exist", tokens.c_str());
    return false;
  }

  if (!paraformer.model.empty()) {
    return paraformer.Validate();
  }

  if (!nemo_ctc.model.empty()) {
    return nemo_ctc.Validate();
  }

  if (!whisper.encoder.empty()) {
    return whisper.Validate();
  }

  if (!fire_red_asr.encoder.empty()) {
    return fire_red_asr.Validate();
  }

  if (!tdnn.model.empty()) {
    return tdnn.Validate();
  }

  if (!zipformer_ctc.model.empty()) {
    return zipformer_ctc.Validate();
  }

  if (!wenet_ctc.model.empty()) {
    return wenet_ctc.Validate();
  }

  if (!sense_voice.model.empty()) {
    return sense_voice.Validate();
  }

  if (!moonshine.preprocessor.empty()) {
    return moonshine.Validate();
  }

  if (!telespeech_ctc.empty() && !FileExists(telespeech_ctc)) {
    SHERPA_ONNX_LOGE("telespeech_ctc: '%s' does not exist",
                     telespeech_ctc.c_str());
    return false;
  }

  if (!transducer.encoder_filename.empty()) {
    return transducer.Validate();
  }

  return true;
}

std::string OfflineModelConfig::ToString() const {
  std::ostringstream os;

  os << "OfflineModelConfig(";
  os << "transducer=" << transducer.ToString() << ", ";
  os << "paraformer=" << paraformer.ToString() << ", ";
  os << "nemo_ctc=" << nemo_ctc.ToString() << ", ";
  os << "whisper=" << whisper.ToString() << ", ";
  os << "fire_red_asr=" << fire_red_asr.ToString() << ", ";
  os << "tdnn=" << tdnn.ToString() << ", ";
  os << "zipformer_ctc=" << zipformer_ctc.ToString() << ", ";
  os << "wenet_ctc=" << wenet_ctc.ToString() << ", ";
  os << "sense_voice=" << sense_voice.ToString() << ", ";
  os << "moonshine=" << moonshine.ToString() << ", ";
  os << "telespeech_ctc=\"" << telespeech_ctc << "\", ";
  os << "tokens=\"" << tokens << "\", ";
  os << "num_threads=" << num_threads << ", ";
  os << "debug=" << (debug ? "True" : "False") << ", ";
  os << "provider=\"" << provider << "\", ";
  os << "model_type=\"" << model_type << "\", ";
  os << "modeling_unit=\"" << modeling_unit << "\", ";
  os << "bpe_vocab=\"" << bpe_vocab << "\")";

  return os.str();
}

}  // namespace sherpa_onnx
