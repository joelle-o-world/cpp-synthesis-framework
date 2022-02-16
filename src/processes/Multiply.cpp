#include "Multiply.h"

// TODO: Probably want to use smart pointers
Multiply &multiply(AudioProcess &a, AudioProcess &b) {
  Multiply *p = new Multiply;
  connect(a, p->inputs[0]);
  connect(b, p->inputs[1]);
  return *p;
}
Multiply &multiply(AudioProcess &a, float b) {
  Multiply *p = new Multiply;
  connect(a, p->inputs[0]);
  connect(b, p->inputs[1]);
  return *p;
}

Multiply &operator*(AudioProcess &a, AudioProcess &b) { return multiply(a, b); }
Multiply &operator*(AudioProcess &a, float b) { return multiply(a, b); }
