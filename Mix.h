#pragma once

#include "Process.h"

class Process;

class Mix: public Process {
  public:
    // Constructors
    Mix();

    inline std::string process_type() { return "mix"; };

    // IO
    Inlet a;
    Inlet b;
    Outlet out;

    // Processing 
    void process() ;
};
