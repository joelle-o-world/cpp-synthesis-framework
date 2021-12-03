
#include <iostream>
#include <portaudio.h>
#include <math.h>

#include "../processes/Osc.h"
#include "../wavetables.h"
#include "../AudioProcess.h"
#include "../processes/arithmetic.h"

#define SAMPLE_RATE (44100)


typedef struct {
  float left_phase;
  float right_phase;
} paTestData;

static paTestData data;

Osc osc;
Clip clip;
Multiply gain;
float f = 100;
float clipamount = 1;


int nCallbacks = 0;

/* This routine will be called by the PortAudio engine when audio is needed.
 * It may called at interrupt level on some machines so don't do anything
 * that could mess up the system like calling malloc() or free().
 */
static int patestCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags, void *userData) {





  /* Cast data passed through stream to our structure. */
  paTestData *data = (paTestData *)userData;
  StereoBuffer *out = (StereoBuffer *)outputBuffer;
  unsigned int i;
  (void)inputBuffer; /* Prevent unused variable warning. */

  osc.process(f/2, *out);

  if(f > 50)
    f -= 16000/ f;
  else
  {
    f = 200;
    osc.flipPhase();
  }

  clipamount *= .999;
  clip.process(*out, clipamount, *out);

  

  return 0;
}

int wulpWulpWulpWulp() {
  initialiseWavetables();


  PaError err = Pa_Initialize();
  if (err != paNoError)
  {
    std::cerr << "Port audio error (at initialisation): " << Pa_GetErrorText(err) << "\n";
    return 1;
  }

  std::cout << "Initialised port audio!\n";

  PaStream *stream;
  /* Open an audio I/O stream. */
  err = Pa_OpenDefaultStream(
      &stream, 0,       /* no input channels */
      2,                /* stereo output */
      paFloat32,        /* 32 bit floating point output */
      SAMPLE_RATE, 2048, /* frames per buffer, i.e. the number
                               of sample frames that PortAudio will
                               request from the callback. Many apps
                               may want to use
                               paFramesPerBufferUnspecified, which
                               tells PortAudio to pick the best,
                               possibly changing, buffer size.*/
      patestCallback,   /* this is your callback function */
      &data);           /*This is a pointer that will be passed to
                                  your callback*/
  if (err != paNoError)
  {
    std::cerr << "Error opening portaudio stream: " << Pa_GetErrorText(err) << "\n";
    return 1;
  }

  std::cout << "Opened a port audio stream!!\n";


  err = Pa_StartStream( stream );
  if( err != paNoError ) {
    std::cerr << "Error starting portaudio stream: " << Pa_GetErrorText(err) << "\n";
    return 1;
  }

  Pa_Sleep(50000);


  err = Pa_StopStream( stream );
  if( err != paNoError ) {
    std::cerr << "Error stopping stream: " << Pa_GetErrorText(err) << "\n";
    return 1;
  }

  err = Pa_Terminate();
  if (err != paNoError)  {
    std::cerr << "Port audio error (at termination): " << Pa_GetErrorText(err) << "\n";
    return 1;
  }

  return 0;
}
