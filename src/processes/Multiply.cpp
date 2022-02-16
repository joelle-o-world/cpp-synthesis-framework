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
Multiply &multiply(Outlet &a, AudioProcess &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(AudioProcess &a, Outlet &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(Outlet &a, Outlet &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(float a, Outlet &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(Outlet &a, float b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Multiply &operator*(AudioProcess &a, AudioProcess &b) { return multiply(a, b); }
Multiply &operator*(float a, AudioProcess &b) { return multiply(a, b); };
Multiply &operator*(AudioProcess &a, float b) { return multiply(a, b); };
Multiply &operator*(Outlet &a, AudioProcess &b) { return multiply(a, b); };
Multiply &operator*(AudioProcess &a, Outlet &b) { return multiply(a, b); };
Multiply &operator*(Outlet &a, Outlet &b) { return multiply(a, b); };
Multiply &operator*(float a, Outlet &b) { return multiply(a, b); };
Multiply &operator*(Outlet &a, float b) { return multiply(a, b); };
