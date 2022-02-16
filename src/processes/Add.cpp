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
Add &add(Outlet &a, AudioProcess &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(AudioProcess &a, Outlet &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(Outlet &a, Outlet &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(float a, Outlet &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(Outlet &a, float b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};

Add &operator+(AudioProcess &a, AudioProcess &b) { return add(a, b); }
Add &operator+(float a, AudioProcess &b) { return add(a, b); };
Add &operator+(AudioProcess &a, float b) { return add(a, b); };
Add &operator+(Outlet &a, AudioProcess &b) { return add(a, b); };
Add &operator+(AudioProcess &a, Outlet &b) { return add(a, b); };
Add &operator+(Outlet &a, Outlet &b) { return add(a, b); };
Add &operator+(float a, Outlet &b) { return add(a, b); };
Add &operator+(Outlet &a, float b) { return add(a, b); };
