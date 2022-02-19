#include "Multiply.h"

// TODO: Probably want to use smart pointers

Multiply &multiply(Component &a, Component &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
}
Multiply &multiply(float a, Component &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(Component &a, float b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(UntypedWriter &a, Component &b) {
  Multiply *p = new Multiply();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Multiply &multiply(Component &a, UntypedWriter &b) {
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

Multiply &operator*(Component &a, Component &b) { return multiply(a, b); }
Multiply &operator*(float a, Component &b) { return multiply(a, b); };
Multiply &operator*(Component &a, float b) { return multiply(a, b); };
Multiply &operator*(UntypedWriter &a, Component &b) { return multiply(a, b); };
Multiply &operator*(Component &a, UntypedWriter &b) { return multiply(a, b); };
Multiply &operator*(UntypedWriter &a, UntypedWriter &b) {
  return multiply(a, b);
};
Multiply &operator*(float a, UntypedWriter &b) { return multiply(a, b); };
Multiply &operator*(UntypedWriter &a, float b) { return multiply(a, b); };
