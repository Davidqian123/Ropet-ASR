// asr-onnx/offline-fire-red-asr-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_OFFLINE_FIRE_RED_ASR_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_OFFLINE_FIRE_RED_ASR_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

// see https://github.com/FireRedTeam/FireRedASR
struct OfflineFireRedAsrModelConfig {
  std::string encoder;
  std::string decoder;

  OfflineFireRedAsrModelConfig() = default;
  OfflineFireRedAsrModelConfig(const std::string &encoder,
                               const std::string &decoder)
      : encoder(encoder), decoder(decoder) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_FIRE_RED_ASR_MODEL_CONFIG_H_
