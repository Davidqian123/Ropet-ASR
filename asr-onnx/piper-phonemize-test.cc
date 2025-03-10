// asr-onnx/piper-phonemize-test.cc
//
 

#include "espeak-ng/speak_lib.h"
#include "gtest/gtest.h"
#include "phoneme_ids.hpp"
#include "phonemize.hpp"
#include "asr-onnx/file-utils.h"
#include "asr-onnx/macros.h"

namespace sherpa_onnx {

TEST(PiperPhonemize, Case1) {
  std::string data_dir = "./install/share/espeak-ng-data";
  if (!FileExists(data_dir + "/en_dict")) {
    SHERPA_ONNX_LOGE("%s/en_dict does not exist. Skipping test",
                     data_dir.c_str());
    return;
  }

  if (!FileExists(data_dir + "/phontab")) {
    SHERPA_ONNX_LOGE("%s/phontab does not exist. Skipping test",
                     data_dir.c_str());
    return;
  }

  if (!FileExists(data_dir + "/phonindex")) {
    SHERPA_ONNX_LOGE("%s/phonindex does not exist. Skipping test",
                     data_dir.c_str());
    return;
  }

  if (!FileExists(data_dir + "/phondata")) {
    SHERPA_ONNX_LOGE("%s/phondata does not exist. Skipping test",
                     data_dir.c_str());
    return;
  }

  if (!FileExists(data_dir + "/intonations")) {
    SHERPA_ONNX_LOGE("%s/intonations does not exist. Skipping test",
                     data_dir.c_str());
    return;
  }
  int32_t result =
      espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 0, data_dir.c_str(), 0);
  EXPECT_EQ(result, 22050);

  piper::eSpeakPhonemeConfig config;

  // ./bin/espeak-ng-bin --path  ./install/share/espeak-ng-data/ --voices
  // to list available voices
  config.voice = "en-us";

  std::vector<std::vector<piper::Phoneme>> phonemes;
  std::string text = "how are you doing?";
  piper::phonemize_eSpeak(text, config, phonemes);

  for (int32_t p : phonemes[0]) {
    std::cout << p << " ";
  }
  std::cout << "\n";

  std::vector<piper::PhonemeId> phoneme_ids;
  std::map<piper::Phoneme, std::size_t> missing_phonemes;

  {
    piper::PhonemeIdConfig config;
    phonemes_to_ids(phonemes[0], config, phoneme_ids, missing_phonemes);
  }

  for (int32_t p : phoneme_ids) {
    std::cout << p << " ";
  }
  std::cout << "\n";
}

}  // namespace sherpa_onnx
