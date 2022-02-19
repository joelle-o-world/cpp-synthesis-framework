#pragma once

#include "AudioProcess.h"
#include "Reader.h"
#include "Writer.h"

void connect(Writer &from, Reader &into);
void connect(AudioProcess &from, Reader &into);

void disconnect(Reader &inlet);
void connect(float constant, Reader &inlet);
