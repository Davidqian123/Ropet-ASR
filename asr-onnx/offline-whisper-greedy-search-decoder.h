// asr-onnx/offline-whisper-greedy-search-decoder.h
//
 

#ifndef SHERPA_ONNX_CSRC_OFFLINE_WHISPER_GREEDY_SEARCH_DECODER_H_
#define SHERPA_ONNX_CSRC_OFFLINE_WHISPER_GREEDY_SEARCH_DECODER_H_

#include <vector>

#include "asr-onnx/offline-whisper-decoder.h"
#include "asr-onnx/offline-whisper-model.h"

namespace sherpa_onnx {

class OfflineWhisperGreedySearchDecoder : public OfflineWhisperDecoder {
 public:
  OfflineWhisperGreedySearchDecoder(const OfflineWhisperModelConfig &config,
                                    OfflineWhisperModel *model)
      : config_(config), model_(model) {}

  std::vector<OfflineWhisperDecoderResult> Decode(
      Ort::Value cross_k, Ort::Value cross_v,
      int32_t num_feature_frames) override;

  void SetConfig(const OfflineWhisperModelConfig &config) override;

 private:
  OfflineWhisperModelConfig config_;
  OfflineWhisperModel *model_;  // not owned
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_WHISPER_GREEDY_SEARCH_DECODER_H_
