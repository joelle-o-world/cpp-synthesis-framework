#pragma once

#include "Outlet.h"
#include "Process.h"

class Outlet;
class Process;

class Inlet {
public:
  float* buffer;
  Process* owner;
  Outlet* connectedTo;
  bool isConnected = false;
  bool dontWriteInPlace = false;
};
