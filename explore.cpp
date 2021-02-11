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
