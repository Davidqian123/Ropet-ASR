include_directories(${CMAKE_SOURCE_DIR})

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
  keyword-spotter-impl.cc
  keyword-spotter.cc
  offline-ctc-fst-decoder-config.cc
  offline-ctc-fst-decoder.cc
  offline-ctc-greedy-search-decoder.cc
  offline-ctc-model.cc
  offline-fire-red-asr-greedy-search-decoder.cc
  offline-fire-red-asr-model-config.cc
  offline-fire-red-asr-model.cc
  offline-lm-config.cc
  offline-lm.cc
  offline-model-config.cc
  offline-moonshine-greedy-search-decoder.cc
  offline-moonshine-model-config.cc
  offline-moonshine-model.cc
  offline-nemo-enc-dec-ctc-model-config.cc
  offline-nemo-enc-dec-ctc-model.cc
  offline-paraformer-greedy-search-decoder.cc
  offline-paraformer-model-config.cc
  offline-paraformer-model.cc
  offline-recognizer-impl.cc
  offline-recognizer.cc
  offline-rnn-lm.cc
  offline-sense-voice-model-config.cc
  offline-sense-voice-model.cc
  offline-stream.cc
  offline-tdnn-ctc-model.cc
  offline-tdnn-model-config.cc
  offline-telespeech-ctc-model.cc
  offline-transducer-greedy-search-decoder.cc
  offline-transducer-greedy-search-nemo-decoder.cc
  offline-transducer-model-config.cc
  offline-transducer-model.cc
  offline-transducer-modified-beam-search-decoder.cc
  offline-transducer-nemo-model.cc
  offline-wenet-ctc-model-config.cc
  offline-wenet-ctc-model.cc
  offline-whisper-greedy-search-decoder.cc
  offline-whisper-model-config.cc
  offline-whisper-model.cc
  offline-zipformer-ctc-model-config.cc
  offline-zipformer-ctc-model.cc
  onnx-utils.cc
  packed-sequence.cc
  pad-sequence.cc
  parse-options.cc
  provider-config.cc
  provider.cc
  resample.cc
  session.cc
  silero-vad-model-config.cc
  silero-vad-model.cc
  slice.cc
  spoken-language-identification-impl.cc
  spoken-language-identification.cc
  stack.cc
  symbol-table.cc
  text-utils.cc
  transducer-keyword-decoder.cc
  transpose.cc
  unbind.cc
  utils.cc
  vad-model-config.cc
  vad-model.cc
  voice-activity-detector.cc
  wave-reader.cc
  wave-writer.cc
)

# speaker embedding extractor
list(APPEND sources
  speaker-embedding-extractor-impl.cc
  speaker-embedding-extractor-model.cc
  speaker-embedding-extractor-nemo-model.cc
  speaker-embedding-extractor.cc
  speaker-embedding-manager.cc
)

# audio tagging
list(APPEND sources
  audio-tagging-impl.cc
  audio-tagging-label-file.cc
  audio-tagging-model-config.cc
  audio-tagging.cc
  offline-ced-model.cc
  offline-zipformer-audio-tagging-model-config.cc
  offline-zipformer-audio-tagging-model.cc
)

# punctuation
list(APPEND sources
  offline-ct-transformer-model.cc
  offline-punctuation-impl.cc
  offline-punctuation-model-config.cc
  offline-punctuation.cc
)

if(SHERPA_ONNX_ENABLE_CHECK)
  list(APPEND sources log.cc)
endif()

# Always static build
add_library(sherpa-onnx-core STATIC ${sources})

set_target_properties(
    sherpa-onnx-core
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
)

# Link dependencies
target_link_libraries(sherpa-onnx-core
  kaldi-native-fbank-core
  kaldi-decoder-core
  ssentencepiece_core
)

# Handle ONNX runtime
if(BUILD_SHARED_LIBS AND NOT DEFINED onnxruntime_lib_files)
  target_link_libraries(sherpa-onnx-core onnxruntime)
else()
  target_link_libraries(sherpa-onnx-core ${onnxruntime_lib_files})
endif()

# Linux-specific libraries
target_link_libraries(sherpa-onnx-core -lm)
target_link_libraries(sherpa-onnx-core fstfar fst)

# For Linux ARM32 and ARM64
if(NOT BUILD_SHARED_LIBS)
  target_link_libraries(sherpa-onnx-core -ldl)
endif()

# Thread support
target_link_libraries(sherpa-onnx-core -pthread)

# Build asr-cli only
add_executable(asr-cli asr-cli.cc)
target_link_libraries(asr-cli sherpa-onnx-core)

# Set rpath
target_link_libraries(asr-cli "-Wl,-rpath,${SHERPA_ONNX_RPATH_ORIGIN}/../lib")
target_link_libraries(asr-cli "-Wl,-rpath,${SHERPA_ONNX_RPATH_ORIGIN}/../../../sherpa_onnx/lib")

# Install targets if needed
if(NOT BUILD_SHARED_LIBS)
  install(TARGETS sherpa-onnx-core DESTINATION lib)
endif()

install(TARGETS asr-cli DESTINATION bin)
