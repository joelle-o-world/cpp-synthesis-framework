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
  TypedSignalBuffer *buffer;
  AudioProcess *owner;
};

class Inlet {
public:
  TypedSignalBuffer *buffer;
  AudioProcess *owner;
  Outlet *connectedTo;
  bool isConstant;

  Inlet() {
    connectedTo = nullptr;
    owner = nullptr;
    isConstant = false;
  }
};
