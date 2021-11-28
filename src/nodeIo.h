#pragma once

/*
 * This file deals with inlets and outlets on pluggable nodes.
 */

#include "TypedSignalBuffer.h"

class AudioProcess;

class Inlet {
public:
  TypedSignalBuffer buffer;
  AudioProcess *owner;
};

class Outlet {
public:
  TypedSignalBuffer buffer;
  AudioProcess *owner;
};

void connect(Outlet &outlet, Inlet &inlet);
