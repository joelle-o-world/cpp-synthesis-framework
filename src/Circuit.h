#pragma once

#include "AudioProcess.h"
#include <set>
#include <vector>

class Circuit {
  AudioProcess *exitNode;
  std::vector<AudioProcess *> firingOrder;

  Circuit(AudioProcess *exitNode) { exitNode = exitNode; }

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
    return firingOrder;
  }
};
