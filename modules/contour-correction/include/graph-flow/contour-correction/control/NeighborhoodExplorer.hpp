#include "NeighborhoodExplorer.h"

namespace GraphFlow::ContourCorrection {
template <class TCombinator, class TThreadData, class TContext>
NeighborhoodExplorer<TCombinator, TThreadData,
                     TContext>::~NeighborhoodExplorer() {
  for (auto it = this->begin(); it != this->end(); ++it) {
    for (auto ep : it->mutableData.candidatesVector) delete ep.ds;
  }
  delete threadTrigger;
}

template <class TCombinator, class TThreadData, class TContext>
NeighborhoodExplorer<TCombinator, TThreadData, TContext>::NeighborhoodExplorer(
    MyCombinator &combinator, const MyContext &context)
    : combinator(combinator), context(context) {}

template <class TCombinator, class TThreadData, class TContext>
void NeighborhoodExplorer<TCombinator, TThreadData, TContext>::start(
    VisitNeighborFunction vnf, int numThreads) {
  typename MyThreadData::ConstantData params;
  const MyContext &myContext = this->context;

  threadTrigger = new MyThreadTrigger(numThreads, 1);
  threadTrigger->start(combinator, params,
                       [&myContext, &vnf](MyThreadInfo &&ti) mutable {
                         vnf(myContext, std::move(ti));
                       }

  );
}

template <class TThreadData, class TRange, class TContext>
auto createNeighborExplorer(TRange &range, const TContext &context) {
  auto src = magLac::Core::Combinator(range);
  typedef decltype(src) MyCombinator;
  return NeighborhoodExplorer<MyCombinator, TThreadData, TContext>(src,
                                                                   context);
}

}  // namespace GraphFlow::ContourCorrection