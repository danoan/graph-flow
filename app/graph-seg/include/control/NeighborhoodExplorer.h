#ifndef GRAPH_FLOW_APP_GRAPH_SEG_NeighborhoodExplorer_h
#define GRAPH_FLOW_APP_GRAPH_SEG_NeighborhoodExplorer_h

#include <magLac/core/base/Range.hpp>
#include <magLac/core/single/Combinator.hpp>
#include <magLac/core/multithread/Trigger.h>
#include <magLac/core/multithread/ThreadInput.h>


namespace App {
template<class TCombinator, class TUserVars, class TParams, class TContext>
class NeighborhoodExplorer {
 public:
  typedef TCombinator MyCombinator;
  typedef TUserVars UserVars;
  typedef TParams Params;
  typedef TContext Context;

  typedef typename MyCombinator::MyResolver MyResolver;

  typedef typename magLac::Core::MultiThread::ThreadInput<MyCombinator, UserVars, Params> MyThreadInput;
  typedef typename magLac::Core::MultiThread::Trigger<MyThreadInput> MyThreadTrigger;
  typedef typename magLac::Core::MultiThread::ThreadControl ThreadControl;

  typedef std::function<void(const Context &, MyResolver &, MyThreadInput &, ThreadControl &)> VisitNeighborFunction;

 public:
  NeighborhoodExplorer(MyCombinator &combinator, const Context &context);
  void start(VisitNeighborFunction vnf, int numThreads);

  auto begin() { return threadTrigger->threadInputVector.begin(); }
  auto end() { return threadTrigger->threadInputVector.end(); }

  ~NeighborhoodExplorer();

 private:
  MyCombinator combinator;
  const Context &context;

  MyThreadTrigger *threadTrigger;
};

template<class TTUserVars, class TTParams, class TRange, class TContext>
auto createNeighhborExplorer(TRange &range, const TContext &context);
}

#include "NeighborhoodExplorer.hpp"

#endif /* GRAPH_FLOW_APP_GRAPH_SEG_NeighborhoodExplorer_h */
