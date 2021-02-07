#include <stdio.h>
#include <math.h>
#include <vector>

#define PI 3.14159265
#define SAMPLE_RATE 44100

static const int CHUNK_SIZE = 256;
typedef float SignalBuffer[CHUNK_SIZE];
const float phiOverSr = 2.0 * PI / SAMPLE_RATE ;
const float PHI = 2.0 * PI;


class AudioComponent {
  public:
    static const int numberOfInputs;
    static const int numberOfOutputs;
    //vector<float*> inputs;
    //vector<float*> outputs;

    float** inputBuffers;
    float** outputBuffers;

    virtual void process() {
      // DO AUDIO PROCESSING HERE!
      //printf("Hello\n");
    }
};

class Osc: public AudioComponent {
  public:
    float frequency;
    float phase;
    //float* out;

    static const int numberOfInputs = 0;
    static const int numberOfOutputs = 1;
    float* inputBuffers[0];
    float* outputBuffers[1];

    void process() {
      const float dPhasePerSample = PHI * frequency / SAMPLE_RATE;
      float* out = outputBuffers[0];
      for(int i=0; i < CHUNK_SIZE; i++) {
        phase = fmod(phase + dPhasePerSample, PHI);
        *(out++) = sin(phase);
      }
    }
};

class Mixer: public AudioComponent {
  public:
    //float* a;
    //float* b;
    //float* out;

    static const int numberOfInputs = 2;
    static const int numberOfOutputs = 1;
    float* inputBuffers[2];
    float* outputBuffers[1];

    void process() {
      float* a = inputBuffers[0];
      float* b = inputBuffers[1];
      float* out = outputBuffers[0];
      for(int i=0; i < CHUNK_SIZE; ++i) {
        *(out++) = (*(a++) + *(b++)) / 2;
      }
    }
};

class Adder: public AudioComponent {
  public:
    static const int numberOfInputs = 2;
    static const int numberOfOutputs = 1;
    float* inputBuffers[2];
    float* outputBuffers[1];

    void process() {
      float* a = inputBuffers[0];
      float* b = inputBuffers[1];
      float* out = outputBuffers[0];
      for(int i=0; i < CHUNK_SIZE; ++i) {
        out[i] = (a[i] + b[i]);
      }

    }
};


//class Multiplier: public AudioComponent {
  //public:
    //static const int numberOfInputs = 2;
    //static const int numberOfOutputs = 1;
    //float* inputs[2];
    //float* outputs[1];

    //void process() {
      //float* a = inputs[0];
      //float* b = inputs[1];
      //float* out = outputs[0];
      //for(int i=0; i < CHUNK_SIZE; ++i) {
        //out[i] = (a[i] * b[i]);
      //}
    //}
//};

//class Powerer: public AudioComponent {
  //public:
    //static const int numberOfInputs = 2;
    //static const int numberOfOutputs = 1;
    //float* inputs[2];
    //float* outputs[1];

    //void process() {
      //float* a = inputs[0];
      //float* b = inputs[1];
      //float* out = outputs[0];
      //for(int i=0; i < CHUNK_SIZE; ++i) {
        //out[i] = pow(a[i], b[i]);
      //}
    //}
//};


//class SemitoneToFrequency;
//class Floor;
//class Granulator;

int main() {
  float buffer1[CHUNK_SIZE];
  float buffer2[CHUNK_SIZE];

  Osc osc1;
  osc1.frequency = 200;
  osc1.outputBuffers[0] = buffer1;

  Osc osc2;
  osc2.frequency = 440;
  osc2.outputBuffers[0] = buffer2;

  Mixer mixer1;
  mixer1.inputBuffers[0] = buffer1;
  mixer1.inputBuffers[1] = buffer2;
  mixer1.outputBuffers[0] = buffer1;
  

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
