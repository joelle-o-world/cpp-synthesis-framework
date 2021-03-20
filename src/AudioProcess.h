#pragma once

const int signalChunkSize = 256;
const int sampleRate = 44100;
const float sampleInterval = 1.0 / float(sampleRate);
typedef float SignalBuffer[signalChunkSize];

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
 *
 */
class AudioProcess {
  public:
    /**
     * The addresses of the audio buffers the process reads from.
     */
    //SignalBuffer** inletbuffers;

    /**
     * The addresses of the audio buffers the process writes to.
     */
    //SignalBuffer** outletbuffers;



    /**
     * The function that transforms the audio data. Sub-classes override this.
     */
    virtual void process() {
      // Base class does nothing
    };
};
