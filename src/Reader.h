#pragma once

#include "signalType.h"

class UntypedWriter;
class AudioProcess;

class UntypedReader {
public:
  void *bufferptr;
  AudioProcess *owner;
  UntypedWriter *connectedTo;
  bool isConstant;
  signalType signalType;

  UntypedReader() {
    connectedTo = nullptr;
    owner = nullptr;
    isConstant = false;
    signalType = nodata;
  }
};

template <typename BufferType> class Reader : public UntypedReader {
public:
  BufferType &data() { return *(BufferType *)bufferptr; }
};
