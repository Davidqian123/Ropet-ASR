// asr-onnx/keyword-spotter-impl.cc
//
 

#include "asr-onnx/keyword-spotter-impl.h"

#include "asr-onnx/keyword-spotter-transducer-impl.h"

#if __ANDROID_API__ >= 9
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#endif

#if __OHOS__
#include "rawfile/raw_file_manager.h"
#endif

namespace sherpa_onnx {

std::unique_ptr<KeywordSpotterImpl> KeywordSpotterImpl::Create(
    const KeywordSpotterConfig &config) {
  if (!config.model_config.transducer.encoder.empty()) {
    return std::make_unique<KeywordSpotterTransducerImpl>(config);
  }

  SHERPA_ONNX_LOGE("Please specify a model");
  exit(-1);
}

template <typename Manager>
std::unique_ptr<KeywordSpotterImpl> KeywordSpotterImpl::Create(
    Manager *mgr, const KeywordSpotterConfig &config) {
  if (!config.model_config.transducer.encoder.empty()) {
    return std::make_unique<KeywordSpotterTransducerImpl>(mgr, config);
  }

  SHERPA_ONNX_LOGE("Please specify a model");
  exit(-1);
}

#if __ANDROID_API__ >= 9
template std::unique_ptr<KeywordSpotterImpl> KeywordSpotterImpl::Create(
    AAssetManager *mgr, const KeywordSpotterConfig &config);
#endif

#if __OHOS__
template std::unique_ptr<KeywordSpotterImpl> KeywordSpotterImpl::Create(
    NativeResourceManager *mgr, const KeywordSpotterConfig &config);
#endif

}  // namespace sherpa_onnx
