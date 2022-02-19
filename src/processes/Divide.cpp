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
Divide &divide(UntypedWriter &a, AudioProcess &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(AudioProcess &a, UntypedWriter &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(UntypedWriter &a, UntypedWriter &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(float a, UntypedWriter &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(UntypedWriter &a, float b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Divide &operator/(AudioProcess &a, AudioProcess &b) { return divide(a, b); }
Divide &operator/(float a, AudioProcess &b) { return divide(a, b); };
Divide &operator/(AudioProcess &a, float b) { return divide(a, b); };
Divide &operator/(UntypedWriter &a, AudioProcess &b) { return divide(a, b); };
Divide &operator/(AudioProcess &a, UntypedWriter &b) { return divide(a, b); };
Divide &operator/(UntypedWriter &a, UntypedWriter &b) { return divide(a, b); };
Divide &operator/(float a, UntypedWriter &b) { return divide(a, b); };
Divide &operator/(UntypedWriter &a, float b) { return divide(a, b); };
