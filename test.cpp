#include <iostream>
#include <assert.h>

#include "Osc.h"
#include "Mix.h"
#include "routing.h"
#include "explore.h"

using std::cout;


#define RED "\033[31m"
#define GREEN "\033[32m"

void H(std::string str) {
  //cout << "## " << str << '\n';
}

void P(std::string str) {
  //cout << str << '\n';
}

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

void Test_AssigningPrioritiesWithSimpleCircuit2() {
  Mix a,b,c,d,e;

  connect(&a, &c);
  connect(&b, &c);
  connect(&c, &d);
  connect(&d, &e);

  e.isFinalProcess = true;

  a.recalculatePriority(19);
  b.recalculatePriority(19);
  c.recalculatePriority(19);
  d.recalculatePriority(19);
  e.recalculatePriority(19);
  
  assert(e.readPriority() == 0);
  assert(d.readPriority() == 1);
  assert(c.readPriority() == 2);
  assert(b.readPriority() == 3);
  assert(a.readPriority() == 3);
}

void Test_AssigningPrioritiesWithFeedback() {
  // With one process
  Mix mix1;

  connect(mix1.outlets[0], mix1.inlets[0]);

  assert(mix1.getPriority('s') == 0);
}

void Test_AssigningPrioritiesWithFeedback2() {
  H("Test: Assigns appropriate priorities to a 3-process feedback loop");
  //cout << "Creating mix units...\n";
  // With one process
  Mix mix1, mix2, mix3;

  // 3 Oscs connected in a circle..
  // ||: --> mix3 --> mix2 --> mix1 --> :||
  P("Connecting mix units in a circle");
  P("||: --> mix3 --> mix2 --> mix1 --> :||");
  connect(mix3.outlets[0], mix2.inlets[0]);
  connect(mix2.outlets[0], mix1.inlets[0]);
  connect(mix1.outlets[0], mix3.inlets[0]);

  mix1.isFinalProcess = true;

  // Starting from mix1
  assert(mix1.getPriority('x') == 0);
  assert(mix2.getPriority('x') == 1);
  assert(mix3.getPriority('x') == 2);
  
}


void Test_ConnectFunction() {
  Mix a, b, c, d, e, f;

  // Connecting outlet pointer to inlet pointer
  P("Connecting " + a.name() + " -> " + b.name());
  connect(a.outlets[0], b.inlets[0]);
  checkConnection(a.outlets[0], b.inlets[0]);

  // connecting outlet pointer to process pointer
  P("Connecting " + b.name() + " -> " + c.name());
  connect(b.outlets[0], &c);
  checkConnection(b.outlets[0], c.inlets[0]);

  // connecting process pointer to inlet pointer
  P("Connecting " + c.name() + " -> " + d.name());
  connect(&c, d.inlets[0]);
  checkConnection(c.outlets[0], d.inlets[0]);

  // connecting process pointer to process pointer
  P("Connecting " + d.name() + " (d) -> " + e.name());
  connect(&d, &e);
  checkConnection(d.outlets[0], e.inlets[0]);


  // connecting to second inlet using process pointer
  P("Connecting " + f.outlets[0]->name() + " -> " + e.inlets[1]->name());
  connect(&f, &e);
  checkConnection(f.outlets[0], e.inlets[1]);


}


void Test_ProcessNeighbours() {
  H("Process::neighbours()");

  Mix a,b,c,d,e;

  connect(&a, &c);
  connect(&b, &c);
  connect(&c, &d);
  connect(&d, &e);
  connect(&e, &b);

  auto aNeighbours = a.neighbours();
  assert(aNeighbours->find(&c) != aNeighbours->end());

  auto bNeighbours = b.neighbours();
  assert(bNeighbours->find(&c) != bNeighbours->end());
  assert(bNeighbours->find(&e) != bNeighbours->end());

  auto cNeighbours = c.neighbours();
  assert(cNeighbours->find(&a) != cNeighbours->end());
  assert(cNeighbours->find(&b) != cNeighbours->end());
  assert(cNeighbours->find(&d) != cNeighbours->end());

  auto dNeighbours = d.neighbours();
  assert(dNeighbours->find(&c) != dNeighbours->end());
  assert(dNeighbours->find(&e) != dNeighbours->end());


  auto eNeighbours = e.neighbours();
  assert(eNeighbours->find(&d) != eNeighbours->end());
  assert(eNeighbours->find(&b) != eNeighbours->end());

  // TODO: Add some negative assertions.
}

