#include "Process.h"


Outlet* Process::mainOutlet() {
  return outlets[0];
}

std::vector<Process*>* Process::dependentProcesses() {
  std::vector<Process*> * list = new std::vector<Process*>;
  Outlet* outlet = *outlets;
  for(int i=0; i < numberOfOutlets; ++i, ++outlet) {

    for(Inlet* inlet : outlet->connectedTo) {
      if(std::find(list->begin(), list->end(), inlet -> owner) != list->end())
        list->push_back(inlet->owner);
    }
  }

  return list;
}

void Process::process() {
  throw "This shouldn't be called";
}
