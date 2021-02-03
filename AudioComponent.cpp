#include <stdio.h>
#include <math.h>
#define PI 3.14159265
#define SAMPLE_RATE 44100

static const int CHUNK_SIZE = 256;
typedef float SignalBuffer[CHUNK_SIZE];
const float phiOverSr = 2.0 * PI / SAMPLE_RATE ;
const float PHI = 2.0 * PI;


class AudioComponent {
  public:
    virtual void process() {
      // DO AUDIO PROCESSING HERE!
      //printf("Hello\n");
    }
};

class Osc: public AudioComponent {
  public:
    float frequency;
    float phase;
    float* out;

    void process() {
      const float dPhasePerSample = PHI * frequency / SAMPLE_RATE;
      for(int i=0; i < CHUNK_SIZE; i++) {
        phase = fmod(phase + dPhasePerSample, PHI);
        out[i] = sin(phase);
      }
    }
};

class Mixer: public AudioComponent {
  public:
    float* a;
    float* b;
    float* out;

    void process() {
      for(int i=0; i < CHUNK_SIZE; ++i) {
        out[i] = (a[i] + b[i]) / 2;
      }
    }
};

int main() {
  float buffer1[CHUNK_SIZE];
  float buffer2[CHUNK_SIZE];

  Osc osc1;
  osc1.frequency = 200;
  osc1.out = buffer1;

  Osc osc2;
  osc2.frequency = 440;
  osc2.out = buffer2;

  Mixer mixer1;
  mixer1.a = buffer1;
  mixer1.b = buffer2;
  mixer1.out = buffer1;

  AudioComponent* processOrder[3] = {&osc1, &osc2, &mixer1};

  for(int c=0; ; ++c) {
    for(int i=0; i < 3; ++i) {
      processOrder[i]->process();
    }

    // Send buffer to stdout
    fwrite(buffer1, sizeof(float), CHUNK_SIZE, stdout);
  }

  return 0;
}
