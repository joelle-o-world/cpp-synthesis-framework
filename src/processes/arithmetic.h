#pragma once

#include "../AudioProcess.h"
#include <algorithm>
#include <math.h>

/**
 * Adds two audio buffers together.
 */
class Add : public BinaryOperationProcess {
private:
  inline void processSample(float &a, float &b, float &out) override { out = a + b; }
};

class Subtract : public BinaryOperationProcess {
private:
  inline void processSample(float &a, float &b, float &out) override { out = a - b; }
};

class Minus : public UnaryOperationProcess {
private:
  inline void processSample(float &in, float &out) { out = -in; }
};

/**
 * Multiplies a signal by a k-rate constant.
 */
class Multiply : public BinaryOperationProcess {
public:
  inline void processSample (float &a, float &b, float &out) override {
    out = a * b;
  }
};


class Divide : public BinaryOperationProcess {
  private:
    inline void processSample(float &a, float &b, float &out) override {
      out = a / b;
    }
};

class Invert : public UnaryOperationProcess {
  private:
    inline void processSample(float &in, float &out) {
      out = 1.0 / in;
    }
};

class Pow : public BinaryOperationProcess {
  private:
    inline void processSample(float &a, float &b, float &out) {
      out = pow(a, b);
    }
};

class Sq : public UnaryOperationProcess {
  private:
    inline void processSample(float &in, float &out) {
      out = in * in;
    }
};

class Sqrt : public UnaryOperationProcess {
  private:
    inline void processSample(float &in, float &out) {
      out = sqrt(in);
    }
};

class Clip : public BinaryOperationProcess {
  private:
    inline void processSample(float &a, float &b, float &out) {
      if(a > 0) {
        if(a > abs(b))
          out = abs(b);
        else
         out = a;
      } else {
        if(-a > abs(b))
          out = -abs(b);
        else
         out = a;
      }
    }
};
