#pragma once

#include "./Reader.h"
#include "Component.h"
#include <set>

class Component;

class UntypedWriter {
  friend UntypedReader;

public:
  std::set<UntypedReader *> connectedTo;
  void *bufferptr;
  Component *owner;
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
