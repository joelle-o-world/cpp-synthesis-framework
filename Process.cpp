#include "Process.h"

int processCount = 0;

// Constructors
Process::Process()
  : process_id(processCount++)
{}

void Process::addInlet(Inlet& inlet) {
  inlets.push_back(&inlet);
  inlet.owner = this;
}

void Process::addOutlet(Outlet& outlet) {
  outlets.push_back(&outlet);
  outlet.owner = this;
}

Outlet* Process::mainOutlet() {
  return outlets[0];
}

std::set<Process*>* Process::dependentProcesses() {
  std::set<Process*> * list = new std::set<Process*>;
  for(Outlet* outlet : outlets) {
    for(Inlet* inlet : outlet->connectedTo) {
      list->insert(inlet->owner);
    }
  }

  return list;
}


void Process::process() {
}

int Process::numberOfInlets() {
  return inlets.size();
}

int Process::numberOfOutlets() {
  return outlets.size();
}

int Process::getPriority(char generation) {
  if(generation == priority_generation) {
    return priority;
  } else {
    recalculatePriority(generation);
    return priority;
  }
}


void Process::recalculatePriority(char generation) {
  priority_generation = generation;
  priority = 0;
  for(Process* p : *dependentProcesses()) {
    int pPriority = p -> getPriority(generation);
    if(pPriority + 1 > priority)
      priority = pPriority + 1;
  }
}
