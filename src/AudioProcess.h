#pragma once

#include "BufferPool.h"
#include "TypedSignalBuffer.h"
#include "nodeIo.h"
#include <iostream>
#include <set>
#include <string>
#include <vector>

inline void stereoify(MonoBuffer &a, StereoBuffer &b) {
  for (int i = signalChunkSize - 1; i >= 0; --i)
    b[i * 2] = b[i * 2 + 1] = a[i];
};

typedef enum { triggered, done } TriggerState;

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
  static BufferPool<float, 4096> bufferPool;
  const unsigned char numberOfInputs;
  const unsigned char numberOfOutputs;
  TriggerState triggerState;

  std::vector<Inlet> inputs;
  std::vector<Outlet> outputs;

  AudioProcess(unsigned char numberInputs, unsigned char numberOfOutputs)
      : numberOfInputs(numberInputs), numberOfOutputs(numberOfOutputs),
        triggerState(done) {

    // TODO: this looks a bit cryptic, sort it out
    inputs.resize(numberOfInputs);
    outputs.resize(numberOfOutputs);
    for (int i = 0; i < numberInputs; ++i)
      inputs[i].owner = this;
    for (int i = 0; i < numberOfOutputs; ++i)
      outputs[i].owner = this;
  }

  void fire() {
    if (triggerState == triggered) {
      return;
    } else {
      triggerState = triggered;
      for (Inlet &input : inputs)
        input.connectedTo->owner->fire();

      for (Outlet &outlet : outputs) {
        // outlet.buffer->stereo = nullptr;
        outlet.bufferptr = bufferPool.allocate(outlet.deallocationIndex);
        for (Inlet *inlet : outlet.connectedTo)
          inlet->bufferptr = outlet.bufferptr;
        outlet.readers = outlet.connectedTo.size();
      }
      process();
      for (Inlet &inlet : inputs) {
        if (--(inlet.connectedTo->readers) == 0) {
          bufferPool.release(inlet.connectedTo->deallocationIndex);
        }
      }

      triggerState = done;
    }
  }

  /**
   * The function that transforms the audio data. Sub-classes override this.
   */
  virtual void process(){
      // Base class does nothing
  };

  std::set<AudioProcess *> *dependencies() {
    std::set<AudioProcess *> *set = new std::set<AudioProcess *>;
    for (Inlet &inlet : inputs)
      if (inlet.connectedTo)
        set->insert(inlet.connectedTo->owner);
    return set;
  }

  virtual std::string describe() { return "unnamed AudioProcess"; }
};

class UnaryOperationProcess : public AudioProcess {
public:
  UnaryOperationProcess() : AudioProcess(1, 1) {}

public:
  virtual inline void processSample(float &in, float &out) {
    throw "No override defined";
  }

  void process() {
    float *in = (float *)inputs[0].bufferptr;
    float *out = (float *)outputs[0].bufferptr;

    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(out[i], in[i]);
  }
};

class BinaryOperationProcess : public AudioProcess {
public:
  BinaryOperationProcess() : AudioProcess(2, 1) {}

private:
  virtual inline void processSample(float &a, float &b, float &out) {
    // Base class does nothing
  }

public:
  // Two a-rate signals
  void process() override {
    float *a = (float *)inputs[0].bufferptr;
    float *b = (float *)inputs[1].bufferptr;
    float *out = (float *)outputs[0].bufferptr;
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(a[i], b[i], out[i]);
  }
};
