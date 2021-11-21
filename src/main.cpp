#include <iostream>
#include <portaudio.h>

int main() {
  auto err = Pa_Initialize();
  if (err != paNoError)
  {
    std::cerr << "Port audio error (at initialisation): " << Pa_GetErrorText(err) << "\n";
    return 1;
  }

  std::cout << "Initialised port audio!\n";

  err = Pa_Terminate();
  if (err != paNoError)
    std::cerr << "Port audio error (at termination): " << Pa_GetErrorText(err) << "\n";
}
