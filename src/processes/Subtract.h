#include "../connect.h"
#include "./BinaryOperation.h"

class Subtract : public BinaryOperation {
private:
  inline void processSample(float &a, float &b, float &out) override {
    out = a - b;
  }
};

Subtract &subtract(AudioProcess &a, AudioProcess &b);
Subtract &subtract(float a, AudioProcess &b);
Subtract &subtract(AudioProcess &a, float b);
Subtract &subtract(Outlet &a, AudioProcess &b);
Subtract &subtract(AudioProcess &a, Outlet &b);
Subtract &subtract(Outlet &a, Outlet &b);
Subtract &subtract(float a, Outlet &b);
Subtract &subtract(Outlet &a, float b);

Subtract &operator-(AudioProcess &a, AudioProcess &b);
Subtract &operator-(float a, AudioProcess &b);
Subtract &operator-(AudioProcess &a, float b);
Subtract &operator-(Outlet &a, AudioProcess &b);
Subtract &operator-(AudioProcess &a, Outlet &b);
Subtract &operator-(Outlet &a, Outlet &b);
Subtract &operator-(float a, Outlet &b);
Subtract &operator-(Outlet &a, float b);
