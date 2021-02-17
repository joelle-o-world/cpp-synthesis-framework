#include "explore.h"

std::vector<Process*>* explore(Process* startingPoint) {
  std::vector<Process*>* all = new std::vector<Process*>;
  all->push_back(startingPoint);

  for(int i=0; i < all->size(); ++i) {
    // iterate P's neighbours
    std::set<Process*> *  neighbours = (*all)[i]->neighbours();
    for(Process* q : *neighbours){
      // If q is already in all
      if(find(all -> begin(), all -> end(), q) != all->end())
        continue;
      else
        all->push_back(q);
    }
  }

  return all;
}

using std::cout;
int assignBuffers(std::vector<Process*>& processes) {
  
  using Buffer = float[CHUNK_SIZE];

  std::vector<float*> buffers; 
  std::vector<int> bufferLocks;
  std::map<Outlet*, int> outletBufferAssignments;
  
  // Initialise all inlets to -1
  for(Process* P : processes) {
    for(Outlet* O : P->outlets) {
      outletBufferAssignments[O] = -1;
    }
  }

  //for process, *P* in *PO* (in order)
  for(Process* P : processes) {
    cout << P -> name() << ":\n";
    cout << "\t(priority " << P -> readPriority() << ")\n";
    
    //For each inlet *I* of *P*
    for(Inlet* I : P -> inlets) {
      cout <<  '\t' << I -> name() << ":\n";
      //decrement I's buffer
      if(I->isConnected) {
        // The bug coming from inside this block!
        int bufferIndex = outletBufferAssignments[I->connectedTo];

        if(bufferIndex == -1) {
          throw I->name() + " is connected to " + I->connectedTo->name() + " which has no assigned buffer";
        }

        cout << "\t" << I->name() << " -- decrementing buffer#" << bufferIndex << "\n";
        --bufferLocks[bufferIndex];
        if(bufferLocks[bufferIndex] < 0)
          throw "Buffer lock was decremented too many times";
      }

      // (IMPLICIT) release the buffer if the reader count is 0
    }

    //For each outlet *O* of *P*
    for(Outlet* O : P -> outlets) {
      // Find the first free buffer, *B*
      int bufferIndex = 0;
      while(bufferIndex < bufferLocks.size() && bufferLocks[bufferIndex] > 0)
        bufferIndex++;

      if(bufferIndex == bufferLocks.size()) {
        bufferLocks.push_back(0);
        buffers.push_back( new Buffer );
      }

      // assign *O*'s write pointer to *B*
      O->buffer = buffers[bufferIndex];

      // Add O to the buffer map
      outletBufferAssignments[O] = bufferIndex;

      //for each inlet *J* connected to *O*
      for(Inlet* inlet : O->connectedTo) {
        // assign *J*'s read pointer to *B*
        inlet->buffer = buffers[bufferIndex];

        //increment *B*'s reader count
        ++bufferLocks[bufferIndex];
        cout << "\t" << O->name() << " -- Incrementing buffer#" << bufferIndex << "\n";
      }

      //(IMPLICIT)
      //if *B*'s reader count == 0 (ie. no inlets connected)
        //release *B*
    }

    //(FUTURE FEATURE)
    //For each _locked_ inlet *I* of *P*
      //decrement I's buffer
      //release the buffer if the reader count is 0
      //
  }

  std::cout << "Used " << buffers.size() << " buffers\n";
  return buffers.size();
}
