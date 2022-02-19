#pragma once

#include "BufferPool.h"
#include "Reader.h"
#include "TypedSignalBuffer.h"
#include "Writer.h"
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

  std::vector<Reader> inputs;
  std::vector<Writer> outputs;

  AudioProcess(std::vector<signalType> inputTypes,
               std::vector<signalType> outputTypes);

  void fire() {
    if (triggerState == triggered) {
      return;
    } else {
      triggerState = triggered;
      for (Reader &input : inputs)
        input.connectedTo->owner->fire();

      for (Writer &outlet : outputs) {
        // outlet.buffer->stereo = nullptr;
        outlet.bufferptr = bufferPool.allocate(outlet.deallocationIndex);
        for (Reader *inlet : outlet.connectedTo)
          inlet->bufferptr = outlet.bufferptr;
        outlet.readers = outlet.connectedTo.size();
      }
      process();
      for (Reader &inlet : inputs) {
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
    for (Reader &inlet : inputs)
      if (inlet.connectedTo)
        set->insert(inlet.connectedTo->owner);
    return set;
  }

  virtual std::string describe() { return "unnamed AudioProcess"; }
};
