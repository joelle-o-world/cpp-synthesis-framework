#pragma once

#include <iostream>
#include <vector>

template <typename T, int size> class BufferPool {
  std::vector<T *> a;

  int busy = 0;

public:
  T *allocate(int &n) {
    if (busy == a.size()) {
      std::cout << "Creating a new buffer.\n";
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
    std::cout << "releasing " << n << ", there are now " << busy
              << " busy buffers\n";
    --busy;
    auto tmp = a[busy];
    a[busy] = a[n];
    a[n] = tmp;
    // swap(a[n], a[--busy]);
    std::cout << "finished releasing\n";
  }
};
