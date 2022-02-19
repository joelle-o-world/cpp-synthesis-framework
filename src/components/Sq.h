#include "UnaryOperation.h"

class Sq : public UnaryOperation {
private:
  inline void processSample(float &in, float &out) { out = in * in; }
};
