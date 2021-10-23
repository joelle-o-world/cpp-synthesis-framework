#pragma once

#include <vector>

const int signalChunkSize = 2048;
const int sampleRate = 44100;
const float sampleInterval = 1.0 / float(sampleRate);
typedef float SignalBuffer[signalChunkSize];

typedef float StereoBuffer[signalChunkSize * 2];
typedef float MonoBuffer[signalChunkSize];
typedef float MonoConstant;
typedef float StereoConstant;
typedef void* MIDIBuffer; // TODO: Future

inline void stereoify(MonoBuffer& a, StereoBuffer& b) {
  for(int i=signalChunkSize-1; i >= 0; --i) 
    b[i*2] = b[i*2+1] = a[i];
};

enum SignalType : unsigned char {
  Stereo = 1,
  Mono,
  Constant,
  MIDIData
};

struct TypedSignalBuffer {
  SignalType type;

  union {
    StereoBuffer* stereo;
    MonoBuffer* mono;
    float* constant;
    MIDIBuffer* midi;
  } ;
};

typedef unsigned char *IOSignature;

/**
 * Base class for audio processes.
 *
 * The sub classes of AudioProcess implement the actual transformation of audio
 * buffers. This is done by overiding the virtual `process()` method. These
 * classes also contain memory addresses of the buffers they read from write
 * too. They may also contain internal state data that needs to carry forward
 * accross cycles.
 *
 * AudioProcess sub-classes should be extremely minimal and do not contain some
 * pieces of information that may be surprising. Number of inlets, outlets and
 * the size and format of their buffers is the domain of the AudioProcessCoordinator
 * subclasses.
 */
class AudioProcess {
  public:
    const unsigned char numberOfInputs;

    /**
     * The addresses of the audio buffers the process reads from.
     */
    TypedSignalBuffer** inputs;


    const unsigned char numberOfOutputs;
    /**
     * The addresses of the audio buffers the process writes to.
     */
    TypedSignalBuffer** outputs;

    AudioProcess(unsigned char numberInputs, unsigned char numberOfOutputs)
        : numberOfInputs(numberInputs),numberOfOutputs(numberOfOutputs)  {
      inputs = new TypedSignalBuffer*[numberOfInputs];
      outputs = new TypedSignalBuffer*[numberOfOutputs];
    }

    ~AudioProcess() {
      delete inputs;
      delete outputs;
    }


    /**
     * The function that transforms the audio data. Sub-classes override this.
     */
    virtual void process() {
      // Base class does nothing
    };
};

class UnaryOperationProcess : public AudioProcess {
public:
  UnaryOperationProcess() : AudioProcess(1, 1) {}

  void process() override {
    TypedSignalBuffer &in = *inputs[0], out = *outputs[0];
    if (in.type == Stereo && out.type == Stereo)
      process(*in.stereo, *out.stereo);
    else
      throw "Unexpected signal types";
  }

  virtual inline void processSample(float &in, float &out) {
    // Base class does nothing
  }

  void process(StereoBuffer &in, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(out[i], in[i]);
  }
};

class BinaryOperationProcess : public AudioProcess {

private:
  virtual inline void processSample(float &a, float &b, float &out) {
    // Base class does nothing
  }

public:
  BinaryOperationProcess() : AudioProcess(2, 1) {}

  void process() override {

    TypedSignalBuffer &a = *inputs[0];
    TypedSignalBuffer &b = *inputs[1];
    TypedSignalBuffer &out = *outputs[0];

    if (out.type == Stereo) {
      if (a.type == Stereo && b.type == Stereo)
        process(*a.stereo, *b.stereo, *out.stereo);

      else if (a.type == Stereo && b.type == Constant)
        process(*a.stereo, *b.constant, *out.stereo);

      else if (a.type == Constant && b.type == Stereo)
        process(*a.constant, *b.stereo, *out.stereo);

      else if (a.type == Constant && b.type == Constant)
        process(*a.constant, *b.constant, *out.stereo);

      else
        throw "unexpected input signal types";

    } else
      throw "output must be stereo";
  }

  // Two a-rate signals
  void process(StereoBuffer &a, StereoBuffer &b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a[i], b[i], out[i]);
  }

  // a is a-rate, b is k-rate
  void process(StereoBuffer &a, float &b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a[i] , b, out[i]);
  }

  // a is k-rate, b is a-rate
  void process(float &a, StereoBuffer &b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a , b[i], out[i] );
  }

  // two k-rate signals
  void process(float &a, float &b, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a, b, out[i]);
  }
};
