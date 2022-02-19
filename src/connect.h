#pragma once

#include "AudioProcess.h"
#include "Reader.h"
#include "Writer.h"

void connect(UntypedWriter &from, UntypedReader &into);
void connect(AudioProcess &from, UntypedReader &into);

void disconnect(UntypedReader &inlet);
void connect(float constant, UntypedReader &inlet);
