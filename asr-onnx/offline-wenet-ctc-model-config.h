// asr-onnx/offline-wenet-ctc-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_OFFLINE_WENET_CTC_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_OFFLINE_WENET_CTC_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OfflineWenetCtcModelConfig {
  std::string model;

  OfflineWenetCtcModelConfig() = default;
  explicit OfflineWenetCtcModelConfig(const std::string &model)
      : model(model) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_WENET_CTC_MODEL_CONFIG_H_
