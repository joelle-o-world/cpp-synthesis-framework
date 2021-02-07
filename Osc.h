#pragma once

#include "Process.h"

class Osc: public Process {
  private:
    float phase;
  public:
    float frequency;
    const static int numberOfInlets = 0;
    const static int numberOfOutlets = 1;
    void process() ;
};
