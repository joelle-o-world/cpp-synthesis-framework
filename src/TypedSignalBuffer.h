#pragma once

const int signalChunkSize = 2048;
const int sampleRate = 44100;
const float sampleInterval = 1.0 / float(sampleRate);

typedef float StereoBuffer[signalChunkSize * 2];
typedef float MonoBuffer[signalChunkSize];
typedef float MonoConstant;
typedef float StereoConstant;
typedef void *MIDIBuffer; // TODO: Future

enum SignalType : unsigned char { Stereo = 1, Mono, Constant, MIDIData };

struct TypedSignalBuffer {
  SignalType type;

  union {
    StereoBuffer *stereo;
    MonoBuffer *mono;
    float *constant;
    MIDIBuffer *midi;
  };
};

void copyData(TypedSignalBuffer *from, StereoBuffer *to);
