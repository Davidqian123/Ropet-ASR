// asr-onnx/offline-moonshine-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_OFFLINE_MOONSHINE_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_OFFLINE_MOONSHINE_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OfflineMoonshineModelConfig {
  std::string preprocessor;
  std::string encoder;
  std::string uncached_decoder;
  std::string cached_decoder;

  OfflineMoonshineModelConfig() = default;
  OfflineMoonshineModelConfig(const std::string &preprocessor,
                              const std::string &encoder,
                              const std::string &uncached_decoder,
                              const std::string &cached_decoder)
      : preprocessor(preprocessor),
        encoder(encoder),
        uncached_decoder(uncached_decoder),
        cached_decoder(cached_decoder) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_MOONSHINE_MODEL_CONFIG_H_
