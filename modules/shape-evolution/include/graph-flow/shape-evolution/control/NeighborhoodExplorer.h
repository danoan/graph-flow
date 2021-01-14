#ifndef GRAPH_FLOW_SHAPE_EVOLUTION_NeighborhoodExplorer_h
#define GRAPH_FLOW_SHAPE_EVOLUTION_NeighborhoodExplorer_h

#include <magLac/core/multithread/Trigger.h>

#include <magLac/core/base/Range.hpp>
#include <magLac/core/base/Combinator.h>

namespace GraphFlow::ShapeEvolution {
template <class TCombinator, class TThreadData, class TContext>
class NeighborhoodExplorer {
 public:
  typedef TCombinator MyCombinator;
  typedef TThreadData MyThreadData;
  typedef TContext MyContext;

  typedef typename MyCombinator::MyResolver MyResolver;

  typedef typename magLac::Core::MultiThread::DataChunk<MyCombinator,
                                                          MyThreadData>
      MyThreadDataChunk;

  typedef typename magLac::Core::MultiThread::Trigger<MyThreadDataChunk>
      MyThreadTrigger;

  typedef typename magLac::Core::MultiThread::ThreadControl MyThreadControl;

  typedef magLac::Core::MultiThread::ThreadInfo<MyThreadDataChunk> MyThreadInfo;

  typedef std::function<void(const MyContext&, MyThreadInfo&&)>
      VisitNeighborFunction;

 public:
  NeighborhoodExplorer(MyCombinator& combinator, const MyContext& context);
  void start(VisitNeighborFunction vnf, int numThreads);

  auto begin() { return threadTrigger->begin(); }
  auto end() { return threadTrigger->end(); }

  ~NeighborhoodExplorer();

 private:
  MyCombinator combinator;
  const MyContext& context;

  MyThreadTrigger* threadTrigger;
};

template <class TThreadData, class TRange, class TContext>
auto createNeighhborExplorer(TRange& range, const TContext& context);
}  // namespace GraphFlow::ShapeEvolution

#include "NeighborhoodExplorer.hpp"

#endif /* GRAPH_FLOW_SHAPE_EVOLUTION_NeighborhoodExplorer_h */
