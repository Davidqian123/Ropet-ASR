// asr-onnx/online-transducer-greedy-search-nemo-decoder.h
//
 
 

#ifndef SHERPA_ONNX_CSRC_ONLINE_TRANSDUCER_GREEDY_SEARCH_NEMO_DECODER_H_
#define SHERPA_ONNX_CSRC_ONLINE_TRANSDUCER_GREEDY_SEARCH_NEMO_DECODER_H_

#include <vector>

#include "asr-onnx/online-transducer-decoder.h"
#include "asr-onnx/online-transducer-nemo-model.h"

namespace sherpa_onnx {

class OnlineStream;

class OnlineTransducerGreedySearchNeMoDecoder {
 public:
  OnlineTransducerGreedySearchNeMoDecoder(OnlineTransducerNeMoModel *model,
                                          float blank_penalty)
      : model_(model), blank_penalty_(blank_penalty) {}

  // @param n number of elements in ss
  void Decode(Ort::Value encoder_out, OnlineStream **ss, int32_t n) const;

 private:
  OnlineTransducerNeMoModel *model_;  // Not owned
  float blank_penalty_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_ONLINE_TRANSDUCER_GREEDY_SEARCH_NEMO_DECODER_H_
