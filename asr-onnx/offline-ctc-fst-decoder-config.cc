// asr-onnx/offline-ctc-fst-decoder-config.cc
//
 

#include "asr-onnx/offline-ctc-fst-decoder-config.h"

#include <sstream>
#include <string>

#include "asr-onnx/file-utils.h"
#include "asr-onnx/macros.h"

namespace sherpa_onnx {

std::string OfflineCtcFstDecoderConfig::ToString() const {
  std::ostringstream os;

  os << "OfflineCtcFstDecoderConfig(";
  os << "graph=\"" << graph << "\", ";
  os << "max_active=" << max_active << ")";

  return os.str();
}

void OfflineCtcFstDecoderConfig::Register(ParseOptions *po) {
  std::string prefix = "ctc";
  ParseOptions p(prefix, po);

  p.Register("graph", &graph, "Path to H.fst, HL.fst, or HLG.fst");

  p.Register("max-active", &max_active,
             "Decoder max active states.  Larger->slower; more accurate");
}

bool OfflineCtcFstDecoderConfig::Validate() const {
  if (!graph.empty() && !FileExists(graph)) {
    SHERPA_ONNX_LOGE("graph: '%s' does not exist", graph.c_str());
    return false;
  }
  return true;
}

}  // namespace sherpa_onnx
