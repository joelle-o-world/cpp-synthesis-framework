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
Subtract &subtract(Writer &a, AudioProcess &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(AudioProcess &a, Writer &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(Writer &a, Writer &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(float a, Writer &b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Subtract &subtract(Writer &a, float b) {
  Subtract *p = new Subtract();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Subtract &operator-(AudioProcess &a, AudioProcess &b) { return subtract(a, b); }
Subtract &operator-(float a, AudioProcess &b) { return subtract(a, b); };
Subtract &operator-(AudioProcess &a, float b) { return subtract(a, b); };
Subtract &operator-(Writer &a, AudioProcess &b) { return subtract(a, b); };
Subtract &operator-(AudioProcess &a, Writer &b) { return subtract(a, b); };
Subtract &operator-(Writer &a, Writer &b) { return subtract(a, b); };
Subtract &operator-(float a, Writer &b) { return subtract(a, b); };
Subtract &operator-(Writer &a, float b) { return subtract(a, b); };
