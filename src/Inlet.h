#pragma once

#include "signalType.h"

class Outlet;
class AudioProcess;

class Inlet {
public:
  void *bufferptr;
  AudioProcess *owner;
  Outlet *connectedTo;
  bool isConstant;
  signalType signalType;

  Inlet() {
    connectedTo = nullptr;
    owner = nullptr;
    isConstant = false;
    signalType = nodata;
  }
};
