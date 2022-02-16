#include "Subtract.h"

Subtract &subtract(AudioProcess &a, AudioProcess &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
}
Subtract &subtract(float a, AudioProcess &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(AudioProcess &a, float b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(Outlet &a, AudioProcess &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(AudioProcess &a, Outlet &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(Outlet &a, Outlet &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(float a, Outlet &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(Outlet &a, float b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Subtract &operator-(AudioProcess &a, AudioProcess &b) { return subtract(a, b); }
Subtract &operator-(float a, AudioProcess &b) { return subtract(a, b); };
Subtract &operator-(AudioProcess &a, float b) { return subtract(a, b); };
Subtract &operator-(Outlet &a, AudioProcess &b) { return subtract(a, b); };
Subtract &operator-(AudioProcess &a, Outlet &b) { return subtract(a, b); };
Subtract &operator-(Outlet &a, Outlet &b) { return subtract(a, b); };
Subtract &operator-(float a, Outlet &b) { return subtract(a, b); };
Subtract &operator-(Outlet &a, float b) { return subtract(a, b); };
