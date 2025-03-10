// asr-onnx/csrc/online-nemo-ctc-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_ONLINE_NEMO_CTC_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_ONLINE_NEMO_CTC_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/csrc/parse-options.h"

namespace sherpa_onnx {

struct OnlineNeMoCtcModelConfig {
  std::string model;

  OnlineNeMoCtcModelConfig() = default;

  explicit OnlineNeMoCtcModelConfig(const std::string &model) : model(model) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_ONLINE_NEMO_CTC_MODEL_CONFIG_H_
