#pragma once

#include "AudioProcess.h"
#include "TypedSignalBuffer.h"
#include <algorithm>
#include <set>
#include <vector>

#include <iostream>

class Circuit {
private:
  AudioProcess *exitNode;
  std::vector<AudioProcess *> firingOrder;

public:
  Circuit(AudioProcess *exitNode) : exitNode(exitNode) {}
  Circuit(AudioProcess &exitNode) : exitNode(&exitNode) {}
  ~Circuit() { deallocateBuffers(); }

  void process() {
    for (AudioProcess *node : firingOrder)
      node->processStatefully();
  }

  void prepare() {
    refreshFiringOrder();
    allocateBuffers();
  }

  TypedSignalBuffer *exitBuffer() { return exitNode->outputs[0].buffer; }

private:
  /**
   * Recalculates the firing order for all nodes and saves to `firingOrder`
   * property.
   */
  std::vector<AudioProcess *> &refreshFiringOrder() {
    firingOrder.clear();
    firingOrder.push_back(exitNode);
    for (int i = 0; i < firingOrder.size(); ++i) {
      std::set<AudioProcess *> *dependencies = firingOrder[i]->dependencies();
      for (AudioProcess *dependency : *dependencies) {
        if (std::find(firingOrder.begin(), firingOrder.end(), dependency) ==
            firingOrder.end()) {
          firingOrder.push_back(dependency);
        }
      }
      delete dependencies;
    }
    std::reverse(firingOrder.begin(), firingOrder.end());
    return firingOrder;
  }

  void allocateBuffers() {
    // TODO: This could be optimised with a buffer pool
    std::cout << "Allocating buffers...\n";
    for (AudioProcess *node : firingOrder)
      for (Outlet &outlet : node->outputs) {
        std::cout << "Allocating a buffer\n";
        outlet.buffer = new TypedSignalBuffer;
        outlet.buffer->type = Stereo;
        outlet.buffer->stereo = (StereoBuffer *)(void *)new StereoBuffer;
        for (Inlet *inlet : outlet.connectedTo)
          inlet->buffer = outlet.buffer;
      }
  }

  void deallocateBuffers() {
    for (AudioProcess *node : firingOrder)
      for (Outlet &outlet : node->outputs) {
        // TODO: delete outlet.buffer->stereo
        delete outlet.buffer;
        outlet.buffer = nullptr;
        for (Inlet *inlet : outlet.connectedTo)
          inlet->buffer = nullptr;
      }
  }
};
