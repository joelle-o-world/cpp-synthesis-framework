#pragma once

#include "AudioProcess.h"
#include "TypedSignalBuffer.h"
#include <algorithm>
#include <iterator>
#include <ostream>
#include <set>
#include <string>
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
    for (AudioProcess *node : firingOrder)
      for (Outlet &outlet : node->outputs) {
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

public:
  void dotGraph(std::ostream &out) {
    int constantCount = 0;
    out << "digraph {\n";
    out << "  p0 -> adac\n";
    for (int i = 0; i < firingOrder.size(); ++i) {
      AudioProcess *p = firingOrder[i];
      std::string iname = "p" + std::to_string(i);
      out << "  p" << i << " ";
      out << "[label=\"" << p->describe() << "\"]";
      out << "\n";
      for (Inlet &inlet : p->inputs) {
        if (inlet.connectedTo) {
          auto it = std::find(firingOrder.begin(), firingOrder.end(),
                              inlet.connectedTo->owner);
          if (it != firingOrder.end()) {
            int j = std::distance(firingOrder.begin(), it);

            std::string jname = "p" + std::to_string(j);

            out << "  " << jname << " -> " << iname << "\n";
          }
        } else if (inlet.isConstant && inlet.buffer->type == Constant) {
          auto value = inlet.buffer->constant;
          std::string constantName = "c" + std::to_string(constantCount++);
          out << "  " << constantName << " ";
          out << "[label=\"" << std::to_string(*value) << "\"]";
          out << " { border: 1px dotted black; }\n";
          out << "\n";

          out << "  " << constantName << " -> " << iname << "\n";
        }
      }
    }
    out << "}\n";
  }
};
