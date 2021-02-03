#include <stdio.h>
#include <math.h>
#define CHUNK_SIZE 256

#define SAMPLE_RATE 44100
#define PI 3.14159265

const float phiOverSr = 2.0 * PI / SAMPLE_RATE ;
const float PHI = 2.0 * PI;

class Osc {
  private:
    float phase;

  public:
    void process(float frequency, float* out) {
      const float dPhasePerSample = PHI * frequency / SAMPLE_RATE;
      for(int i=0; i < CHUNK_SIZE; i++) {
        phase = fmod(phase + dPhasePerSample, PHI);
        out[i] = sin(phase);
      }
    }

    void process(float* frequency, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i) {
        phase = fmod(phase + frequency[i] * phiOverSr, PHI);
        out[i] = sin(phase);
      }
    }

    void resetPhase() {
      phase = 0;
    }
};

class Mixer {
  public:
    void process(float* a, float* b, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = (a[i] + b[i]) / 2;
    }
};

class Adder {
  public: 
    void process(float* a, float* b, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = a[i] + b[i];
    }

    void process(float a, float* b, float* out) {
      for(int i=0; i<CHUNK_SIZE; ++i)
        out[i] = a + b[i];
    }

    void process(float* a, float b, float* out) {
      for(int i=0; i<CHUNK_SIZE; ++i)
        out[i] = a[i] + b;
    }
};

class Multiplier {
  public:
    void process(float* a, float* b, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = a[i] * b[i];
    }

    void process(float a, float* b, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = a * b[i];
    }

    void process(float *a, float b, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = a[i] * b;
    }
};

class Powerer {
  public:
    void process(float* a, float* b, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = pow(a[i], b[i]);
    }

    void process(float a, float* b, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = pow(a, b[i]);
    }

    void process(float* a, float b, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = pow(a[i], b);
    }
};

class SemitoneToFrequency {
  Multiplier multiplier1;
  Powerer pow1;

  public:
    void process(float* in, float* out) {
      multiplier1.process(in, 1.0/12.0, out);
      pow1.process(2, out, out);
    }
};

class Floor {
  public:
    void process(float* in, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = round(in[i]);
    }
};

class Granulator {
  public:
    void process(float* in, float* interval, float* offset, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = floor((in[i] - offset[i]) / interval[i]) * interval[i] + offset[i];
    }

    void process(float* in, float interval, float* offset, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = floor((in[i] - offset[i]) / interval) * interval + offset[i];
    }

    void process(float* in, float* interval, float offset, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = floor((in[i] - offset) / interval[i]) * interval[i] + offset;
    }
    void process(float* in, float interval, float offset, float* out) {
      for(int i=0; i < CHUNK_SIZE; ++i)
        out[i] = floor((in[i] - offset) / interval) * interval + offset;
    }
};




int main() {

  float buffer1[CHUNK_SIZE];
  float buffer2[CHUNK_SIZE];
  float buffer3[CHUNK_SIZE];
  float buffer4[CHUNK_SIZE];
  float buffer5[CHUNK_SIZE];
  float buffer6[CHUNK_SIZE];

  Osc osc1, lfo1;
  Multiplier mult;
  Adder add;
  SemitoneToFrequency st2f;
  Floor fl;
  Granulator gran;

  for(int c=0; ; ++c) {
    lfo1.process(1, buffer1);
    mult.process(6.0, buffer1, buffer1);
    gran.process(buffer1, 2.0, 0.0, buffer1);
    st2f.process(buffer1, buffer1);

    mult.process(buffer1, 300, buffer1);

    osc1.process(buffer1, buffer1);

    // Send buffer to stdout
    fwrite(buffer1, sizeof(float), CHUNK_SIZE, stdout);
  }

  return 0;
};

// To Run:
// gcc main.cpp && ./a.out | play -t raw -r 44100 -e floating-point -b 32 - 

