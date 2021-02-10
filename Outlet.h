#pragma once

#include <vector>
#include "Inlet.h"
#include "Process.h"

class Inlet;
class Process;

class Outlet {
public:
  float* buffer;
  Process* owner;
  std::vector<Inlet*> connectedTo;

  int numberOfConnections();

  bool isConnectedTo(Inlet * inlet);

  int index();
  std::string name();
};
