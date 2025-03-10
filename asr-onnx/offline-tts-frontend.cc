// asr-onnx/offline-tts-frontend.cc
//
 

#include "asr-onnx/offline-tts-frontend.h"

#include <sstream>
#include <string>

namespace sherpa_onnx {

std::string TokenIDs::ToString() const {
  std::ostringstream os;
  os << "TokenIDs(";
  os << "tokens=[";
  std::string sep;
  for (auto i : tokens) {
    os << sep << i;
    sep = ", ";
  }
  os << "], ";

  os << "tones=[";
  sep = {};
  for (auto i : tones) {
    os << sep << i;
    sep = ", ";
  }
  os << "]";
  os << ")";
  return os.str();
}

}  // namespace sherpa_onnx
