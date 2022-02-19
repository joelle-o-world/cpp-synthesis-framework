#include "./Add.h"

// NOTE: Hmm this file is worryingly repetitive. Probably could use a template
// to solve this.

Add &add(Component &a, Component &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
}
Add &add(float a, Component &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(Component &a, float b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(UntypedWriter &a, Component &b) {
  Add *p = new Add();
  connect(a, p->a());
  connect(b, p->b());
  return *p;
};
Add &add(Component &a, UntypedWriter &b) {
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

Add &operator+(Component &a, Component &b) { return add(a, b); }
Add &operator+(float a, Component &b) { return add(a, b); };
Add &operator+(Component &a, float b) { return add(a, b); };
Add &operator+(UntypedWriter &a, Component &b) { return add(a, b); };
Add &operator+(Component &a, UntypedWriter &b) { return add(a, b); };
Add &operator+(UntypedWriter &a, UntypedWriter &b) { return add(a, b); };
Add &operator+(float a, UntypedWriter &b) { return add(a, b); };
Add &operator+(UntypedWriter &a, float b) { return add(a, b); };
