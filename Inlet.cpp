#include "Inlet.h"

bool Inlet::isFree() { return !isConnected; }

bool Inlet::isConnectedTo(Outlet* outlet) {
  return connectedTo == outlet;
}

int Inlet::index() {
  if(!owner)
    throw "Inlet has no owner";

  for(int i=0; i<owner->inlets.size(); ++i) {
    if(owner->inlets[i] == this)
      return i;
  }

  throw "Inlet does not appear in owners inlet list";
}

std::string Inlet::name() {
  if(owner) {
    return owner->name() + ".i" + std::to_string(index());
  } else
    return "unclaimed-intlet";
}
