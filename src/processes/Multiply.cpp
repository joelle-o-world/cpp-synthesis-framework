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
Multiply &multiply(UntypedWriter &a, AudioProcess &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(AudioProcess &a, UntypedWriter &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(UntypedWriter &a, UntypedWriter &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(float a, UntypedWriter &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(UntypedWriter &a, float b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Multiply &operator*(AudioProcess &a, AudioProcess &b) { return multiply(a, b); }
Multiply &operator*(float a, AudioProcess &b) { return multiply(a, b); };
Multiply &operator*(AudioProcess &a, float b) { return multiply(a, b); };
Multiply &operator*(UntypedWriter &a, AudioProcess &b) {
  return multiply(a, b);
};
Multiply &operator*(AudioProcess &a, UntypedWriter &b) {
  return multiply(a, b);
};
Multiply &operator*(UntypedWriter &a, UntypedWriter &b) {
  return multiply(a, b);
};
Multiply &operator*(float a, UntypedWriter &b) { return multiply(a, b); };
Multiply &operator*(UntypedWriter &a, float b) { return multiply(a, b); };
