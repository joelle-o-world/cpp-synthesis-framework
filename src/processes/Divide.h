#include "../connect.h"
#include "./BinaryOperation.h"

class Divide : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a / b;
  }
};

Divide &divide(AudioProcess &a, AudioProcess &b);
Divide &divide(float a, AudioProcess &b);
Divide &divide(AudioProcess &a, float b);
Divide &divide(Outlet &a, AudioProcess &b);
Divide &divide(AudioProcess &a, Outlet &b);
Divide &divide(Outlet &a, Outlet &b);
Divide &divide(float a, Outlet &b);
Divide &divide(Outlet &a, float b);

Divide &operator/(AudioProcess &a, AudioProcess &b);
Divide &operator/(float a, AudioProcess &b);
Divide &operator/(AudioProcess &a, float b);
Divide &operator/(Outlet &a, AudioProcess &b);
Divide &operator/(AudioProcess &a, Outlet &b);
Divide &operator/(Outlet &a, Outlet &b);
Divide &operator/(float a, Outlet &b);
Divide &operator/(Outlet &a, float b);
