#include <iostream> 

#include "./processes/Osc.h"

int main() {

  std::cout << "A\n";
  float myBuffer[signalChunkSize];
  std::cout << "B\n";
  _Osc myOsc;

  std::cout << "C\n";
  myOsc.outletbuffers = &myBuffer;

  std::cout << "D\n";
  myOsc.process();
  std::cout << myBuffer[0] << std::endl;
}