void Test_ExploringCircuits() {
  Mix a,b,c,d,e, f;

  connect(&a, &c);
  connect(&b, &c);
  connect(&c, &d);
  connect(&d, &e);
  connect(&e, &b);

  std::vector<Process*>* all = explore(&a);
  assert(all->size() == 5);
  assert(find(all->begin(), all->end(), &a) != all->end());
  assert(find(all->begin(), all->end(), &b) != all->end());
  assert(find(all->begin(), all->end(), &c) != all->end());
  assert(find(all->begin(), all->end(), &d) != all->end());
  assert(find(all->begin(), all->end(), &e) != all->end());
  assert(find(all->begin(), all->end(), &f) == all->end());
  delete all;

  all = explore(&c);
  assert(all->size() == 5);
  assert(find(all->begin(), all->end(), &a) != all->end());
  assert(find(all->begin(), all->end(), &b) != all->end());
  assert(find(all->begin(), all->end(), &c) != all->end());
  assert(find(all->begin(), all->end(), &d) != all->end());
  assert(find(all->begin(), all->end(), &e) != all->end());
  assert(find(all->begin(), all->end(), &f) == all->end());
  delete all;

  all = explore(&d);
  assert(all->size() == 5);
  assert(find(all->begin(), all->end(), &a) != all->end());
  assert(find(all->begin(), all->end(), &b) != all->end());
  assert(find(all->begin(), all->end(), &c) != all->end());
  assert(find(all->begin(), all->end(), &d) != all->end());
  assert(find(all->begin(), all->end(), &e) != all->end());
  assert(find(all->begin(), all->end(), &f) == all->end());
  delete all;

  all = explore(&f);
  assert(all->size() == 1);
  assert((*all)[0] == &f);
  delete all;
}

void Test_SortingByPriority() {
  Mix a,b,c,d,e;

  connect(&a, &b);
  connect(&b, &c);
  connect(&c, &d);
  connect(&d, &e);

  e.isFinalProcess = true;
  e.recalculatePriority(19);

  auto allProcesses = explore(&a);

  sortProcesses(*allProcesses);

  assert((*allProcesses)[0] == &a);
  assert((*allProcesses)[1] == &b);
  assert((*allProcesses)[2] == &c);
  assert((*allProcesses)[3] == &d);
  assert((*allProcesses)[4] == &e);
}

void Test_BufferAssignment() {
  cout << "Testing Buffer Assignment\n";
  Mix a,b,c,d,e;

  cout << "Connecting " << a.name() << " -> " << c.name() << '\n';
  connect(a.outlets[0], c.inlets[0]);
  cout << "Connecting " << b.name() << " -> " << c.name() << '\n';
  connect(b.outlets[0], c.inlets[1]);
  cout << "Connecting " << c.name() << " -> " << d.name() << '\n';
  connect(c.outlets[0], d.inlets[0]);
  cout << "Connecting " << d.name() << " -> " << e.name() << '\n';
  connect(d.outlets[0], e.inlets[0]);

  e.isFinalProcess = true;
  a.recalculatePriority(19);
  b.recalculatePriority(19);
  c.recalculatePriority(19);
  d.recalculatePriority(19);
  e.recalculatePriority(19);



  std::vector<Process*> allProcesses = *explore(&a);
  sortProcesses(allProcesses);
  int numberOfBuffers = assignBuffers(allProcesses);
  assert(numberOfBuffers == 2);
}

int main() {

  try {

    Test_AssigningPrioritiesWithSimpleCircuit();
    Test_AssigningPrioritiesWithSimpleCircuit2();
    Test_AssigningPrioritiesWithFeedback();
    Test_AssigningPrioritiesWithFeedback2();
    Test_ConnectFunction();
    Test_ProcessNeighbours();
    Test_ExploringCircuits();
    Test_SortingByPriority();
    
    Test_BufferAssignment();

  } catch(char const * msg) {
    std::cerr << RED << "Test failed: " << msg << std::endl;
    return 1;
  } catch(std::string msg) {
    std::cerr << RED << "Test failed: " << msg << std::endl;
    return 1;
  }


  cout << GREEN << "All tests passed!\n";
  return 0;
}
