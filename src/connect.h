#pragma once

#include "AudioProcess.h"
#include "nodeIo.h"

void connect(Outlet &from, Inlet &into);
void connect(AudioProcess &from, Inlet &into);

void disconnect(Inlet &inlet);
void connect(float constant, Inlet &inlet);
