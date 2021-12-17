#pragma once

#include <iostream>
#include <vector>

template <typename T, int size> class BufferPool {
  std::vector<T *> a;

  int busy = 0;

public:
  T *allocate(int &n) {
    if (busy == a.size()) {
      T *newbuf = new T[size];
      a.push_back(newbuf);
    }
    n = busy;
    ++busy;
    std::cout << "Returning buffer " << n << " of " << a.size() << "\n";
    std::cout << "Buffer address: " << &a[n] << "\n";
    return a[n];
  }

  void release(int n) {
    auto tmp = a[--busy];
    a[busy] = a[n];
    a[n] = tmp;
    // swap(a[n], a[--busy]);
  }
};
