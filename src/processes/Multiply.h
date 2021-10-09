#pragma once

#include "../AudioProcess.h"

/**
 * Multiplies a signal by a k-rate constant.
 */
class _Multiply : public AudioProcess {
  public:
    float a = 1.0;
    float b = 1.0;

    _Multiply(): AudioProcess(2,1) {
      inputs = new SignalBuffer*[2];
      outputs = new SignalBuffer*[1];
    }

    void process() override {
      SignalBuffer& out = *outputs[0];

      if(inputs[0] != nullptr) {
        SignalBuffer& a = *inputs[0];
        if(inputs[1] != nullptr) {
          // a is a-rate, b is a-rate
          SignalBuffer& b = *inputs[1];
          for(int i=0; i < signalChunkSize; ++i)
            out[i] = a[i] * b[i];

        } else
          // a is a-rate, b is k-rate
          for(int i=0; i < signalChunkSize; ++i)
            out[i] = a[i] * b;

      } else {
        if(inputs[1] != nullptr) {
          // a is k-rate, b is a-rate
          SignalBuffer& b = *inputs[1];
          for(int i=0; i < signalChunkSize; ++i)
            out[i] = a * b[i];

        } else
          // 2 k-rate operands. Weird edge case
          for( int i=0; i < signalChunkSize; ++i)
            out[i] = a* b;
      }
    }
};
