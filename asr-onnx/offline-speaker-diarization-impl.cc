// asr-onnx/offline-speaker-diarization-impl.cc
//
 

#include "asr-onnx/offline-speaker-diarization-impl.h"

#include <memory>

#if __ANDROID_API__ >= 9
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#endif

#if __OHOS__
#include "rawfile/raw_file_manager.h"
#endif

#include "asr-onnx/macros.h"
#include "asr-onnx/offline-speaker-diarization-pyannote-impl.h"

namespace sherpa_onnx {

std::unique_ptr<OfflineSpeakerDiarizationImpl>
OfflineSpeakerDiarizationImpl::Create(
    const OfflineSpeakerDiarizationConfig &config) {
  if (!config.segmentation.pyannote.model.empty()) {
    return std::make_unique<OfflineSpeakerDiarizationPyannoteImpl>(config);
  }

  SHERPA_ONNX_LOGE("Please specify a speaker segmentation model.");

  return nullptr;
}

template <typename Manager>
std::unique_ptr<OfflineSpeakerDiarizationImpl>
OfflineSpeakerDiarizationImpl::Create(
    Manager *mgr, const OfflineSpeakerDiarizationConfig &config) {
  if (!config.segmentation.pyannote.model.empty()) {
    return std::make_unique<OfflineSpeakerDiarizationPyannoteImpl>(mgr, config);
  }

  SHERPA_ONNX_LOGE("Please specify a speaker segmentation model.");

  return nullptr;
}

#if __ANDROID_API__ >= 9
template std::unique_ptr<OfflineSpeakerDiarizationImpl>
OfflineSpeakerDiarizationImpl::Create(
    AAssetManager *mgr, const OfflineSpeakerDiarizationConfig &config);
#endif

#if __OHOS__
template std::unique_ptr<OfflineSpeakerDiarizationImpl>
OfflineSpeakerDiarizationImpl::Create(
    NativeResourceManager *mgr, const OfflineSpeakerDiarizationConfig &config);
#endif

}  // namespace sherpa_onnx
