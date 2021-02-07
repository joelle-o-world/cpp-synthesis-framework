#include "Process.h"

class Trace {
  public:
    const Process * const value;
    Trace * const previous;


    Trace(Trace* previous, Process* value) 
      : value(value),
        previous(previous)
    {}


    bool includes(Process* P) const {
      if(value == P)
        return true;
      else if(previous)
        return previous->includes(P);
      else
        return false;
    }

    Trace append(Process* value) {
      return Trace(this, value);
    }
};

class Coordinator {

  int calculatePriority(Process* P, Trace parentTrace) {
    Trace trace = parentTrace.append(P);


    // Maximum priority
    int max = 0;
    for(Process* Q : P->dependentProcesses()) {
      if(trace.includes(Q))
        continue;

      else {
        int qPriority = lookUpOrCalculatePriority(Q, trace);
        if(qPriority > max)
          max = qPriority;
      }
    }

    return max;
  }

  int lookUpOrCalculatePriority(Process* P, Trace parentTrace) {
    int priority = lookUpPriority(P);
    if(priority > 0)
      // Note negative priority indicates unknown
      return priority;

    else
      return calculatePriority(P, parentTrace);
  }

  int lookUpPriority(Process* P);
};
