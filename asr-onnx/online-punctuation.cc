// asr-onnx/online-punctuation.cc
//
 

#include "asr-onnx/online-punctuation.h"

#if __ANDROID_API__ >= 9
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#endif

#include "asr-onnx/macros.h"
#include "asr-onnx/online-punctuation-impl.h"

namespace sherpa_onnx {

void OnlinePunctuationConfig::Register(ParseOptions *po) { model.Register(po); }

bool OnlinePunctuationConfig::Validate() const {
  if (!model.Validate()) {
    return false;
  }

  return true;
}

std::string OnlinePunctuationConfig::ToString() const {
  std::ostringstream os;

  os << "OnlinePunctuationConfig(";
  os << "model=" << model.ToString() << ")";

  return os.str();
}

OnlinePunctuation::OnlinePunctuation(const OnlinePunctuationConfig &config)
    : impl_(OnlinePunctuationImpl::Create(config)) {}

#if __ANDROID_API__ >= 9
OnlinePunctuation::OnlinePunctuation(AAssetManager *mgr,
                                     const OnlinePunctuationConfig &config)
    : impl_(OnlinePunctuationImpl::Create(mgr, config)) {}
#endif

OnlinePunctuation::~OnlinePunctuation() = default;

std::string OnlinePunctuation::AddPunctuationWithCase(
    const std::string &text) const {
  return impl_->AddPunctuationWithCase(text);
}

}  // namespace sherpa_onnx
