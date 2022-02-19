#include "Divide.h"

// NOTE: Hmm this file is worryingly repetitive. Probably could use a template
// to solve this.

Divide &divide(Component &a, Component &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
}
Divide &divide(float a, Component &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(Component &a, float b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(UntypedWriter &a, Component &b) {
  Divide *p = new Divide();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Divide &divide(Component &a, UntypedWriter &b) {
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

Divide &operator/(Component &a, Component &b) { return divide(a, b); }
Divide &operator/(float a, Component &b) { return divide(a, b); };
Divide &operator/(Component &a, float b) { return divide(a, b); };
Divide &operator/(UntypedWriter &a, Component &b) { return divide(a, b); };
Divide &operator/(Component &a, UntypedWriter &b) { return divide(a, b); };
Divide &operator/(UntypedWriter &a, UntypedWriter &b) { return divide(a, b); };
Divide &operator/(float a, UntypedWriter &b) { return divide(a, b); };
Divide &operator/(UntypedWriter &a, float b) { return divide(a, b); };
