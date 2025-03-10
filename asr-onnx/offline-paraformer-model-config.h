// asr-onnx/offline-paraformer-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_OFFLINE_PARAFORMER_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_OFFLINE_PARAFORMER_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OfflineParaformerModelConfig {
  std::string model;

  OfflineParaformerModelConfig() = default;
  explicit OfflineParaformerModelConfig(const std::string &model)
      : model(model) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_PARAFORMER_MODEL_CONFIG_H_
