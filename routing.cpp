#include "routing.h"


void connect(Outlet* outlet, Inlet* inlet) {
  if(inlet->isConnected) 
    throw "Inlet is already connected";

  inlet->connectedTo = outlet;
  inlet->isConnected = true;
  outlet->connectedTo.push_back(inlet);
}
