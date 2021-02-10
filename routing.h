#pragma once

#include <vector>
#include "Inlet.h"
#include "Outlet.h"


void connect(Outlet* outlet, Inlet* inlet);
void connect(Outlet* outlet, Process* P);
void connect(Process* P, Inlet* inlet);
void connect(Process* P, Process* Q);

void checkConnection(Outlet* outlet, Inlet* inlet);




