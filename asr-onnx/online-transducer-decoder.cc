// asr-onnx/online-transducer-decoder.cc
//
 

#include "asr-onnx/online-transducer-decoder.h"

#include <utility>
#include <vector>

#include "onnxruntime_cxx_api.h"  // NOLINT
#include "asr-onnx/onnx-utils.h"

namespace sherpa_onnx {

OnlineTransducerDecoderResult::OnlineTransducerDecoderResult(
    const OnlineTransducerDecoderResult &other)
    : OnlineTransducerDecoderResult() {
  *this = other;
}

OnlineTransducerDecoderResult &OnlineTransducerDecoderResult::operator=(
    const OnlineTransducerDecoderResult &other) {
  if (this == &other) {
    return *this;
  }

  tokens = other.tokens;
  num_trailing_blanks = other.num_trailing_blanks;

  Ort::AllocatorWithDefaultOptions allocator;
  if (other.decoder_out) {
    decoder_out = Clone(allocator, &other.decoder_out);
  }

  hyps = other.hyps;

  frame_offset = other.frame_offset;
  timestamps = other.timestamps;

  ys_probs = other.ys_probs;
  lm_probs = other.lm_probs;
  context_scores = other.context_scores;

  return *this;
}

OnlineTransducerDecoderResult::OnlineTransducerDecoderResult(
    OnlineTransducerDecoderResult &&other) noexcept
    : OnlineTransducerDecoderResult() {
  *this = std::move(other);
}

OnlineTransducerDecoderResult &OnlineTransducerDecoderResult::operator=(
    OnlineTransducerDecoderResult &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  tokens = std::move(other.tokens);
  num_trailing_blanks = other.num_trailing_blanks;
  decoder_out = std::move(other.decoder_out);
  hyps = std::move(other.hyps);

  frame_offset = other.frame_offset;
  timestamps = std::move(other.timestamps);

  ys_probs = std::move(other.ys_probs);
  lm_probs = std::move(other.lm_probs);
  context_scores = std::move(other.context_scores);

  return *this;
}

}  // namespace sherpa_onnx
