include_directories(${CMAKE_SOURCE_DIR})

# Define the core source files needed for asr-cli
set(sources
  base64-decode.cc
  bbpe.cc
  cat.cc
  circular-buffer.cc
  context-graph.cc
  endpoint.cc
  features.cc
  file-utils.cc
  fst-utils.cc
  hypothesis.cc
  offline-ctc-model.cc
  offline-lm-config.cc
  offline-lm.cc
  offline-model-config.cc
  offline-recognizer-impl.cc
  offline-recognizer.cc
  offline-stream.cc
  offline-transducer-greedy-search-decoder.cc
  offline-transducer-model-config.cc
  offline-transducer-model.cc
  offline-transducer-modified-beam-search-decoder.cc
  onnx-utils.cc
  packed-sequence.cc
  pad-sequence.cc
  parse-options.cc
  provider-config.cc
  provider.cc
  session.cc
  slice.cc
  stack.cc
  symbol-table.cc
  text-utils.cc
  transpose.cc
  unbind.cc
  utils.cc
  wave-reader.cc
  wave-writer.cc
)

# Build the core library (always static)
add_library(sherpa-onnx-core STATIC ${sources})

set_target_properties(
    sherpa-onnx-core
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
)

# Link the core library with its dependencies
target_link_libraries(sherpa-onnx-core
  kaldi-native-fbank-core
  kaldi-decoder-core
  ssentencepiece_core
)

if(BUILD_SHARED_LIBS AND NOT DEFINED onnxruntime_lib_files)
  target_link_libraries(sherpa-onnx-core onnxruntime)
else()
  target_link_libraries(sherpa-onnx-core ${onnxruntime_lib_files})
endif()

if(NOT WIN32)
  target_link_libraries(sherpa-onnx-core -lm)
endif()

target_link_libraries(sherpa-onnx-core fstfar fst)

if(NOT BUILD_SHARED_LIBS AND CMAKE_SYSTEM_NAME STREQUAL Linux)
  # For Linux ARM32 and ARM64
  target_link_libraries(sherpa-onnx-core -ldl)
endif()

if(NOT WIN32 AND CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_link_libraries(sherpa-onnx-core -pthread)
endif()

# Build asr-cli
add_executable(asr-cli asr-cli.cc)
target_link_libraries(asr-cli sherpa-onnx-core)

if(NOT WIN32)
  target_link_libraries(asr-cli "-Wl,-rpath,${SHERPA_ONNX_RPATH_ORIGIN}/../lib")
  target_link_libraries(asr-cli "-Wl,-rpath,${SHERPA_ONNX_RPATH_ORIGIN}/../../../sherpa_onnx/lib")
endif()

# Install targets
install(TARGETS sherpa-onnx-core DESTINATION lib)
install(TARGETS asr-cli DESTINATION bin)
