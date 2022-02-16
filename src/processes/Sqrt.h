#include "UnaryOperation.h"
#include <math.h>

class Sqrt : public UnaryOperation {
private:
  inline void processSample(float &in, float &out) { out = sqrt(in); }
};
