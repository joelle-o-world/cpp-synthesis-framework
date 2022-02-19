#pragma once
#include "../Component.h"

class BinaryOperation : public Component {
public:
  BinaryOperation() : Component({stereo, stereo}, {stereo}) {}

private:
  virtual inline void processSample(float &a, float &b, float &out) {
    // Base class does nothing
  }

public:
  // Two a-rate signals
  void process() override {
    auto A = a().data();
    auto B = b().data();
    auto OUT = out().data();
    for (int i = 0; i < signalChunkSize * 2; ++i)
      processSample(A[i], B[i], OUT[i]);
  }

  inline Reader<StereoBuffer> &a() { return (Reader<StereoBuffer> &)inputs[0]; }
  inline Reader<StereoBuffer> &b() { return (Reader<StereoBuffer> &)inputs[1]; }
  inline Writer<StereoBuffer> &out() {
    return (Writer<StereoBuffer> &)outputs[0];
  }
};
