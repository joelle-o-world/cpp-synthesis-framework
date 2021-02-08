#include "calculatePriority.h"

bool Trace::includes(Process* P) const {
  if(value == P)
    return true;
  else if(previous)
    return previous->includes(P);
  else
    return false;
}

Trace Trace::append(Process* value) {
  return Trace(this, value);
}

// Constructors

Trace::Trace()
  : value(NULL), previous(NULL) { }

Trace::Trace(Trace* previous, Process* value) 
  : value(value),
    previous(previous)
  {}

int calculatePriority(Process& P) {
  Trace trace;
  return calculatePriority(P, trace);
}

int calculatePriority(Process& P, Trace parentTrace) {
  Trace trace = parentTrace.append(&P);


  // Maximum priority
  int max = 0;
  for(Process* Q : *P.dependentProcesses()) {
    if(trace.includes(Q))
      continue;

    else {
      int qPriority = lookUpOrCalculatePriority(*Q, trace);
      if(qPriority > max)
        max = qPriority;
    }
  }

  return max;
}

int lookUpOrCalculatePriority(Process& P, Trace parentTrace) {
  int priority = P.priority;
  if(priority > 0)
    // Note negative priority indicates unknown
    return priority;

  else
    return calculatePriority(P, parentTrace);
}

