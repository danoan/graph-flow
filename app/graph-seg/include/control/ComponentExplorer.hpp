#include "ComponentExplorer.h"

namespace App {
template<class TCombinator, class TUserVars, class TParams, class TContext>
ComponentExplorer<TCombinator, TUserVars, TParams, TContext>::~ComponentExplorer() {
  for (auto it = this->begin(); it!=this->end(); ++it) {
    for (auto ep:it->vars.vectorOfCandidates) delete ep.ds;
  }
  delete threadTrigger;
}

template<class TCombinator, class TUserVars, class TParams, class TContext>
ComponentExplorer<TCombinator, TUserVars, TParams, TContext>::ComponentExplorer(MyCombinator &combinator,
                                                                                      const Context &context):
    combinator(combinator),
    context(context) {}

template<class TCombinator, class TUserVars, class TParams, class TContext>
void ComponentExplorer<TCombinator, TUserVars, TParams, TContext>::start(VisitNeighborFunction vnf, int numThreads) {
  Params params;
  const Context &myContext = this->context;
  threadTrigger = new MyThreadTrigger(numThreads,
                                      1,
                                      [&myContext, &vnf](MyResolver &resolver, MyThreadInput &ti, ThreadControl &tc) {
                                        vnf(myContext, resolver, ti, tc);
                                      }

  );
  threadTrigger->start(combinator, params);
}

template<class TUserVars, class TParams, class TRange, class TContext>
auto createNeighborExplorer(TRange &range, const TContext &context) {
  auto src = magLac::Core::Single::createCombinator(range);
  typedef decltype(src) MyCombinator;
  return ComponentExplorer<MyCombinator, TUserVars, TParams, TContext>(src, context);
}

}