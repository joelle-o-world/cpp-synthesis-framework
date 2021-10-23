#pragma once

#include "../AudioProcess.h"
#include <math.h>

/**
 * Adds two audio buffers together.
 */
class Add : public BinaryOperationProcess {
private:
  void processSample(float &a, float &b, float &out) override { out = a + b; }
};

class Subtract : public BinaryOperationProcess {
private:
  void processSample(float &a, float &b, float &out) override { out = a - b; }
};

class Minus : public UnaryOperationProcess {
private:
  void processSample(float &in, float &out) { out = -in; }
};

/**
 * Multiplies a signal by a k-rate constant.
 */
class Multiply : public BinaryOperationProcess {
public:
  void processSample (float &a, float &b, float &out) override {
    out = a * b;
  }
};

class Divide : public BinaryOperationProcess {
  private:
    void processSample(float &a, float &b, float &out) override {
      out = a / b;
    }
};

class Invert : public UnaryOperationProcess {
  private:
    void processSample(float &in, float &out) {
      out = 1.0 / in;
    }
};

class Pow : public BinaryOperationProcess {
  private:
    void processSample(float &a, float &b, float &out) {
      out = pow(a, b);
    }
};

class Sq : public UnaryOperationProcess {
  private:
    void processSample(float &in, float &out) {
      out = in * in;
    }
};

class Sqrt : public UnaryOperationProcess {
  private:
    void processSample(float &in, float &out) {
      out = sqrt(in);
    }
};
