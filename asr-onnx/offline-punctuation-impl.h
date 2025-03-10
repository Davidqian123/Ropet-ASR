// asr-onnx/offline-punctuation-impl.h
//
 
#ifndef SHERPA_ONNX_CSRC_OFFLINE_PUNCTUATION_IMPL_H_
#define SHERPA_ONNX_CSRC_OFFLINE_PUNCTUATION_IMPL_H_

#include <memory>
#include <string>
#include <vector>
#if __ANDROID_API__ >= 9
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#endif

#include "asr-onnx/offline-punctuation.h"

namespace sherpa_onnx {

class OfflinePunctuationImpl {
 public:
  virtual ~OfflinePunctuationImpl() = default;

  static std::unique_ptr<OfflinePunctuationImpl> Create(
      const OfflinePunctuationConfig &config);

#if __ANDROID_API__ >= 9
  static std::unique_ptr<OfflinePunctuationImpl> Create(
      AAssetManager *mgr, const OfflinePunctuationConfig &config);
#endif

  virtual std::string AddPunctuation(const std::string &text) const = 0;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_PUNCTUATION_IMPL_H_
