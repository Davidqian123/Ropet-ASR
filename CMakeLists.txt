cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(asr-onnx)

set(ROPET_ASR_VERSION "1.10.46")

option(BUILD_SHARED_LIBS "Whether to build shared libraries" OFF)
option(SHERPA_ONNX_USE_PRE_INSTALLED_ONNXRUNTIME_IF_AVAILABLE "True to use pre-installed onnxruntime if available" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(SHERPA_ONNX_RPATH_ORIGIN "$ORIGIN")
set(CMAKE_INSTALL_RPATH ${SHERPA_ONNX_RPATH_ORIGIN})
set(CMAKE_BUILD_RPATH ${SHERPA_ONNX_RPATH_ORIGIN})

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No CMAKE_BUILD_TYPE given, default to Release")
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS}")

if(BUILD_SHARED_LIBS)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ version to be used.")
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ Standard version: ${CMAKE_CXX_STANDARD}")

include(CheckIncludeFileCXX)

check_include_file_cxx(cxxabi.h SHERPA_ONNX_HAVE_CXXABI_H)
check_include_file_cxx(execinfo.h SHERPA_ONNX_HAVE_EXECINFO_H)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(NOT BUILD_SHARED_LIBS)
  message(STATUS "Link libstdc++ statically")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

endif()

include(kaldi-native-fbank)
include(kaldi-decoder)
include(onnxruntime)
include(simple-sentencepiece)
set(ONNXRUNTIME_DIR ${onnxruntime_SOURCE_DIR})
message(STATUS "ONNXRUNTIME_DIR: ${ONNXRUNTIME_DIR}")

add_subdirectory(asr-onnx)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")