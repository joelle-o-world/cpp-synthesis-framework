#include "Decay.h"
#include "../connect.h"

Decay &decay(float halfLife) {
  Decay *p = new Decay;
  connect(halfLife, p->inputs[0]);
  return *p;
}
Decay &decay(Component &halfLife) {
  Decay *p = new Decay;
  connect(halfLife, p->inputs[0]);
  return *p;
}
