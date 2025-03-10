// asr-onnx/piper-phonemize-lexicon.h
//
 

#ifndef SHERPA_ONNX_CSRC_PIPER_PHONEMIZE_LEXICON_H_
#define SHERPA_ONNX_CSRC_PIPER_PHONEMIZE_LEXICON_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "asr-onnx/offline-tts-frontend.h"
#include "asr-onnx/offline-tts-kokoro-model-meta-data.h"
#include "asr-onnx/offline-tts-matcha-model-meta-data.h"
#include "asr-onnx/offline-tts-vits-model-meta-data.h"

namespace sherpa_onnx {

class PiperPhonemizeLexicon : public OfflineTtsFrontend {
 public:
  PiperPhonemizeLexicon(const std::string &tokens, const std::string &data_dir,
                        const OfflineTtsVitsModelMetaData &vits_meta_data);

  PiperPhonemizeLexicon(const std::string &tokens, const std::string &data_dir,
                        const OfflineTtsMatchaModelMetaData &matcha_meta_data);

  PiperPhonemizeLexicon(const std::string &tokens, const std::string &data_dir,
                        const OfflineTtsKokoroModelMetaData &kokoro_meta_data);

  template <typename Manager>
  PiperPhonemizeLexicon(Manager *mgr, const std::string &tokens,
                        const std::string &data_dir,
                        const OfflineTtsVitsModelMetaData &vits_meta_data);

  template <typename Manager>
  PiperPhonemizeLexicon(Manager *mgr, const std::string &tokens,
                        const std::string &data_dir,
                        const OfflineTtsMatchaModelMetaData &matcha_meta_data);

  template <typename Manager>
  PiperPhonemizeLexicon(Manager *mgr, const std::string &tokens,
                        const std::string &data_dir,
                        const OfflineTtsKokoroModelMetaData &kokoro_meta_data);

  std::vector<TokenIDs> ConvertTextToTokenIds(
      const std::string &text, const std::string &voice = "") const override;

 private:
  std::vector<TokenIDs> ConvertTextToTokenIdsVits(
      const std::string &text, const std::string &voice = "") const;

  std::vector<TokenIDs> ConvertTextToTokenIdsMatcha(
      const std::string &text, const std::string &voice = "") const;

  std::vector<TokenIDs> ConvertTextToTokenIdsKokoro(
      const std::string &text, const std::string &voice = "") const;

 private:
  // map unicode codepoint to an integer ID
  std::unordered_map<char32_t, int32_t> token2id_;
  OfflineTtsVitsModelMetaData vits_meta_data_;
  OfflineTtsMatchaModelMetaData matcha_meta_data_;
  OfflineTtsKokoroModelMetaData kokoro_meta_data_;
  bool is_matcha_ = false;
  bool is_kokoro_ = false;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_PIPER_PHONEMIZE_LEXICON_H_
