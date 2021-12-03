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

  void connect(Outlet &outlet) {
    disconnect();
    connectedTo = &outlet;
    outlet.connectedTo.insert(this);
  }

  void connect(float constant) {
    isConstant = true;
    buffer = new TypedSignalBuffer;
    buffer->type = Constant;
    buffer->constant = new float(constant);
  }

  void disconnect() {
    isConstant = false;
    if (connectedTo)
      connectedTo->connectedTo.erase(this);
    connectedTo = nullptr;
  }

  void healthCheck() {
    if (!isConstant && !connectedTo) {
      std::cerr << "Unhealthy Inlet!\n";
      throw 1;
    }
  }
};
