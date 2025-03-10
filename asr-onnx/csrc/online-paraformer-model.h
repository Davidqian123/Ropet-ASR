// asr-onnx/csrc/online-paraformer-model.h
//
 
#ifndef SHERPA_ONNX_CSRC_ONLINE_PARAFORMER_MODEL_H_
#define SHERPA_ONNX_CSRC_ONLINE_PARAFORMER_MODEL_H_

#include <memory>
#include <utility>
#include <vector>

#include "onnxruntime_cxx_api.h"  // NOLINT
#include "asr-onnx/csrc/online-model-config.h"

namespace sherpa_onnx {

class OnlineParaformerModel {
 public:
  explicit OnlineParaformerModel(const OnlineModelConfig &config);

  template <typename Manager>
  OnlineParaformerModel(Manager *mgr, const OnlineModelConfig &config);

  ~OnlineParaformerModel();

  std::vector<Ort::Value> ForwardEncoder(Ort::Value features,
                                         Ort::Value features_length) const;

  std::vector<Ort::Value> ForwardDecoder(Ort::Value encoder_out,
                                         Ort::Value encoder_out_length,
                                         Ort::Value acoustic_embedding,
                                         Ort::Value acoustic_embedding_length,
                                         std::vector<Ort::Value> states) const;

  /** Return the vocabulary size of the model
   */
  int32_t VocabSize() const;

  /** It is lfr_m in config.yaml
   */
  int32_t LfrWindowSize() const;

  /** It is lfr_n in config.yaml
   */
  int32_t LfrWindowShift() const;

  int32_t EncoderOutputSize() const;

  int32_t DecoderKernelSize() const;
  int32_t DecoderNumBlocks() const;

  /** Return negative mean for CMVN
   */
  const std::vector<float> &NegativeMean() const;

  /** Return inverse stddev for CMVN
   */
  const std::vector<float> &InverseStdDev() const;

  /** Return an allocator for allocating memory
   */
  OrtAllocator *Allocator() const;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_ONLINE_PARAFORMER_MODEL_H_
