#pragma once

#include "AudioProcess.h"
#include "Outlet.h"
#include "Reader.h"

void connect(Outlet &from, Reader &into);
void connect(AudioProcess &from, Reader &into);

void disconnect(Reader &inlet);
void connect(float constant, Reader &inlet);
