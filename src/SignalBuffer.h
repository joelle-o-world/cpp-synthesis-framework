#pragma once

template <typename Sample = float> class SignalBuffer {
  const int numberOfChannels;
  const int numberOfFrames;
  const int size;
  const Sample *data;

  SignalBuffer(int channels, int frames)
      : numberOfChannels(channels), numberOfFrames(frames),
        size(frames * channels) {
    data = new Sample[channels * frames];
  }

  ~SignalBuffer() { delete data; }

  /**
   * Resize the data, writing the result into the given container
   */
  template <typename Sample1, typename Sample2>
  static void resize(SignalBuffer<Sample1> &from, SignalBuffer<Sample2> &into) {
    // TODO: For efficiont interpolation, bake antruct { int i0, i1; float
    // scale0, scale1; } resizeCoeffs[into.size]; and store as class prop on the
    // resize process
    for (int intoIndex = 0; intoIndex < into.size(); ++intoIndex) {
      // TODO: Rework this with pen and paper
      int intoChannel = intoIndex % into.numberOfChannels;
      int intoTime = intoIndex / into.numberOfChannels;
      int fromChannel =
          (intoChannel * from.numberOfChannels) / into.numberOfChannels;
      int fromTime = intoTime * from.numberOfFrames / into.numberOfFrames;
      int fromIndex = fromTime * from.numberOfChannels + fromChannel;
    }
  };
};
