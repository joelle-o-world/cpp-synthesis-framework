#include "Multiply.h"

// TODO: Probably want to use smart pointers

Multiply &multiply(AudioProcess &a, AudioProcess &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
}
Multiply &multiply(float a, AudioProcess &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(AudioProcess &a, float b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(Writer &a, AudioProcess &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(AudioProcess &a, Writer &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(Writer &a, Writer &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(float a, Writer &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(Writer &a, float b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Multiply &operator*(AudioProcess &a, AudioProcess &b) { return multiply(a, b); }
Multiply &operator*(float a, AudioProcess &b) { return multiply(a, b); };
Multiply &operator*(AudioProcess &a, float b) { return multiply(a, b); };
Multiply &operator*(Writer &a, AudioProcess &b) { return multiply(a, b); };
Multiply &operator*(AudioProcess &a, Writer &b) { return multiply(a, b); };
Multiply &operator*(Writer &a, Writer &b) { return multiply(a, b); };
Multiply &operator*(float a, Writer &b) { return multiply(a, b); };
Multiply &operator*(Writer &a, float b) { return multiply(a, b); };
