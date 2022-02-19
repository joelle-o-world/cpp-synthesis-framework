#include "../connect.h"
#include "./BinaryOperation.h"

class Subtract : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a - b;
  }
};

Subtract &subtract(Component &a, Component &b);
Subtract &subtract(float a, Component &b);
Subtract &subtract(Component &a, float b);
Subtract &subtract(UntypedWriter &a, Component &b);
Subtract &subtract(Component &a, UntypedWriter &b);
Subtract &subtract(UntypedWriter &a, UntypedWriter &b);
Subtract &subtract(float a, UntypedWriter &b);
Subtract &subtract(UntypedWriter &a, float b);

Subtract &operator-(Component &a, Component &b);
Subtract &operator-(float a, Component &b);
Subtract &operator-(Component &a, float b);
Subtract &operator-(UntypedWriter &a, Component &b);
Subtract &operator-(Component &a, UntypedWriter &b);
Subtract &operator-(UntypedWriter &a, UntypedWriter &b);
Subtract &operator-(float a, UntypedWriter &b);
Subtract &operator-(UntypedWriter &a, float b);
