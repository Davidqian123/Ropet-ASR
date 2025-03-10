// asr-onnx/kokoro-multi-lang-lexicon.h
//
 

#ifndef SHERPA_ONNX_CSRC_KOKORO_MULTI_LANG_LEXICON_H_
#define SHERPA_ONNX_CSRC_KOKORO_MULTI_LANG_LEXICON_H_

#include <memory>
#include <string>
#include <vector>

#include "asr-onnx/offline-tts-frontend.h"
#include "asr-onnx/offline-tts-kokoro-model-meta-data.h"

namespace sherpa_onnx {

class KokoroMultiLangLexicon : public OfflineTtsFrontend {
 public:
  ~KokoroMultiLangLexicon() override;

  KokoroMultiLangLexicon(const std::string &tokens, const std::string &lexicon,
                         const std::string &dict_dir,
                         const std::string &data_dir,
                         const OfflineTtsKokoroModelMetaData &meta_data,
                         bool debug);

  template <typename Manager>
  KokoroMultiLangLexicon(Manager *mgr, const std::string &tokens,
                         const std::string &lexicon,
                         const std::string &dict_dir,
                         const std::string &data_dir,
                         const OfflineTtsKokoroModelMetaData &meta_data,
                         bool debug);

  std::vector<TokenIDs> ConvertTextToTokenIds(
      const std::string &text, const std::string &voice = "") const override;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_KOKORO_MULTI_LANG_LEXICON_H_
