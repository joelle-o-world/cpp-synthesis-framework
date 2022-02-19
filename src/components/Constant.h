#pragma once

#include "../Component.h"
#include <string>

class Constant : public Component {
public:
  float value;
  Constant(float value) : Component({}, {stereo}), value(value) {}

  void process() override {
    auto OUT = out().data();
    for (int i = 0; i < signalChunkSize * 2; ++i) {
      OUT[i] = value;
    }
  }

  Writer<StereoBuffer> &out() { return (Writer<StereoBuffer> &)outputs[0]; }

  std::string describe() override { return std::to_string(value); }
};
