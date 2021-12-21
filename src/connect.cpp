#include "connect.h"

void connect(Outlet &outlet, Inlet &inlet) {
  disconnect(inlet);
  inlet.connectedTo = &outlet;
  outlet.connectedTo.insert(&inlet);
}

void connect(AudioProcess &from, Inlet &into) {
  connect(from.outputs[0], into);
}

void disconnect(Inlet &inlet) {
  inlet.isConstant = false;
  if (inlet.connectedTo)
    inlet.connectedTo->connectedTo.erase(&inlet);
  inlet.connectedTo = nullptr;
}
