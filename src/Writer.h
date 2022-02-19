#pragma once

#include "./Reader.h"
#include "AudioProcess.h"
#include <set>

class AudioProcess;

class UntypedWriter {
  friend UntypedReader;

public:
  std::set<UntypedReader *> connectedTo;
  void *bufferptr;
  AudioProcess *owner;
  int deallocationIndex;
  signalType signalType;
  /// The number of inputs waiting to read this outlet's buffer.
  int readers;
  UntypedWriter() {
    readers = 0;
    deallocationIndex = -1;
    signalType = nodata;
  }
};

template <typename T> class Writer : public UntypedWriter {
public:
  T &data() { return *(T *)bufferptr; }

  int chunkSize() { return sizeof(T); }
};
