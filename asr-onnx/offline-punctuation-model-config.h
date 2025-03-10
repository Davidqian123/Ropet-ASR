// asr-onnx/offline-punctuation-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_OFFLINE_PUNCTUATION_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_OFFLINE_PUNCTUATION_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OfflinePunctuationModelConfig {
  std::string ct_transformer;

  int32_t num_threads = 1;
  bool debug = false;
  std::string provider = "cpu";

  OfflinePunctuationModelConfig() = default;

  OfflinePunctuationModelConfig(const std::string &ct_transformer,
                                int32_t num_threads, bool debug,
                                const std::string &provider)
      : ct_transformer(ct_transformer),
        num_threads(num_threads),
        debug(debug),
        provider(provider) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_PUNCTUATION_MODEL_CONFIG_H_
