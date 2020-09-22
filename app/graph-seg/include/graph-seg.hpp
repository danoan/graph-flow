#include "graph-seg.h"

namespace App {

template<class TNeighExplorer>
double buildBestSolution(DigitalSet &solution, TNeighExplorer &neighExplorer) {

  std::vector<App::Candidate> allCandidates;
  for (auto it = neighExplorer.begin(); it!=neighExplorer.end(); ++it) {
    allCandidates.insert(allCandidates.end(),
                         it->vars.vectorOfCandidates.begin(),
                         it->vars.vectorOfCandidates.end());
  }

  std::sort(allCandidates.begin(),
            allCandidates.end(),
            [](const App::Candidate &c1, const App::Candidate &c2) {
              return c1.value < c2.value;
            });

  solution = *allCandidates[0].ds;
  return allCandidates[0].value;
}
}