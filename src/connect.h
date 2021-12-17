#pragma once

#include "nodeIo.h"

void connect(Outlet &from, Inlet &into);
void connect(AudioProcess &from, Inlet &into);
void connect(float constant, Inlet &inlet);

void disconnect(Inlet &inlet);
