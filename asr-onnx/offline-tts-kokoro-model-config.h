// asr-onnx/offline-tts-kokoro-model-config.h
//
 

#ifndef SHERPA_ONNX_CSRC_OFFLINE_TTS_KOKORO_MODEL_CONFIG_H_
#define SHERPA_ONNX_CSRC_OFFLINE_TTS_KOKORO_MODEL_CONFIG_H_

#include <string>

#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OfflineTtsKokoroModelConfig {
  std::string model;
  std::string voices;
  std::string tokens;

  // Note: You can pass multiple files, separated by ",", to lexicon
  // Example: lexicon = "./lexicon-gb-en.txt,./lexicon-zh.txt";
  std::string lexicon;

  std::string data_dir;

  std::string dict_dir;

  // speed = 1 / length_scale
  float length_scale = 1.0;

  OfflineTtsKokoroModelConfig() = default;

  OfflineTtsKokoroModelConfig(const std::string &model,
                              const std::string &voices,
                              const std::string &tokens,
                              const std::string &lexicon,
                              const std::string &data_dir,
                              const std::string &dict_dir, float length_scale)
      : model(model),
        voices(voices),
        tokens(tokens),
        lexicon(lexicon),
        data_dir(data_dir),
        dict_dir(dict_dir),
        length_scale(length_scale) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_TTS_KOKORO_MODEL_CONFIG_H_
