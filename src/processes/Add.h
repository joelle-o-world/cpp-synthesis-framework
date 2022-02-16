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

Add &add(AudioProcess &a, AudioProcess &b);
Add &add(float a, AudioProcess &b);
Add &add(AudioProcess &a, float b);
Add &add(Outlet &a, AudioProcess &b);
Add &add(AudioProcess &a, Outlet &b);
Add &add(Outlet &a, Outlet &b);
Add &add(float a, Outlet &b);
Add &add(Outlet &a, float b);

Add &operator+(AudioProcess &a, AudioProcess &b);
Add &operator+(float a, AudioProcess &b);
Add &operator+(AudioProcess &a, float b);
Add &operator+(Outlet &a, AudioProcess &b);
Add &operator+(AudioProcess &a, Outlet &b);
Add &operator+(Outlet &a, Outlet &b);
Add &operator+(float a, Outlet &b);
Add &operator+(Outlet &a, float b);
