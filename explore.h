#pragma once

#include <vector>
#include <set>
#include <algorithm>
#include <map>

#include "Process.h"


std::vector<Process*>* explore(Process* startingPoint);
int assignBuffers(std::vector<Process*>& orderedProcesses);
