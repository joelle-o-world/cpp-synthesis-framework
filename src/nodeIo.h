#pragma once

/*
 * This file deals with inlets and outlets on pluggable nodes.
 */

#include "TypedSignalBuffer.h"
#include <set>
#include <vector>

class AudioProcess;
class Inlet;

class Outlet {
  friend Inlet;

private:
  std::set<Inlet *> connectedTo;

public:
  TypedSignalBuffer *buffer;
  AudioProcess *owner;
};

class Inlet {
public:
  TypedSignalBuffer *buffer;
  AudioProcess *owner;
  Outlet *connectedTo;

  void connect(Outlet &outlet) {
    disconnect();
    connectedTo = &outlet;
    outlet.connectedTo.insert(this);
  }

  void disconnect() {
    connectedTo->connectedTo.erase(this);
    connectedTo = nullptr;
  }
};
