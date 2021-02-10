#include "routing.h"


void connect(Outlet* outlet, Inlet* inlet) {
  if(inlet->isConnected) 
    throw "Inlet is already connected";
  inlet->connectedTo = outlet;
  inlet->isConnected = true;
  outlet->connectedTo.push_back(inlet);
}

void connect(Outlet* outlet, Process* P) {
  connect(outlet, P -> firstFreeInlet());
}

void connect(Process* P, Inlet* inlet) {
  connect(P -> mainOutlet(), inlet);
}

void connect(Process* P, Process* Q) {
  connect(P -> mainOutlet(), Q -> firstFreeInlet());
}

void checkConnection(Outlet* outlet, Inlet* inlet) {
  bool iToO = inlet -> isConnectedTo(outlet);
  bool oToI = outlet -> isConnectedTo(inlet);
  if(iToO && oToI)
    return ;
  else
    throw "Broken connection! \n" + outlet->name() + " -/> " + inlet->name() + "\n inlet_to_outlet = " + std::to_string(iToO) + "\n outlet_to_inlet = " + std::to_string(oToI);
}
