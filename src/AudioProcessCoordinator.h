#pragma once

#include <vector>

#include "./AudioProcess.h"

class Inlet;
class Outlet;

/**
 * Base class for audio process coordinators.
 *
 * Coordinators are responsible for carrying meta data about audio processes
 * and provide an interface for combining them into larger structures (called
 * circuits).
 *
 *
 */
class AudioProcessCoordinator {
  private:
    /**
     * The `AudioProcess` instance being coordinated.
     */
    AudioProcess* process;

  public:
    std::vector<Inlet&> inlets;
    std::vector<Outlet&> outlets;

};

class Inlet {
  public:
    /**
     * The process coordinator which owns this inlet.
     */
    AudioProcessCoordinator& owner;

    /**
     * Returns `true` if inlet has a connection.
     */
    bool isConnected() { 
      return connectedTo != NULL;
    };

    /**
     * Returns true if the inlet has no connection.
     */
    bool isFree() {
      return connectedTo == NULL;
    }

    /**
     * The outlet this inlet is connected to, or `NULL` if there is no
     * connection.
     */
    Outlet* connectedTo = NULL;
};

class Outlet {
  public:
    /**
     * The process coordinator which owns this outlet.
     */
    AudioProcessCoordinator& owner;

    /**
     * The inlets connected to this outlet.
     */
    std::vector<Inlet*> connections;
};
