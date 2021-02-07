#include "Process.h"
#include <iostream>


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

std::vector<Process*>* Process::dependentProcesses() {
  std::vector<Process*> * list = new std::vector<Process*>;
  //Outlet* outlet = *outlets;
  for(Outlet* outlet : outlets) {
    std::cout << "Outlet has " << outlet->numberOfConnections() << " connections.\n";

    for(Inlet* inlet : outlet->connectedTo) {
      std::cout << "Inlet owner:" << inlet->owner;
      if(std::find(list->begin(), list->end(), inlet -> owner) != list->end())
        list->push_back(inlet->owner);
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
