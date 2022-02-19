#include "Subtract.h"

Subtract &subtract(Component &a, Component &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
}
Subtract &subtract(float a, Component &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(Component &a, float b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(UntypedWriter &a, Component &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(Component &a, UntypedWriter &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(UntypedWriter &a, UntypedWriter &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(float a, UntypedWriter &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(UntypedWriter &a, float b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Subtract &operator-(Component &a, Component &b) { return subtract(a, b); }
Subtract &operator-(float a, Component &b) { return subtract(a, b); };
Subtract &operator-(Component &a, float b) { return subtract(a, b); };
Subtract &operator-(UntypedWriter &a, Component &b) { return subtract(a, b); };
Subtract &operator-(Component &a, UntypedWriter &b) { return subtract(a, b); };
Subtract &operator-(UntypedWriter &a, UntypedWriter &b) {
  return subtract(a, b);
};
Subtract &operator-(float a, UntypedWriter &b) { return subtract(a, b); };
Subtract &operator-(UntypedWriter &a, float b) { return subtract(a, b); };
