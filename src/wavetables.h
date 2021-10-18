#pragma once

#include "./constants.h"
#include <math.h>

const int WAVETABLE_SIZE = 44100;

typedef float Wavetable[WAVETABLE_SIZE];

extern Wavetable sawtoothWavetable;
extern Wavetable sineWavetable;
extern Wavetable squareWavetable;
extern Wavetable triangleWavetable;

void initialiseWavetables();
