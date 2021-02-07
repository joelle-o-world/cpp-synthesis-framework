#include "Osc.h"
#include "Mix.h"
#include "routing.h"

int main() {

  Osc osc1;
  osc1.frequency = 220;

  Osc osc2;
  osc2.frequency = 300;

  Mix mix1;
  connect(osc1.outlets[0], mix1.inlets[0]);
  connect(osc2.outlets[0], mix1.inlets[1]);


  return 0;
}
