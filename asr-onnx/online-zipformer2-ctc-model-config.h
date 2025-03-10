// asr-onnx/online-zipformer2-ctc-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_ONLINE_ZIPFORMER2_CTC_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_ONLINE_ZIPFORMER2_CTC_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OnlineZipformer2CtcModelConfig {
  std::string model;

  OnlineZipformer2CtcModelConfig() = default;

  explicit OnlineZipformer2CtcModelConfig(const std::string &model)
      : model(model) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_ONLINE_ZIPFORMER2_CTC_MODEL_CONFIG_H_
