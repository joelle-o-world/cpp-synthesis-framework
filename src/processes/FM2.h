#pragma once

#include "../AudioProcess.h"
#include "./Osc.h"
#include "./arithmetic.h"
#include <iostream>

class FM2 : public AudioProcess {
  private:
  Osc osc1;
  Osc osc2;

  Multiply mult;
  Add add;

  StereoBuffer buffer1, buffer2;

public:
  FM2() : AudioProcess(6, 1) {}

  void process() {
    TypedSignalBuffer &frequency1 = *inputs[0], &modulation1 = *inputs[1],
                      &volume1 = *inputs[2], &frequency2 = *inputs[3],
                      &modulation2 = *inputs[4], &volume2 = *inputs[5],
                      &out = *outputs[0];

    if (frequency1.type == Stereo && modulation1.type == Stereo &&
        volume1.type == Stereo && frequency2.type == Stereo &&
        modulation2.type == Stereo && volume2.type == Stereo &&
        out.type == Stereo) {
      std::cout << "Using signal inputs";
      process(*frequency1.stereo, *modulation1.stereo, *volume1.stereo,
              *frequency2.stereo, *modulation2.stereo, *volume2.stereo,
              *out.stereo);
    } else if (frequency1.type == Constant && modulation1.type == Constant &&
               volume1.type == Constant && frequency2.type == Constant &&
               modulation2.type == Constant && volume2.type == Constant &&
               out.type == Stereo) {
      process(*frequency1.constant, *modulation1.constant, *volume1.constant,
              *frequency2.constant, *modulation2.constant, *volume2.constant,
              *out.stereo);
      std::cout << "Using constant inputs";
    } else
      throw "";
  }

  template <typename T1, typename T2, typename T3, typename T4, typename T5,
            typename T6, typename T7>
  void process(T1 &frequency1, T2 &modulation1, T3 &volume1, T4 &frequency2,
               T5 &modulation2, T6 &volume2, T7 &out) {

    //mult.process(frequency1, modulation1, buffer2);
    osc1.process(buffer1, buffer1);
    mult.process(volume1, buffer1, out);

    //mult.process(frequency2, modulation2, buffer2);
    osc2.process(buffer2, buffer2);
    mult.process(volume2, buffer2, buffer2);
    add.process(buffer1, out, out);
  }
};
