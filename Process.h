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
    int priority_generation;
    virtual inline std::string process_type() { return "process"; };

  public:
    // Constructors
    Process();
    
    // Identification
    std::string name();

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

    int getPriority(int generation = 0);
    void recalculatePriority(int generation = 0);

};
