#pragma once

#include "Process.h"

class Process;

class Mix: public Process {
  public:
    // Constructors
    Mix();

    // IO
    Inlet a;
    Inlet b;
    Outlet out;

    // Processing 
    void process() ;
};
