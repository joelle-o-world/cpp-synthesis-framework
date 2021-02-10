#pragma once

#include <string>

#include "Outlet.h"
#include "Process.h"

class Outlet;
class Process;

class Inlet {
  public:
    float* buffer;
    Process* owner = NULL;
    Outlet* connectedTo;
    bool isConnected = false;
    bool isFree();
    bool dontWriteInPlace = false;
    bool isConnectedTo(Outlet* outlet);

    // Get the position in its owners `inlets` list
    int index();
    std::string name();
};
