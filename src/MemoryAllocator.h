#include <vector>
template <typename Buffer> class MemoryAllocator {
private:
  std::vector<Buffer> a;
  int capacity;
  int active;
  int busy;

public:
  typedef struct {
    Buffer *ptr;
    int position;
  } BufferPtr;

  Buffer *allocate() {
    if (busy == active) {
      if (active < capacity) {
        a[active] = new Buffer;
        ++active;
      } else {
        // TODO: copy array into larger newly allocated array;
        // TODO: update capacity;
      }
    }
    ++busy;
    return a[busy - 1];
  }

  void release(int position) { swap(a[position], a[--busy]); }
};
