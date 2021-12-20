#pragma once

#include "./BinaryOperation.h"
#include "./UnaryOperation.h"
#include <algorithm>
#include <math.h>
#include <string>

/**
 * Adds two audio buffers together.
 */
class Add : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a + b;
  }
};

class Subtract : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a - b;
  }
};

class Minus : public UnaryOperation {
private:
  inline void processSample(float &in, float &out) { out = -in; }
};

/**
 * Multiplies a signal by a k-rate constant.
 */
class Multiply : public BinaryOperation {
public:
  std::string describe() override { return "Multiply"; }
  inline void processSample(float &a, float &b, float &out) override {
    out = a * b;
  }
};

class Divide : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a / b;
  }
};

class Invert : public UnaryOperation {
private:
  inline void processSample(float &in, float &out) { out = 1.0 / in; }
};

class Pow : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) { out = pow(a, b); }
};

class Sq : public UnaryOperation {
private:
  inline void processSample(float &in, float &out) { out = in * in; }
};

class Sqrt : public UnaryOperation {
private:
  inline void processSample(float &in, float &out) { out = sqrt(in); }
};

class Clip : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) {
    if (a > 0) {
      if (a > abs(b))
        out = abs(b);
      else
        out = a;
    } else {
      if (-a > abs(b))
        out = -abs(b);
      else
        out = a;
    }
  }
};
