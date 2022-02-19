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
Subtract &subtract(UntypedWriter &a, AudioProcess &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(AudioProcess &a, UntypedWriter &b) {
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

Subtract &operator-(AudioProcess &a, AudioProcess &b) { return subtract(a, b); }
Subtract &operator-(float a, AudioProcess &b) { return subtract(a, b); };
Subtract &operator-(AudioProcess &a, float b) { return subtract(a, b); };
Subtract &operator-(UntypedWriter &a, AudioProcess &b) {
  return subtract(a, b);
};
Subtract &operator-(AudioProcess &a, UntypedWriter &b) {
  return subtract(a, b);
};
Subtract &operator-(UntypedWriter &a, UntypedWriter &b) {
  return subtract(a, b);
};
Subtract &operator-(float a, UntypedWriter &b) { return subtract(a, b); };
Subtract &operator-(UntypedWriter &a, float b) { return subtract(a, b); };
