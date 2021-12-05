#include "nodeIo.h"

Inlet::Inlet() {
  connectedTo = nullptr;
  owner = nullptr;
  isConstant = false;
}

void Inlet::connect(Outlet &outlet) {
  disconnect();
  connectedTo = &outlet;
  outlet.connectedTo.insert(this);
}
void Inlet::connect(float constant) {
  isConstant = true;
  buffer = new TypedSignalBuffer;
  buffer->type = Constant;
  buffer->constant = new float(constant);
}

void Inlet::disconnect() {
  isConstant = false;
  if (connectedTo)
    connectedTo->connectedTo.erase(this);
  connectedTo = nullptr;
}

void Inlet::healthCheck() {
  if (!isConstant && !connectedTo) {
    // TODO: Write a specific error message
    std::cerr << "Unhealthy Inlet!\n";
    throw 1;
  }
}
