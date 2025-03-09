// asr-onnx/csrc/offline-transducer-decoder.h
//
// Copyright (c)  2023  Xiaomi Corporation

#ifndef SHERPA_ONNX_CSRC_OFFLINE_TRANSDUCER_DECODER_H_
#define SHERPA_ONNX_CSRC_OFFLINE_TRANSDUCER_DECODER_H_

#include <vector>

#include "onnxruntime_cxx_api.h"  // NOLINT
#include "asr-onnx/csrc/offline-stream.h"

namespace sherpa_onnx {

struct OfflineTransducerDecoderResult {
  /// The decoded token IDs
  std::vector<int64_t> tokens;

  /// timestamps[i] contains the output frame index where tokens[i] is decoded.
  /// Note: The index is after subsampling
  std::vector<int32_t> timestamps;
};

class OfflineTransducerDecoder {
 public:
  virtual ~OfflineTransducerDecoder() = default;

  /** Run transducer beam search given the output from the encoder model.
   *
   * @param encoder_out A 3-D tensor of shape (N, T, joiner_dim)
   * @param encoder_out_length A 1-D tensor of shape (N,) containing number
   *                           of valid frames in encoder_out before padding.
   *
   * @return Return a vector of size `N` containing the decoded results.
   */
  virtual std::vector<OfflineTransducerDecoderResult> Decode(
      Ort::Value encoder_out, Ort::Value encoder_out_length,
      OfflineStream **ss = nullptr, int32_t n = 0) = 0;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_TRANSDUCER_DECODER_H_
