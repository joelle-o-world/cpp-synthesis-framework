#pragma once

#include "Process.h"

class Osc: public Process {
  private:
    float phase;
  public:
    // Constructors
    Osc();
    Osc(float frequency);

    inline std::string process_type() { return "osc"; };

    // IO
    float frequency;
    Outlet output;

    // Processing
    void process() ;
};
