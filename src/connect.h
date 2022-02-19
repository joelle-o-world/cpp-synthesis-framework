#pragma once

#include "Component.h"
#include "Reader.h"
#include "Writer.h"

void connect(UntypedWriter &from, UntypedReader &into);
void connect(Component &from, UntypedReader &into);

void disconnect(UntypedReader &inlet);
void connect(float constant, UntypedReader &inlet);
