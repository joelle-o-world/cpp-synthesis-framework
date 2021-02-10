#pragma once

#include <vector>
#include <set>
#include <string>

#include "Outlet.h"
#include "Inlet.h"

#define CHUNK_SIZE 256
const int SAMPLE_RATE = 44100;

extern int processCount;

class Inlet;
class Outlet;

class Process {
  private:
    const int process_id;
    int priority;
    char priority_generation;

  public:
    // Constructors
    Process();
    
    // Identification
    char *name();

    // Array of inlets belonging to the component
    std::vector<Inlet*> inlets;

    // Array of outlets belonging to the component
    std::vector<Outlet*> outlets;

    virtual void process();

    Outlet* mainOutlet();

    std::set<Process*>* dependentProcesses();

    int numberOfInlets();
    int numberOfOutlets();

    void addInlet(Inlet& inlet);
    void addOutlet(Outlet& outlet);

    int getPriority(char generation = 0);
    void recalculatePriority(char generation = 0);

};
