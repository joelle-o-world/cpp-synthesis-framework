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

enum SignalType : unsigned char {
  Stereo32BitFloat = 1,
  Mono32BitFloat,
  ConstantDouble,
  ConstantInt,
  MIDIData
};

struct TypedSignalBuffer {
  SignalType type;

  union {
    StereoBuffer* stereoPCM;
    MonoBuffer* monoPCM;
    float* constant;
    MIDIBuffer* midi;
  };
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
    SignalBuffer** inputs;


    const unsigned char numberOfOutputs;
    /**
     * The addresses of the audio buffers the process writes to.
     */
    SignalBuffer** outputs;

    AudioProcess(unsigned char numberInputs, unsigned char numberOfOutputs)
        : numberOfOutputs(numberOfOutputs), numberOfInputs(numberInputs) {}

    ~AudioProcess() {
      delete inputs;
      delete outputs;
    }

    //IOSignature ioSignature() {
      //unsigned char* signature = (unsigned char*) malloc(numberOfInputs + numberOfOutputs + 1);

      //for(int i=0; i < numberOfInputs; ++i)
        //signature[i] = inputs[i]->type;
      //for(int i=0; i < numberOfOutputs; ++i)
        //signature[i + numberOfInputs] = outputs[i] -> type;
      //signature[numberOfInputs + numberOfOutputs] = 0;

      //return signature;
    //}


    /**
     * The function that transforms the audio data. Sub-classes override this.
     */
    virtual void process() {
      // Base class does nothing
    };
};
