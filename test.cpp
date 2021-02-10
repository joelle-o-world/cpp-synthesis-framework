#include <iostream>
#include <assert.h>
#include "Osc.h"
#include "Mix.h"
#include "routing.h"

using std::cout;


#define RED "\033[31m"
#define GREEN "\033[32m"


void Test_AssigningPrioritiesWithSimpleCircuit() {
  Osc osc1, osc2, osc3;

  Mix mix1, mix2;
  connect(osc1.outlets[0], mix1.inlets[0]);
  connect(osc2.outlets[0], mix1.inlets[1]);
  connect(mix1.outlets[0], mix2.inlets[0]);
  connect(osc3.outlets[0], mix2.inlets[1]);

  assert(osc1.getPriority('a') == 2);
  assert(osc2.getPriority('b') == 2);
  assert(mix1.getPriority('c') == 1);
  assert(osc3.getPriority('c') == 1);
  assert(mix2.getPriority('c') == 0);
}

void Test_AssigningPrioritiesWithFeedback() {
  // With one process
  Mix mix1;

  connect(mix1.outlets[0], mix1.inlets[0]);

  assert(mix1.getPriority('x') == 0);
}

int main() {
  try {
    Test_AssigningPrioritiesWithSimpleCircuit();
    Test_AssigningPrioritiesWithFeedback();

  } catch(char * msg) {
    std::cerr << RED << "Test failed: " << msg << std::endl;
    return 1;
  }


  cout << GREEN << "All tests passed!\n";
  return 0;
}
