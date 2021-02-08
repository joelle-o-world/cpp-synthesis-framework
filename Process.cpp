#include "Process.h"


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
  throw "This shouldn't be called";
}

int Process::numberOfInlets() {
  return inlets.size();
}

int Process::numberOfOutlets() {
  return outlets.size();
}
