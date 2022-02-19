#pragma once

#include "signalType.h"

class Outlet;
class AudioProcess;

class Reader {
public:
  void *bufferptr;
  AudioProcess *owner;
  Outlet *connectedTo;
  bool isConstant;
  signalType signalType;

  Reader() {
    connectedTo = nullptr;
    owner = nullptr;
    isConstant = false;
    signalType = nodata;
  }
};
