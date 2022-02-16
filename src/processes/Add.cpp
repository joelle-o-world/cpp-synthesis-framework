#include "./Add.h"

Add &add(AudioProcess &a, AudioProcess &b) {
  Add *p = new Add();
  connect(a, p->inputs[0]);
  connect(b, p->inputs[1]);
  return *p;
}

Add &operator+(AudioProcess &a, AudioProcess &b) { return add(a, b); }
