// asr-onnx/offline-speaker-segmentation-model-config.h
//
 
#ifndef SHERPA_ONNX_CSRC_OFFLINE_SPEAKER_SEGMENTATION_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_OFFLINE_SPEAKER_SEGMENTATION_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/offline-speaker-segmentation-pyannote-model-config.h"
#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OfflineSpeakerSegmentationModelConfig {
  OfflineSpeakerSegmentationPyannoteModelConfig pyannote;

  int32_t num_threads = 1;
  bool debug = false;
  std::string provider = "cpu";

  OfflineSpeakerSegmentationModelConfig() = default;

  explicit OfflineSpeakerSegmentationModelConfig(
      const OfflineSpeakerSegmentationPyannoteModelConfig &pyannote,
      int32_t num_threads, bool debug, const std::string &provider)
      : pyannote(pyannote),
        num_threads(num_threads),
        debug(debug),
        provider(provider) {}

  void Register(ParseOptions *po);

  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_SPEAKER_SEGMENTATION_MODEL_CONFIG_H_
