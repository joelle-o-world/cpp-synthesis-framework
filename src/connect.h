#pragma once

#include "AudioProcess.h"
#include "Inlet.h"
#include "Outlet.h"

void connect(Outlet &from, Inlet &into);
void connect(AudioProcess &from, Inlet &into);

void disconnect(Inlet &inlet);
void connect(float constant, Inlet &inlet);
