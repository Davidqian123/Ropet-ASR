// asr-onnx/online-punctuation.h
//
 

#ifndef SHERPA_ONNX_CSRC_ONLINE_PUNCTUATION_H_
#define SHERPA_ONNX_CSRC_ONLINE_PUNCTUATION_H_

#include <memory>
#include <string>
#include <vector>

#if __ANDROID_API__ >= 9
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#endif

#include "asr-onnx/online-punctuation-model-config.h"
#include "asr-onnx/parse-options.h"

namespace sherpa_onnx {

struct OnlinePunctuationConfig {
  OnlinePunctuationModelConfig model;

  OnlinePunctuationConfig() = default;

  explicit OnlinePunctuationConfig(const OnlinePunctuationModelConfig &model)
      : model(model) {}

  void Register(ParseOptions *po);
  bool Validate() const;

  std::string ToString() const;
};

class OnlinePunctuationImpl;

class OnlinePunctuation {
 public:
  explicit OnlinePunctuation(const OnlinePunctuationConfig &config);

#if __ANDROID_API__ >= 9
  OnlinePunctuation(AAssetManager *mgr, const OnlinePunctuationConfig &config);
#endif

  ~OnlinePunctuation();

  // Add punctuation and casing to the input text and return it.
  std::string AddPunctuationWithCase(const std::string &text) const;

 private:
  std::unique_ptr<OnlinePunctuationImpl> impl_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_ONLINE_PUNCTUATION_H_
