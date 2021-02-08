#include <iostream>
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

  std::cout << "It worked?\n";

  std::cout << "osc1 has " << osc1.numberOfInlets() << " inlets.\n";
  std::cout << "osc2 has " << osc2.numberOfInlets() << " inlets.\n";
  std::cout << "mix1 has " << mix1.numberOfInlets() << " inlets.\n";
  std::cout << "osc1 has " << osc1.numberOfOutlets() << " outlets.\n";
  std::cout << "osc2 has " << osc2.numberOfOutlets() << " outlets.\n";
  std::cout << "mix1 has " << mix1.numberOfOutlets() << " outlets.\n";

  auto dependents = osc1.dependentProcesses();
  //std::cout << "Mix 1 has " << mix1.dependentProcesses()->size() << " dependent processes.\n";
  //

  std::cout << "osc1 has " << dependents->size() << " dependent processes.\n";

  

  return 0;
}
