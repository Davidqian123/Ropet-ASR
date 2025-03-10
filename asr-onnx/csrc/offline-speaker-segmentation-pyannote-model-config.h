// asr-onnx/csrc/offline-speaker-segmentation-pyannote-model-config.h
//
 

#ifndef SHERPA_ONNX_CSRC_OFFLINE_SPEAKER_SEGMENTATION_PYANNOTE_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_OFFLINE_SPEAKER_SEGMENTATION_PYANNOTE_MODEL_CONFIG_H_
#include <string>

#include "asr-onnx/csrc/parse-options.h"

namespace sherpa_onnx {

struct OfflineSpeakerSegmentationPyannoteModelConfig {
  std::string model;

  OfflineSpeakerSegmentationPyannoteModelConfig() = default;

  explicit OfflineSpeakerSegmentationPyannoteModelConfig(
      const std::string &model)
      : model(model) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_SPEAKER_SEGMENTATION_PYANNOTE_MODEL_CONFIG_H_
