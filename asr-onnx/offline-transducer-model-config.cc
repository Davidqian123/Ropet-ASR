// asr-onnx/offline-transducer-model-config.cc
//
 
#include "asr-onnx/offline-transducer-model-config.h"

#include <sstream>

#include "asr-onnx/file-utils.h"
#include "asr-onnx/macros.h"

namespace sherpa_onnx {

void OfflineTransducerModelConfig::Register(ParseOptions *po) {
  po->Register("encoder", &encoder_filename, "Path to encoder.onnx");
  po->Register("decoder", &decoder_filename, "Path to decoder.onnx");
  po->Register("joiner", &joiner_filename, "Path to joiner.onnx");
}

bool OfflineTransducerModelConfig::Validate() const {
  if (!FileExists(encoder_filename)) {
    SHERPA_ONNX_LOGE("transducer encoder: '%s' does not exist",
                     encoder_filename.c_str());
    return false;
  }

  if (!FileExists(decoder_filename)) {
    SHERPA_ONNX_LOGE("transducer decoder: '%s' does not exist",
                     decoder_filename.c_str());
    return false;
  }

  if (!FileExists(joiner_filename)) {
    SHERPA_ONNX_LOGE("transducer joiner: '%s' does not exist",
                     joiner_filename.c_str());
    return false;
  }

  return true;
}

std::string OfflineTransducerModelConfig::ToString() const {
  std::ostringstream os;

  os << "OfflineTransducerModelConfig(";
  os << "encoder_filename=\"" << encoder_filename << "\", ";
  os << "decoder_filename=\"" << decoder_filename << "\", ";
  os << "joiner_filename=\"" << joiner_filename << "\")";

  return os.str();
}

}  // namespace sherpa_onnx
