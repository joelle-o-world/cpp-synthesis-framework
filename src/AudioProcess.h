#pragma once

#include "TypedSignalBuffer.h"
#include "nodeIo.h"
#include <vector>

inline void stereoify(MonoBuffer &a, StereoBuffer &b) {
  for (int i = signalChunkSize - 1; i >= 0; --i)
    b[i * 2] = b[i * 2 + 1] = a[i];
};

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
 * the size and format of their buffers is the domain of the
 * AudioProcessCoordinator subclasses.
 */
class AudioProcess {
public:
  const unsigned char numberOfInputs;
  const unsigned char numberOfOutputs;

  std::vector<Inlet> inputs;
  std::vector<Outlet> outputs;

  AudioProcess(unsigned char numberInputs, unsigned char numberOfOutputs)
      : numberOfInputs(numberInputs), numberOfOutputs(numberOfOutputs) {

    // TODO: this looks a bit cryptic, sort it out
    inputs.resize(numberOfInputs);
    outputs.resize(numberOfOutputs);
  }

  /**
   * The function that transforms the audio data. Sub-classes override this.
   */
  virtual void processStatefully(){
      // Base class does nothing
  };
};

class UnaryProcess : public AudioProcess {
public:
  UnaryProcess() : AudioProcess(1, 1) {}

  void processStatefully() override {
    TypedSignalBuffer &in = *(inputs[0].buffer);
    TypedSignalBuffer &out = *(outputs[0].buffer);
    if (in.type == Stereo && out.type == Stereo)
      process(*in.stereo, *out.stereo);
    else
      throw "Unexpected signal types";
  }

  virtual void process(StereoBuffer &in, StereoBuffer &out) {
    throw "No override defined";
  }
};

class UnaryOperationProcess : public UnaryProcess {
public:
  virtual inline void processSample(float &in, float &out) {
    throw "No override defined";
  }

  void process(StereoBuffer &in, StereoBuffer &out) {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(out[i], in[i]);
  }
};

class BinaryProcess : public AudioProcess {
public:
  BinaryProcess() : AudioProcess(2, 1) {}

  void processStatefully() override {

    TypedSignalBuffer &a = *(inputs[0].buffer);
    TypedSignalBuffer &b = *inputs[1].buffer;
    TypedSignalBuffer &out = *outputs[0].buffer;

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
  virtual void process(StereoBuffer &a, StereoBuffer &b, StereoBuffer &out) {
    throw "No override defined";
  }

  // a is a-rate, b is k-rate
  virtual void process(StereoBuffer &a, float b, StereoBuffer &out) {
    throw "No override defined";
  }

  // a is k-rate, b is a-rate
  virtual void process(float a, StereoBuffer &b, StereoBuffer &out) {
    throw "No override defined";
  }

  // two k-rate signals
  virtual void process(float a, float b, StereoBuffer &out) {
    throw "No override difined";
  }
};
class BinaryOperationProcess : public BinaryProcess {

private:
  virtual inline void processSample(float &a, float &b, float &out) {
    // Base class does nothing
  }

public:
  // Two a-rate signals
  void process(StereoBuffer &a, StereoBuffer &b, StereoBuffer &out) override {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a[i], b[i], out[i]);
  }

  // a is a-rate, b is k-rate
  void process(StereoBuffer &a, float b, StereoBuffer &out) override {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a[i], b, out[i]);
  }

  // a is k-rate, b is a-rate
  void process(float a, StereoBuffer &b, StereoBuffer &out) override {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a, b[i], out[i]);
  }

  // two k-rate signals
  void process(float a, float b, StereoBuffer &out) override {
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a, b, out[i]);
  }
};
