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

void Test_AssigningPrioritiesWithFeedback2() {
  // With one process
  Mix mix1, mix2, mix3;

  // 3 Oscs connected in a circle..
  // ||: --> mix3 --> mix2 --> mix1 --> :||
  connect(mix3.outlets[0], mix2.inlets[0]);
  connect(mix2.outlets[0], mix1.inlets[0]);
  connect(mix1.outlets[0], mix3.inlets[0]);

  // Starting from mix1
  assert(mix1.getPriority('x') == 0);
  assert(mix2.getPriority('x') == 1);
  assert(mix3.getPriority('x') == 2);
  
  // Starting from mix2
  cout << "mix2.getPriority('y') = " << mix2.getPriority('y') << '\n';
  assert(mix2.getPriority('y') == 0); // ERROR
  assert(mix3.getPriority('y') == 1);
  assert(mix1.getPriority('y') == 2);

  // Starting from mix1
  assert(mix3.getPriority('z') == 0);
  assert(mix1.getPriority('z') == 1);
  assert(mix2.getPriority('z') == 2);
}

int main() {
  try {
    Test_AssigningPrioritiesWithSimpleCircuit();
    Test_AssigningPrioritiesWithFeedback();
    Test_AssigningPrioritiesWithFeedback2();

  } catch(char * msg) {
    std::cerr << RED << "Test failed: " << msg << std::endl;
    return 1;
  }


  cout << GREEN << "All tests passed!\n";
  return 0;
}
