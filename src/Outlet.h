#pragma once

#include "./Reader.h"
#include "AudioProcess.h"
#include <set>

class AudioProcess;

class Outlet {
  friend Reader;

public:
  std::set<Reader *> connectedTo;
  void *bufferptr;
  AudioProcess *owner;
  int deallocationIndex;
  signalType signalType;
  /// The number of inputs waiting to read this outlet's buffer.
  int readers;
  Outlet() {
    readers = 0;
    deallocationIndex = -1;
    signalType = nodata;
  }
};
