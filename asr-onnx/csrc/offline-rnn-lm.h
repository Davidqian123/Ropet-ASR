// asr-onnx/csrc/offline-rnn-lm.h
//
 

#ifndef SHERPA_ONNX_CSRC_OFFLINE_RNN_LM_H_
#define SHERPA_ONNX_CSRC_OFFLINE_RNN_LM_H_

#include <memory>

#include "onnxruntime_cxx_api.h"  // NOLINT
#include "asr-onnx/csrc/offline-lm-config.h"
#include "asr-onnx/csrc/offline-lm.h"

namespace sherpa_onnx {

class OfflineRnnLM : public OfflineLM {
 public:
  ~OfflineRnnLM() override;

  explicit OfflineRnnLM(const OfflineLMConfig &config);

  template <typename Manager>
  OfflineRnnLM(Manager *mgr, const OfflineLMConfig &config);

  /** Rescore a batch of sentences.
   *
   * @param x A 2-D tensor of shape (N, L) with data type int64.
   * @param x_lens A 1-D tensor of shape (N,) with data type int64.
   *               It contains number of valid tokens in x before padding.
   * @return Return a 1-D tensor of shape (N,) containing the log likelihood
   *         of each utterance. Its data type is float32.
   *
   * Caution: It returns log likelihood, not negative log likelihood (nll).
   */
  Ort::Value Rescore(Ort::Value x, Ort::Value x_lens) override;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_RNN_LM_H_
