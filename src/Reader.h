#pragma once

#include "signalType.h"

class UntypedWriter;
class Component;

class UntypedReader {
public:
  void *bufferptr;
  Component *owner;
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
