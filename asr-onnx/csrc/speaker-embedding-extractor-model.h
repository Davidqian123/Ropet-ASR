// asr-onnx/csrc/speaker-embedding-extractor-model.h
//
// Copyright (c)  2024  Xiaomi Corporation
#ifndef SHERPA_ONNX_CSRC_SPEAKER_EMBEDDING_EXTRACTOR_MODEL_H_
#define SHERPA_ONNX_CSRC_SPEAKER_EMBEDDING_EXTRACTOR_MODEL_H_

#include <memory>

#include "onnxruntime_cxx_api.h"  // NOLINT
#include "asr-onnx/csrc/speaker-embedding-extractor-model-meta-data.h"
#include "asr-onnx/csrc/speaker-embedding-extractor.h"

namespace sherpa_onnx {

class SpeakerEmbeddingExtractorModel {
 public:
  explicit SpeakerEmbeddingExtractorModel(
      const SpeakerEmbeddingExtractorConfig &config);

  template <typename Manager>
  SpeakerEmbeddingExtractorModel(Manager *mgr,
                                 const SpeakerEmbeddingExtractorConfig &config);

  ~SpeakerEmbeddingExtractorModel();

  const SpeakerEmbeddingExtractorModelMetaData &GetMetaData() const;

  /**
   * @param x A float32 tensor of shape (N, T, C)
   * @return A float32 tensor of shape (N, C)
   */
  Ort::Value Compute(Ort::Value x) const;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_SPEAKER_EMBEDDING_EXTRACTOR_MODEL_H_
