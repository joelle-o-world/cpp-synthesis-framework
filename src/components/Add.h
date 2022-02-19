#include "../connect.h"
#include "./BinaryOperation.h"

/**
 * Adds two audio buffers together.
 */
class Add : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a + b;
  }
};

Add &add(Component &a, Component &b);
Add &add(float a, Component &b);
Add &add(Component &a, float b);
Add &add(UntypedWriter &a, Component &b);
Add &add(Component &a, UntypedWriter &b);
Add &add(UntypedWriter &a, UntypedWriter &b);
Add &add(float a, UntypedWriter &b);
Add &add(UntypedWriter &a, float b);

Add &operator+(Component &a, Component &b);
Add &operator+(float a, Component &b);
Add &operator+(Component &a, float b);
Add &operator+(UntypedWriter &a, Component &b);
Add &operator+(Component &a, UntypedWriter &b);
Add &operator+(UntypedWriter &a, UntypedWriter &b);
Add &operator+(float a, UntypedWriter &b);
Add &operator+(UntypedWriter &a, float b);
