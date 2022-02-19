#include "AudioProcess.h"

AudioProcess::AudioProcess(std::vector<signalType> inputTypes,
                           std::vector<signalType> outputTypes)
    : numberOfInputs(inputTypes.size()), numberOfOutputs(outputTypes.size()),
      triggerState(done) {

  // Initialise the inlets
  inputs.resize(numberOfInputs);
  outputs.resize(numberOfOutputs);
  for (int i = 0; i < numberOfInputs; ++i) {
    inputs[i].signalType = inputTypes[i];
    inputs[i].owner = this;
  }
  for (int i = 0; i < numberOfOutputs; ++i) {
    outputs[i].signalType = outputTypes[i];
    outputs[i].owner = this;
  }
}

BufferPool<float, 4096> AudioProcess::bufferPool;
