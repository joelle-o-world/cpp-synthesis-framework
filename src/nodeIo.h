#pragma once

/*
 * This file deals with inlets and outlets on pluggable nodes.
 */

#include "TypedSignalBuffer.h"
#include <iostream>
#include <set>
#include <vector>

enum signalType {
  nodata = 0,
  constant,
  stereo,
  mono,
};

class AudioProcess;
class Inlet;

class Outlet {
  friend Inlet;

public:
  std::set<Inlet *> connectedTo;
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
