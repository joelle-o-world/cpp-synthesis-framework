#pragma once
#include "../Component.h"

class UnaryOperation : public Component {
public:
  UnaryOperation() : Component({stereo}, {stereo}) {}

public:
  virtual inline void processSample(float &in, float &out) {
    throw "No override defined";
  }

  void process() {
    auto IN = in().data();
    float *OUT = out().data();

    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(OUT[i], IN[i]);
  }

public:
  Reader<StereoBuffer> &in() { return (Reader<StereoBuffer> &)inputs[0]; }
  Writer<StereoBuffer> &out() { return (Writer<StereoBuffer> &)outputs[0]; }
};
