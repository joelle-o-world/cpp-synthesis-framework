#pragma once

#include "AudioProcess.h"
#include "TypedSignalBuffer.h"
#include <algorithm>
#include <set>
#include <vector>

class Circuit {
private:
  AudioProcess *exitNode;
  std::vector<AudioProcess *> firingOrder;

public:
  Circuit(AudioProcess *exitNode) { exitNode = exitNode; }

  void process() {
    for (AudioProcess *node : firingOrder)
      node->processStatefully();
  }

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
    for (AudioProcess *node : firingOrder)
      for (Outlet &outlet : node->outputs) {
        outlet.buffer = new TypedSignalBuffer;
        for (Inlet *inlet : outlet.connectedTo)
          inlet->buffer = outlet.buffer;
      }
  }

  void deallocateBuffers() {
    for (AudioProcess *node : firingOrder)
      for (Outlet &outlet : node->outputs) {
        delete outlet.buffer;
        outlet.buffer = nullptr;
        for (Inlet *inlet : outlet.connectedTo)
          inlet->buffer = nullptr;
      }
  }
};
