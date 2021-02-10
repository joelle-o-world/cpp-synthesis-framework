#include <iostream>
#include "Osc.h"
#include "Mix.h"
#include "routing.h"

int main() {
    
  try {

    Osc osc1;
    osc1.frequency = 220;

    Osc osc2;
    osc2.frequency = 300;

    Mix mix1;
    connect(osc1.outlets[0], mix1.inlets[0]);
    connect(osc2.outlets[0], mix1.inlets[1]);


    //std::cout << "Connecting feedback on osc1\n";
    //connect(mix1.outlets[0], mix1.inlets[0]);
    //std::cout << "feedback on osc1 done\n";

    std::cout << "It worked?\n";


    auto dependents = osc1.dependentProcesses();
    //std::cout << "Mix 1 has " << mix1.dependentProcesses()->size() << " dependent processes.\n";
    //

    std::cout << "osc1 has " << dependents->size() << " dependent processes.\n";


    std::cout << "osc1.priority: " << osc1.getPriority('a') << std::endl;
    std::cout << "osc2.priority: " << osc2.getPriority('a') << std::endl;
    std::cout << "mix1.priority: " << mix1.getPriority('a') << std::endl;

    
  } catch(const char* e) {
    std::cerr << e << std::endl;
  }

    return 0;
}
