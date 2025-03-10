// asr-onnx/csrc/online-model-config.cc
//
 
#include "asr-onnx/csrc/online-model-config.h"

#include <string>

#include "asr-onnx/csrc/file-utils.h"
#include "asr-onnx/csrc/macros.h"
#include "asr-onnx/csrc/text-utils.h"

namespace sherpa_onnx {

void OnlineModelConfig::Register(ParseOptions *po) {
  transducer.Register(po);
  paraformer.Register(po);
  wenet_ctc.Register(po);
  zipformer2_ctc.Register(po);
  nemo_ctc.Register(po);
  provider_config.Register(po);

  po->Register("tokens", &tokens, "Path to tokens.txt");

  po->Register("num-threads", &num_threads,
               "Number of threads to run the neural network");

  po->Register("warm-up", &warm_up,
               "Number of warm-up to run the onnxruntime"
               "Valid vales are: zipformer2");

  po->Register("debug", &debug,
               "true to print model information while loading it.");

  po->Register("modeling-unit", &modeling_unit,
               "The modeling unit of the model, commonly used units are bpe, "
               "cjkchar, cjkchar+bpe, etc. Currently, it is needed only when "
               "hotwords are provided, we need it to encode the hotwords into "
               "token sequence.");

  po->Register("bpe-vocab", &bpe_vocab,
               "The vocabulary generated by google's sentencepiece program. "
               "It is a file has two columns, one is the token, the other is "
               "the log probability, you can get it from the directory where "
               "your bpe model is generated. Only used when hotwords provided "
               "and the modeling unit is bpe or cjkchar+bpe");

  po->Register("model-type", &model_type,
               "Specify it to reduce model initialization time. "
               "Valid values are: conformer, lstm, zipformer, zipformer2, "
               "wenet_ctc, nemo_ctc. "
               "All other values lead to loading the model twice.");
}

bool OnlineModelConfig::Validate() const {
  // For RK NPU, we reinterpret num_threads:
  //
  // For RK3588 only
  // num_threads == 1 -> Select a core randomly
  // num_threads == 0 -> Use NPU core 0
  // num_threads == -1 -> Use NPU core 1
  // num_threads == -2 -> Use NPU core 2
  // num_threads == -3 -> Use NPU core 0 and core 1
  // num_threads == -4 -> Use NPU core 0, core 1, and core 2
  if (provider_config.provider != "rknn") {
    if (num_threads < 1) {
      SHERPA_ONNX_LOGE("num_threads should be > 0. Given %d", num_threads);
      return false;
    }
    if (!transducer.encoder.empty() && (EndsWith(transducer.encoder, ".rknn") ||
                                        EndsWith(transducer.decoder, ".rknn") ||
                                        EndsWith(transducer.joiner, ".rknn"))) {
      SHERPA_ONNX_LOGE(
          "--provider is %s, which is not rknn, but you pass rknn model "
          "filenames. encoder: '%s', decoder: '%s', joiner: '%s'",
          provider_config.provider.c_str(), transducer.encoder.c_str(),
          transducer.decoder.c_str(), transducer.joiner.c_str());
      return false;
    }

    if (!zipformer2_ctc.model.empty() &&
        EndsWith(zipformer2_ctc.model, ".rknn")) {
      SHERPA_ONNX_LOGE(
          "--provider is %s, which is not rknn, but you pass rknn model "
          "filename for zipformer2_ctc: '%s'",
          provider_config.provider.c_str(), zipformer2_ctc.model.c_str());
      return false;
    }
  }

  if (provider_config.provider == "rknn") {
    if (!transducer.encoder.empty() && (EndsWith(transducer.encoder, ".onnx") ||
                                        EndsWith(transducer.decoder, ".onnx") ||
                                        EndsWith(transducer.joiner, ".onnx"))) {
      SHERPA_ONNX_LOGE(
          "--provider is rknn, but you pass onnx model "
          "filenames. encoder: '%s', decoder: '%s', joiner: '%s'",
          transducer.encoder.c_str(), transducer.decoder.c_str(),
          transducer.joiner.c_str());
      return false;
    }

    if (!zipformer2_ctc.model.empty() &&
        EndsWith(zipformer2_ctc.model, ".onnx")) {
      SHERPA_ONNX_LOGE(
          "--provider rknn, but you pass onnx model filename for "
          "zipformer2_ctc: '%s'",
          zipformer2_ctc.model.c_str());
      return false;
    }
  }

  if (!tokens_buf.empty() && FileExists(tokens)) {
    SHERPA_ONNX_LOGE(
        "you can not provide a tokens_buf and a tokens file: '%s', "
        "at the same time, which is confusing",
        tokens.c_str());
    return false;
  }

  if (tokens_buf.empty() && !FileExists(tokens)) {
    SHERPA_ONNX_LOGE(
        "tokens: '%s' does not exist, you should provide "
        "either a tokens buffer or a tokens file",
        tokens.c_str());
    return false;
  }

  if (!modeling_unit.empty() &&
      (modeling_unit == "bpe" || modeling_unit == "cjkchar+bpe")) {
    if (!FileExists(bpe_vocab)) {
      SHERPA_ONNX_LOGE("bpe_vocab: '%s' does not exist", bpe_vocab.c_str());
      return false;
    }
  }

  if (!paraformer.encoder.empty()) {
    return paraformer.Validate();
  }

  if (!wenet_ctc.model.empty()) {
    return wenet_ctc.Validate();
  }

  if (!zipformer2_ctc.model.empty()) {
    return zipformer2_ctc.Validate();
  }

  if (!nemo_ctc.model.empty()) {
    return nemo_ctc.Validate();
  }

  if (!provider_config.Validate()) {
    return false;
  }

  return transducer.Validate();
}

std::string OnlineModelConfig::ToString() const {
  std::ostringstream os;

  os << "OnlineModelConfig(";
  os << "transducer=" << transducer.ToString() << ", ";
  os << "paraformer=" << paraformer.ToString() << ", ";
  os << "wenet_ctc=" << wenet_ctc.ToString() << ", ";
  os << "zipformer2_ctc=" << zipformer2_ctc.ToString() << ", ";
  os << "nemo_ctc=" << nemo_ctc.ToString() << ", ";
  os << "provider_config=" << provider_config.ToString() << ", ";
  os << "tokens=\"" << tokens << "\", ";
  os << "num_threads=" << num_threads << ", ";
  os << "warm_up=" << warm_up << ", ";
  os << "debug=" << (debug ? "True" : "False") << ", ";
  os << "model_type=\"" << model_type << "\", ";
  os << "modeling_unit=\"" << modeling_unit << "\", ";
  os << "bpe_vocab=\"" << bpe_vocab << "\")";

  return os.str();
}

}  // namespace sherpa_onnx
