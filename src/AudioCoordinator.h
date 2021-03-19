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
 */
class AudioCoordinator {
  private:
    /**
     * The AudioProcess instance being coordinated.
     */
    AudioProcess* process;

  public:
    std::vector<Inlet&> inlets;
    std::vector<Outlet&> outlets;

};

class Inlet {
};

class Outlet {
};
