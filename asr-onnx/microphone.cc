// asr-onnx/microphone.cc
//
 

#include "asr-onnx/microphone.h"

#include <stdio.h>
#include <stdlib.h>

#include "portaudio.h"  // NOLINT

namespace sherpa_onnx {

Microphone::Microphone() {
  PaError err = Pa_Initialize();
  if (err != paNoError) {
    fprintf(stderr, "portaudio error: %s\n", Pa_GetErrorText(err));
    exit(-1);
  }
}

Microphone::~Microphone() {
  PaError err = Pa_Terminate();
  if (err != paNoError) {
    fprintf(stderr, "portaudio error: %s\n", Pa_GetErrorText(err));
    exit(-1);
  }
}

}  // namespace sherpa_onnx
