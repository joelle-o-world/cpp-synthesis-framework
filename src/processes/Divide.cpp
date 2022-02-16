#include "Divide.h"

// NOTE: Hmm this file is worryingly repetitive. Probably could use a template
// to solve this.

Divide &divide(AudioProcess &a, AudioProcess &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
}
Divide &divide(float a, AudioProcess &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(AudioProcess &a, float b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(Outlet &a, AudioProcess &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(AudioProcess &a, Outlet &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(Outlet &a, Outlet &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(float a, Outlet &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(Outlet &a, float b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Divide &operator/(AudioProcess &a, AudioProcess &b) { return divide(a, b); }
Divide &operator/(float a, AudioProcess &b) { return divide(a, b); };
Divide &operator/(AudioProcess &a, float b) { return divide(a, b); };
Divide &operator/(Outlet &a, AudioProcess &b) { return divide(a, b); };
Divide &operator/(AudioProcess &a, Outlet &b) { return divide(a, b); };
Divide &operator/(Outlet &a, Outlet &b) { return divide(a, b); };
Divide &operator/(float a, Outlet &b) { return divide(a, b); };
Divide &operator/(Outlet &a, float b) { return divide(a, b); };
