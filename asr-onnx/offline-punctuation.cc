// asr-onnx/offline-punctuation.cc
//
 

#include "asr-onnx/offline-punctuation.h"

#if __ANDROID_API__ >= 9
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#endif

#include "asr-onnx/macros.h"
#include "asr-onnx/offline-punctuation-impl.h"

namespace sherpa_onnx {

void OfflinePunctuationConfig::Register(ParseOptions *po) {
  model.Register(po);
}

bool OfflinePunctuationConfig::Validate() const {
  if (!model.Validate()) {
    return false;
  }

  return true;
}

std::string OfflinePunctuationConfig::ToString() const {
  std::ostringstream os;

  os << "OfflinePunctuationConfig(";
  os << "model=" << model.ToString() << ")";

  return os.str();
}

OfflinePunctuation::OfflinePunctuation(const OfflinePunctuationConfig &config)
    : impl_(OfflinePunctuationImpl::Create(config)) {}

#if __ANDROID_API__ >= 9
OfflinePunctuation::OfflinePunctuation(AAssetManager *mgr,
                                       const OfflinePunctuationConfig &config)
    : impl_(OfflinePunctuationImpl::Create(mgr, config)) {}
#endif

OfflinePunctuation::~OfflinePunctuation() = default;

std::string OfflinePunctuation::AddPunctuation(const std::string &text) const {
  return impl_->AddPunctuation(text);
}

}  // namespace sherpa_onnx
