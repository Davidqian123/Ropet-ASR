// asr-onnx/offline-ced-model.h
//
 
#ifndef SHERPA_ONNX_CSRC_OFFLINE_CED_MODEL_H_
#define SHERPA_ONNX_CSRC_OFFLINE_CED_MODEL_H_
#include <memory>
#include <utility>

#if __ANDROID_API__ >= 9
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#endif

#include "onnxruntime_cxx_api.h"  // NOLINT
#include "asr-onnx/audio-tagging-model-config.h"

namespace sherpa_onnx {

/** This class implements the CED model from
 * https://github.com/RicherMans/CED/blob/main/export_onnx.py
 */
class OfflineCEDModel {
 public:
  explicit OfflineCEDModel(const AudioTaggingModelConfig &config);

#if __ANDROID_API__ >= 9
  OfflineCEDModel(AAssetManager *mgr, const AudioTaggingModelConfig &config);
#endif

  ~OfflineCEDModel();

  /** Run the forward method of the model.
   *
   * @param features  A tensor of shape (N, T, C).
   *
   * @return Return a tensor
   *  - probs: A 2-D tensor of shape (N, num_event_classes).
   */
  Ort::Value Forward(Ort::Value features) const;

  /** Return the number of event classes of the model
   */
  int32_t NumEventClasses() const;

  /** Return an allocator for allocating memory
   */
  OrtAllocator *Allocator() const;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_OFFLINE_CED_MODEL_H_
