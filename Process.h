#pragma once

#include <vector>
#include <set>
#include <string>
#include <iostream>

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
    int priority = 0;
    int priority_generation;
    virtual inline std::string process_type() { return "process"; };

  protected:
    void addInlet(Inlet& inlet);
    void addOutlet(Outlet& outlet);

  public:
    // Constructors
    Process();

    bool isFinalProcess = false;
    
    // Identification
    std::string name();

    // Array of inlets belonging to the component
    std::vector<Inlet*> inlets;

    // Array of outlets belonging to the component
    std::vector<Outlet*> outlets;

    virtual void process();

    Outlet* mainOutlet();
    Inlet* mainInlet();

    Inlet* firstFreeInlet();

    // Navigating the signal graph
    std::set<Process*>* dependentProcesses();
    std::set<Process*>* neighbours();

    int numberOfInlets();
    int numberOfOutlets();


    int getPriority(int generation = 0);
    void recalculatePriority(int generation = 0);
    int readPriority() { return priority; }

    friend bool sort_by_priority(Process* r, Process* l);
};


bool sort_by_priority(Process* r, Process* l);

void sortProcesses(std::vector<Process*>& processes);
