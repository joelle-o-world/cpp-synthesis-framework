#pragma once

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
  private:
    /**
     * The addresses of the audio buffers the process reads from.
     */
    float** inletbuffers;

    /**
     * The addresses of the audio buffers the process writes to.
     */
    float** outletbuffers;

  public:
    /**
     * The function that transforms the audio data. Sub-classes override this.
     */
    virtual void process();
};
