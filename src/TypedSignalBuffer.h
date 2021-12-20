#pragma once

const int signalChunkSize = 2048;
const int sampleRate = 44100;
const float sampleInterval = 1.0 / float(sampleRate);

typedef float StereoBuffer[signalChunkSize * 2];
typedef float MonoBuffer[signalChunkSize];
typedef float MonoConstant;
typedef float StereoConstant;
typedef void *MIDIBuffer; // TODO: Future

// void copyData(TypedSignalBuffer *from, StereoBuffer *to);
void copyData(float *from, float *to);
