#include "connect.h"
#include "components/Constant.h"

void connect(UntypedWriter &outlet, UntypedReader &inlet) {
  disconnect(inlet);
  inlet.connectedTo = &outlet;
  outlet.connectedTo.insert(&inlet);
}

void connect(AudioProcess &from, UntypedReader &into) {
  connect(from.outputs[0], into);
}

void disconnect(UntypedReader &inlet) {
  inlet.isConstant = false;
  if (inlet.connectedTo)
    inlet.connectedTo->connectedTo.erase(&inlet);
  inlet.connectedTo = nullptr;
}

void connect(float k, UntypedReader &inlet) {
  auto c = new Constant(k);
  connect(*c, inlet);
}
