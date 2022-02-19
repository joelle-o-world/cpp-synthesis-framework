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
Add &add(UntypedWriter &a, AudioProcess &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(AudioProcess &a, UntypedWriter &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(UntypedWriter &a, UntypedWriter &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(float a, UntypedWriter &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(UntypedWriter &a, float b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Add &operator+(AudioProcess &a, AudioProcess &b) { return add(a, b); }
Add &operator+(float a, AudioProcess &b) { return add(a, b); };
Add &operator+(AudioProcess &a, float b) { return add(a, b); };
Add &operator+(UntypedWriter &a, AudioProcess &b) { return add(a, b); };
Add &operator+(AudioProcess &a, UntypedWriter &b) { return add(a, b); };
Add &operator+(UntypedWriter &a, UntypedWriter &b) { return add(a, b); };
Add &operator+(float a, UntypedWriter &b) { return add(a, b); };
Add &operator+(UntypedWriter &a, float b) { return add(a, b); };
