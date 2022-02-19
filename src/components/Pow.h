#include "BinaryOperation.h"
#include <math.h>

class Pow : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) { out = pow(a, b); }
};
