#pragma once
#include "processes.h"

void connect(float constant, Inlet &inlet);
Decay &decay(float halfLife);
Decay &decay(AudioProcess &halfLife);
Osc &osc(float frequency);
Osc &osc(AudioProcess &frequency);
Multiply &multiply(AudioProcess &a, AudioProcess &b);
Multiply &operator*(AudioProcess &a, AudioProcess &b);
Add &add(AudioProcess &a, AudioProcess &b);
Add &operator+(AudioProcess &a, AudioProcess &b);
