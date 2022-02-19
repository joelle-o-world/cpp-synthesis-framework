#include "connect.h"
#include "processes/Constant.h"

void connect(Writer &outlet, Reader &inlet) {
  disconnect(inlet);
  inlet.connectedTo = &outlet;
  outlet.connectedTo.insert(&inlet);
}

void connect(AudioProcess &from, Reader &into) {
  connect(from.outputs[0], into);
}

void disconnect(Reader &inlet) {
  inlet.isConstant = false;
  if (inlet.connectedTo)
    inlet.connectedTo->connectedTo.erase(&inlet);
  inlet.connectedTo = nullptr;
}

void connect(float k, Reader &inlet) {
  auto c = new Constant(k);
  connect(*c, inlet);
}
