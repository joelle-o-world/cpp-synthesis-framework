#pragma once

#include "../AudioProcess.h"
#include "../AudioProcessCoordinator.h"

class _Add : public AudioProcess {
public:
  SignalBuffer* a;
  SignalBuffer* b;
  SignalBuffer* out;
  void process() override {
    for(int i=0; i < signalChunkSize; ++i) 
      (*out)[i] = (*a)[i] + (*b)[i];
  }
};
