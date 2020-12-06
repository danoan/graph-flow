#include "NeighborhoodExplorer.h"

namespace GraphFlow::ShapeEvolution {
template <class TCombinator, class TUserVars, class TParams, class TContext>
NeighborhoodExplorer<TCombinator, TUserVars, TParams,
                     TContext>::~NeighborhoodExplorer() {
  for (auto it = this->begin(); it != this->end(); ++it) {
    for (auto ep : it->vars.candidatesVector) delete ep.ds;
  }
  delete threadTrigger;
}

template <class TCombinator, class TUserVars, class TParams, class TContext>
NeighborhoodExplorer<TCombinator, TUserVars, TParams,
                     TContext>::NeighborhoodExplorer(MyCombinator &combinator,
                                                     const Context &context)
    : combinator(combinator), context(context) {}

template <class TCombinator, class TUserVars, class TParams, class TContext>
void NeighborhoodExplorer<TCombinator, TUserVars, TParams, TContext>::start(
    VisitNeighborFunction vnf, int numThreads) {
  Params params;
  const Context &myContext = this->context;
  threadTrigger = new MyThreadTrigger(
      numThreads, 1,
      [&myContext, &vnf](MyResolver &resolver, MyThreadInput &ti,
                         ThreadControl &tc) {
        vnf(myContext, resolver, ti, tc);
      }

  );
  threadTrigger->start(combinator, params);
}

template <class TUserVars, class TParams, class TRange, class TContext>
auto createNeighborExplorer(TRange &range, const TContext &context) {
  auto src = magLac::Core::Single::createCombinator(range);
  typedef decltype(src) MyCombinator;
  return NeighborhoodExplorer<MyCombinator, TUserVars, TParams, TContext>(
      src, context);
}

}  // namespace GraphFlow::ShapeEvolution