// asr-onnx/offline-transducer-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_OFFLINE_TRANSDUCER_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_OFFLINE_TRANSDUCER_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OfflineTransducerModelConfig {
  std::string encoder_filename;
  std::string decoder_filename;
  std::string joiner_filename;

  OfflineTransducerModelConfig() = default;
  OfflineTransducerModelConfig(const std::string &encoder_filename,
                               const std::string &decoder_filename,
                               const std::string &joiner_filename)
      : encoder_filename(encoder_filename),
        decoder_filename(decoder_filename),
        joiner_filename(joiner_filename) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_TRANSDUCER_MODEL_CONFIG_H_
