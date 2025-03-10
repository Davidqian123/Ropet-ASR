// asr-onnx/asr-cli.cc
//
 

#include <stdio.h>

#include <chrono>  // NOLINT
#include <string>
#include <vector>

#include "asr-onnx/offline-recognizer.h"
#include "asr-onnx/parse-options.h"
#include "asr-onnx/wave-reader.h"

int main(int32_t argc, char *argv[]) {
  const char *kUsageMessage = R"usage(
Usage:

  ./asr-cli \
    --tokens=/path/to/tokens.txt \
    --encoder=/path/to/encoder.onnx \
    --decoder=/path/to/decoder.onnx \
    --joiner=/path/to/joiner.onnx \
    --num-threads=1 \
    --decoding-method=greedy_search \
    /path/to/test.wav

)usage";

  sherpa_onnx::ParseOptions po(kUsageMessage);
  sherpa_onnx::OfflineRecognizerConfig config;

  po.Register("tokens", &config.model_config.tokens, "Path to tokens.txt");
  po.Register("encoder", &config.model_config.transducer.encoder_filename, "Path to encoder.onnx");
  po.Register("decoder", &config.model_config.transducer.decoder_filename, "Path to decoder.onnx");
  po.Register("joiner", &config.model_config.transducer.joiner_filename, "Path to joiner.onnx");
  po.Register("num-threads", &config.model_config.num_threads, "Number of threads to run the model");
  po.Register("decoding-method", &config.decoding_method, "Decoding method: greedy_search or modified_beam_search");

  po.Read(argc, argv);
  if (po.NumArgs() < 1) {
    fprintf(stderr, "Error: Please provide at least 1 wave file.\n\n");
    po.PrintUsage();
    exit(EXIT_FAILURE);
  }

  // fprintf(stderr, "%s\n", config.ToString().c_str());

  if (!config.Validate()) {
    fprintf(stderr, "Errors in config!\n");
    return -1;
  }

  fprintf(stderr, "Creating recognizer ...\n");
  sherpa_onnx::OfflineRecognizer recognizer(config);

  fprintf(stderr, "Started\n");
  const auto begin = std::chrono::steady_clock::now();

  std::vector<std::unique_ptr<sherpa_onnx::OfflineStream>> ss;
  std::vector<sherpa_onnx::OfflineStream *> ss_pointers;
  float duration = 0;
  for (int32_t i = 1; i <= po.NumArgs(); ++i) {
    const std::string wav_filename = po.GetArg(i);
    int32_t sampling_rate = -1;
    bool is_ok = false;
    const std::vector<float> samples =
        sherpa_onnx::ReadWave(wav_filename, &sampling_rate, &is_ok);
    if (!is_ok) {
      fprintf(stderr, "Failed to read '%s'\n", wav_filename.c_str());
      return -1;
    }
    duration += samples.size() / static_cast<float>(sampling_rate);

    auto s = recognizer.CreateStream();
    s->AcceptWaveform(sampling_rate, samples.data(), samples.size());

    ss.push_back(std::move(s));
    ss_pointers.push_back(ss.back().get());
  }

  recognizer.DecodeStreams(ss_pointers.data(), ss_pointers.size());

  const auto end = std::chrono::steady_clock::now();

  fprintf(stderr, "Done!\n\n");
  for (int32_t i = 1; i <= po.NumArgs(); ++i) {
    fprintf(stderr, "%s\n%s\n----\n", po.GetArg(i).c_str(),
            ss[i - 1]->GetResult().text.c_str());
  }

  float elapsed_seconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
          .count() /
      1000.;

  fprintf(stderr, "num threads: %d\n", config.model_config.num_threads);
  fprintf(stderr, "decoding method: %s\n", config.decoding_method.c_str());
  if (config.decoding_method == "modified_beam_search") {
    fprintf(stderr, "max active paths: %d\n", config.max_active_paths);
  }

  fprintf(stderr, "Elapsed seconds: %.3f s\n", elapsed_seconds);
  float rtf = elapsed_seconds / duration;
  fprintf(stderr, "Real time factor (RTF): %.3f / %.3f = %.3f\n",
          elapsed_seconds, duration, rtf);

  return 0;
}
