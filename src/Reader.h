#pragma once

#include "signalType.h"

class Writer;
class AudioProcess;

class Reader {
public:
  void *bufferptr;
  AudioProcess *owner;
  Writer *connectedTo;
  bool isConstant;
  signalType signalType;

  Reader() {
    connectedTo = nullptr;
    owner = nullptr;
    isConstant = false;
    signalType = nodata;
  }
};
