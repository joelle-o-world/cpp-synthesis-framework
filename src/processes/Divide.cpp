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
Divide &divide(Writer &a, AudioProcess &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(AudioProcess &a, Writer &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(Writer &a, Writer &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(float a, Writer &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(Writer &a, float b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Divide &operator/(AudioProcess &a, AudioProcess &b) { return divide(a, b); }
Divide &operator/(float a, AudioProcess &b) { return divide(a, b); };
Divide &operator/(AudioProcess &a, float b) { return divide(a, b); };
Divide &operator/(Writer &a, AudioProcess &b) { return divide(a, b); };
Divide &operator/(AudioProcess &a, Writer &b) { return divide(a, b); };
Divide &operator/(Writer &a, Writer &b) { return divide(a, b); };
Divide &operator/(float a, Writer &b) { return divide(a, b); };
Divide &operator/(Writer &a, float b) { return divide(a, b); };
