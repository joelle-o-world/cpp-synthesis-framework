#pragma once

/*
 *
 * This file deals with inlets and outlets on pluggable nodes.
 *
 */

#include "AudioProcess.h"
#include "TypedSignalBuffer.h"

class AudioProcess;

class Inlet {
  TypedSignalBuffer buffer;
  AudioProcess *owner;
};

class Outlet {
  TypedSignalBuffer *buffer;
  AudioProcess *owner;
};
