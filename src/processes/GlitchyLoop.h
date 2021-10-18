#pragma once

#include "../AudioProcess.h"
#include "../wavetables.h"
#include "./Osc.h"
#include "./Multiply.h"


class GlitchyLoop: public AudioProcess {
  public: 
    StereoBuffer internalBuffer;
    Osc osc1;
    Multiply multiply;

    GlitchyLoop(): AudioProcess(1, 1) {
      initialiseBuffer(sineWavetable, 10, .2);

    }

    void initialiseBuffer(Wavetable& wavetable, float frequency, float phaseShift) {
      float phase = phaseShift;
      Osc singleUseOsc;
      singleUseOsc.setPhase(phaseShift);
      singleUseOsc.process(frequency, internalBuffer);
    }

    void process() {
      TypedSignalBuffer &f = *inputs[0], 
                        &out = *outputs[0];

      if(out.type != Stereo)
        throw "output must be stereo";

      else {
        if(f.type == Stereo)
          process(*f.stereo, *out.stereo);
        else if(f.type == Mono)
          process(*f.mono, *out.stereo);
        else if(f.type == Constant)
          process(*f.constant, *out.stereo);
        else
         throw "Unexpected io";
      }

    }

    template<typename Frequency>
    void process(Frequency& f, StereoBuffer& out) {
      osc1.process(f, out);
      multiply.process(internalBuffer, out, out);
    }
};
