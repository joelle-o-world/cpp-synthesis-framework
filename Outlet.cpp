#include "Outlet.h"

int Outlet::numberOfConnections() {
  return connectedTo.size();
}

bool Outlet::isConnectedTo(Inlet* inlet) {
  for(Inlet* inl : connectedTo)
    if(inl == inlet)
      return true;
  //Otherwise
  return false;
}

int Outlet::index() {
  if(!owner) {
    throw "Outlet has no owner";
  } else {
    for(int i=0; i < owner->outlets.size(); ++i)
      if(owner->outlets[i] == this)
        return i;
  }

  throw "Outlet not found in owner's `outlets` list";
}


std::string Outlet::name() {
  if(owner) {
    return owner->name() + ".o" + std::to_string(index()); 
  } else
    return "unclaimed-intlet";
}
