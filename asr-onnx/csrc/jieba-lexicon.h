// asr-onnx/csrc/jieba-lexicon.h
//
 

#ifndef SHERPA_ONNX_CSRC_JIEBA_LEXICON_H_
#define SHERPA_ONNX_CSRC_JIEBA_LEXICON_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "asr-onnx/csrc/offline-tts-frontend.h"

namespace sherpa_onnx {

class JiebaLexicon : public OfflineTtsFrontend {
 public:
  ~JiebaLexicon() override;

  JiebaLexicon(const std::string &lexicon, const std::string &tokens,
               const std::string &dict_dir, bool debug);

  template <typename Manager>
  JiebaLexicon(Manager *mgr, const std::string &lexicon,
               const std::string &tokens, const std::string &dict_dir,
               bool debug);

  std::vector<TokenIDs> ConvertTextToTokenIds(
      const std::string &text,
      const std::string &unused_voice = "") const override;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_JIEBA_LEXICON_H_
