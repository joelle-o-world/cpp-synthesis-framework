#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>

template <typename T, int size> class BufferPool {
  T **a;

  int busy;
  int active;
  int capacity;

  void increaseCapacity() {}

public:
  BufferPool(int initialCapacity = 64) {
    busy = 0;
    active = 0;
    a = (T **)malloc(sizeof(T *) * initialCapacity);
    capacity = initialCapacity;
    for (int i = 0; i < capacity; ++i)
      a[i] = (T *)std::malloc(size * sizeof(T *));
  }

  T *allocate(int &n) {
    n = busy;
    ++busy;
    return a[n];
  }

  void release(int n) {
    --busy;
    T *tmp = a[busy];
    a[busy] = a[n];
    a[n] = tmp;
    // ie, swap(a[n], a[--busy]);
  }
};
