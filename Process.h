#pragma once

#include <vector>

#include "Outlet.h"
#include "Inlet.h"

class Inlet;
class Outlet;

class Process {
  public:
    const static int numberOfInlets;

    // Array of inlets belonging to the component
    Inlet** inlets;

    const static int numberOfOutlets;

    // Array of outlets belonging to the component
    Outlet** outlets;

    void process();

    Outlet* mainOutlet();

    std::vector<Process*> dependentProcesses();
};
