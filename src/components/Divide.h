#include "../connect.h"
#include "./BinaryOperation.h"

class Divide : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a / b;
  }
};

Divide &divide(Component &a, Component &b);
Divide &divide(float a, Component &b);
Divide &divide(Component &a, float b);
Divide &divide(UntypedWriter &a, Component &b);
Divide &divide(Component &a, UntypedWriter &b);
Divide &divide(UntypedWriter &a, UntypedWriter &b);
Divide &divide(float a, UntypedWriter &b);
Divide &divide(UntypedWriter &a, float b);

Divide &operator/(Component &a, Component &b);
Divide &operator/(float a, Component &b);
Divide &operator/(Component &a, float b);
Divide &operator/(UntypedWriter &a, Component &b);
Divide &operator/(Component &a, UntypedWriter &b);
Divide &operator/(UntypedWriter &a, UntypedWriter &b);
Divide &operator/(float a, UntypedWriter &b);
Divide &operator/(UntypedWriter &a, float b);
