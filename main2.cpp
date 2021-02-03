#include <stdio.h>
#include <stdlib.h>
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


const int numberOfParticles = 8;
const float numberOfOctaves = 4;
const float lowFreq = 50;

class Particle {
  public:
    float position;
    float mass;
    float velocity;
};

class ParticleThing {
  public:
    Particle particles[numberOfParticles];

    ParticleThing() {
      for(int i=0; i < numberOfParticles; ++i) {
        particles[i].position = float(rand()) / float(RAND_MAX);
        particles[i].mass = float(rand()) / float(RAND_MAX);
        particles[i].velocity = 0;
      }
    }

    void next(float dt) {
      applyRepulsion(dt);
      applyTopForce(dt);
      applyBottomForce(dt);
      updatePositions(dt);
    }

    void applyRepulsion(float dt, float repulsionConstant = 0.1) { 
      for(int i=0; i < numberOfParticles; ++i) {
        for(int j=i+1; j < numberOfParticles; ++j) {
          float distance = particles[i].position - particles[j].position;
          float impulse = dt * distance * repulsionConstant;
          particles[i].velocity += dt / particles[i].mass;
          particles[j].velocity -= dt / particles[j].mass;
        }
      }
    }

    void updatePositions(float dt) {
      for(int i=0; i < numberOfParticles; ++i)
        particles[i].position += dt * particles[i].velocity;
    }

    void applyTopForce(float dt, float strength=10, float range=0.25) {
      for(int i=0; i < numberOfParticles; ++i) {
        if(particles[i].position > 1) {
          //particles[i].velocity -= (dt * str5ength) * (particles[i].position - (1 - range));
          particles[i].velocity = -abs(particles[i].velocity);
          particles[i].position = 1;
        }
      }
    }

    void applyBottomForce(float dt, float strength=1, float range=0.25) {
      for(int i=0; i < numberOfParticles; ++i) {
        if(particles[i].position < 0) {
          particles[i].position = 0;
          particles[i].velocity = abs(particles[i].velocity);
        }
      }
    }

};


int main() {

  float buffer1[CHUNK_SIZE];
  float buffer2[CHUNK_SIZE];
  float buffer3[CHUNK_SIZE];
  float buffer4[CHUNK_SIZE];
  float buffer5[CHUNK_SIZE];
  float buffer6[CHUNK_SIZE];

  Osc oscs[numberOfParticles];
  Multiplier mult;
  Adder add;
  ParticleThing pt;


  for(int c=0; ; ++c) {
    pt.next(10.0 / SAMPLE_RATE);
    for(int t=0; t < CHUNK_SIZE; ++t)
      buffer2[t] = 0;

    for(int i=0; i < numberOfParticles; ++i) {
      float f = lowFreq * pow(2, pt.particles[i].position * numberOfOctaves);
      oscs[i].process(f, buffer1);
      mult.process(0.1 * pt.particles[i].mass / numberOfParticles, buffer1, buffer1);
      add.process(buffer1, buffer2, buffer2);
    }

    // Send buffer to stdout
    fwrite(buffer2, sizeof(float), CHUNK_SIZE, stdout);
  }

  return 0;
};

// To Run:
// gcc main.cpp && ./a.out | play -t raw -r 44100 -e floating-point -b 32 - 

