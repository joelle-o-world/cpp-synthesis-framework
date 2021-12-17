
#include <iostream>
#include <math.h>
#include <portaudio.h>

#include "AudioProcess.h"
#include "Circuit.h"
#include "TypedSignalBuffer.h"
#include "processes/Osc.h"
#include "processes/arithmetic.h"
#include "wavetables.h"

#define SAMPLE_RATE (44100)

typedef struct {
  Outlet *output;
} paTestData;

static paTestData data;

int nCallbacks = 0;

static int patestCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags, void *userData) {

  /* Cast data passed through stream to our structure. */
  paTestData *data = (paTestData *)userData;

  float *out = (float *)outputBuffer;
  unsigned int i;
  (void)inputBuffer; /* Prevent unused variable warning. */

  data->output->owner->fire();

  copyData((float *)data->output->bufferptr, out);

  return 0;
}

int play(Outlet &outlet) {
  // circuit.prepare();
  data = {&outlet};
  PaError err = Pa_Initialize();
  if (err != paNoError) {
    std::cerr << "Port audio error (at initialisation): "
              << Pa_GetErrorText(err) << "\n";
    return 1;
  }

  // std::cout << "Initialised port audio!\n";

  PaStream *stream;
  /* Open an audio I/O stream. */
  err = Pa_OpenDefaultStream(
      &stream, 0,       /* no input channels */
      2,                /* stereo output */
      paFloat32,        /* 32 bit floating point output */
      sampleRate, 2048, /* frames per buffer, i.e. the number
                               of sample frames that PortAudio will
                               request from the callback. Many apps
                               may want to use
                               paFramesPerBufferUnspecified, which
                               tells PortAudio to pick the best,
                               possibly changing, buffer size.*/
      patestCallback,   /* this is your callback function */
      &data);           /*This is a pointer that will be passed to
                                  your callback*/
  if (err != paNoError) {
    std::cerr << "Error opening portaudio stream: " << Pa_GetErrorText(err)
              << "\n";
    return 1;
  }

  // std::cout << "Opened a port audio stream!!\n";

  err = Pa_StartStream(stream);
  if (err != paNoError) {
    std::cerr << "Error starting portaudio stream: " << Pa_GetErrorText(err)
              << "\n";
    return 1;
  }

  Pa_Sleep(5000);

  std::cout << "done!\n";
  err = Pa_StopStream(stream);
  if (err != paNoError) {
    std::cerr << "Error stopping stream: " << Pa_GetErrorText(err) << "\n";
    return 1;
  }

  err = Pa_Terminate();
  if (err != paNoError) {
    std::cerr << "Port audio error (at termination): " << Pa_GetErrorText(err)
              << "\n";
    return 1;
  }

  return 0;
}
