#pragma once

#include "Process.h"

class Process;

class Mix: public Process {
  public:
    const static int numberOfInlets = 2;
    const static int numberOfOutlets = 1;
    void process() ;
};
