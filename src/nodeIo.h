#pragma once

/*
 * This file deals with inlets and outlets on pluggable nodes.
 */

#include "TypedSignalBuffer.h"
#include <iostream>
#include <set>
#include <vector>

class AudioProcess;
class Inlet;

class Outlet {
  friend Inlet;

public:
  std::set<Inlet *> connectedTo;
  void *bufferptr;
  AudioProcess *owner;
  int deallocationIndex;
  /// The number of inputs waiting to read this outlet's buffer.
  int readers;
};

class Inlet {
public:
  void *bufferptr;
  AudioProcess *owner;
  Outlet *connectedTo;
  bool isConstant;

  Inlet() {
    connectedTo = nullptr;
    owner = nullptr;
    isConstant = false;
  }
};
