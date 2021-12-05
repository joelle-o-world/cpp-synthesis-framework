#include "AudioProcess.h"

AudioProcess::AudioProcess(unsigned char numberOfInputs,
                           unsigned char numberOfOutputs)
    : numberOfInputs(numberOfInputs), numberOfOutputs(numberOfOutputs) {

  // TODO: this looks a bit cryptic, sort it out
  inputs.resize(numberOfInputs);
  outputs.resize(numberOfOutputs);
  for (int i = 0; i < numberOfInputs; ++i)
    inputs[i].owner = this;
  for (int i = 0; i < numberOfOutputs; ++i)
    outputs[i].owner = this;
}

void AudioProcess::processStatefully(){
    // Base class does nothing
};

std::set<AudioProcess *> *AudioProcess::dependencies() {
  std::set<AudioProcess *> *set = new std::set<AudioProcess *>;
  for (Inlet &inlet : inputs)
    if (inlet.connectedTo)
      set->insert(inlet.connectedTo->owner);
  return set;
}

std::string AudioProcess::describe() { return "unnamed AudioProcess"; }
