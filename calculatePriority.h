#pragma once

#include "Process.h"

class Process;

class Trace {
  public:
    // Properties
    const Process * const value;
    Trace * const previous;

    // Constructors
    Trace();
    Trace(Trace* previous, Process* value);

    // Methods
    bool includes(Process* P) const;
    Trace append(Process* value);
};

int calculatePriority(Process& P);
int calculatePriority(Process& P, Trace parentTrace);
int lookUpOrCalculatePriority(Process& P, Trace parentTrace);
