#include "graph-seg.h"

namespace App {

template<class TNeighExplorer>
void buildBestSolution(DigitalSet &solution, TNeighExplorer &neighExplorer) {

  std::vector<App::Candidate> allCandidates;
  for (auto it = neighExplorer.begin(); it!=neighExplorer.end(); ++it) {
    allCandidates.insert(allCandidates.end(),
                         it->vars.vectorOfCandidates.begin(),
                         it->vars.vectorOfCandidates.end());
  }

  std::sort(allCandidates.begin(),
            allCandidates.end(),
            [](const App::Candidate &c1, const App::Candidate &c2) {
              if(c1.id == c2.id) return c1.value < c2.value;
              else return c1.id < c2.id;
            });

  int lastId=-1;
  auto it = allCandidates.begin();
  while(it!=allCandidates.end()){
    solution += *(it->ds);
    lastId = it->id;

    while(it!=allCandidates.end() && it->id==lastId) ++it;
  }
}
}