#include "BinaryOperation.h"

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
