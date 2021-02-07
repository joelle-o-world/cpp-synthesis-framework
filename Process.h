#pragma once

#include <vector>

#include "Outlet.h"
#include "Inlet.h"

#define CHUNK_SIZE 256
const int SAMPLE_RATE = 44100;

class Inlet;
class Outlet;

class Process {
  public:
    const static int numberOfInlets = 0;

    // Array of inlets belonging to the component
    Inlet** inlets;

    const static int numberOfOutlets = 0;

    // Array of outlets belonging to the component
    Outlet** outlets;

    virtual void process();

    Outlet* mainOutlet();

    std::vector<Process*>* dependentProcesses();
};
