// asr-onnx/csrc/melo-tts-lexicon.h
//
 

#ifndef SHERPA_ONNX_CSRC_MELO_TTS_LEXICON_H_
#define SHERPA_ONNX_CSRC_MELO_TTS_LEXICON_H_

#include <memory>
#include <string>
#include <vector>

#include "asr-onnx/csrc/offline-tts-frontend.h"
#include "asr-onnx/csrc/offline-tts-vits-model-meta-data.h"

namespace sherpa_onnx {

class MeloTtsLexicon : public OfflineTtsFrontend {
 public:
  ~MeloTtsLexicon() override;
  MeloTtsLexicon(const std::string &lexicon, const std::string &tokens,
                 const std::string &dict_dir,
                 const OfflineTtsVitsModelMetaData &meta_data, bool debug);

  MeloTtsLexicon(const std::string &lexicon, const std::string &tokens,
                 const OfflineTtsVitsModelMetaData &meta_data, bool debug);

  template <typename Manager>
  MeloTtsLexicon(Manager *mgr, const std::string &lexicon,
                 const std::string &tokens, const std::string &dict_dir,
                 const OfflineTtsVitsModelMetaData &meta_data, bool debug);

  template <typename Manager>
  MeloTtsLexicon(Manager *mgr, const std::string &lexicon,
                 const std::string &tokens,
                 const OfflineTtsVitsModelMetaData &meta_data, bool debug);

  std::vector<TokenIDs> ConvertTextToTokenIds(
      const std::string &text,
      const std::string &unused_voice = "") const override;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_MELO_TTS_LEXICON_H_
