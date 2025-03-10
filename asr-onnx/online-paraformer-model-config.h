// asr-onnx/online-paraformer-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_ONLINE_PARAFORMER_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_ONLINE_PARAFORMER_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OnlineParaformerModelConfig {
  std::string encoder;
  std::string decoder;

  OnlineParaformerModelConfig() = default;

  OnlineParaformerModelConfig(const std::string &encoder,
                              const std::string &decoder)
      : encoder(encoder), decoder(decoder) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_ONLINE_PARAFORMER_MODEL_CONFIG_H_
