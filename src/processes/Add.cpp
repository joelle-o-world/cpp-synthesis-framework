#include "./Add.h"

// NOTE: Hmm this file is worryingly repetitive. Probably could use a template
// to solve this.

Add &add(AudioProcess &a, AudioProcess &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
}
Add &add(float a, AudioProcess &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(AudioProcess &a, float b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(Writer &a, AudioProcess &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(AudioProcess &a, Writer &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(Writer &a, Writer &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(float a, Writer &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(Writer &a, float b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Add &operator+(AudioProcess &a, AudioProcess &b) { return add(a, b); }
Add &operator+(float a, AudioProcess &b) { return add(a, b); };
Add &operator+(AudioProcess &a, float b) { return add(a, b); };
Add &operator+(Writer &a, AudioProcess &b) { return add(a, b); };
Add &operator+(AudioProcess &a, Writer &b) { return add(a, b); };
Add &operator+(Writer &a, Writer &b) { return add(a, b); };
Add &operator+(float a, Writer &b) { return add(a, b); };
Add &operator+(Writer &a, float b) { return add(a, b); };
