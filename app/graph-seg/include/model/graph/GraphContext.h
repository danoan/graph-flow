#ifndef GRAPH_FLOW_APP_GRAPH_SEG_GRAPHCONTEXT_H
#define GRAPH_FLOW_APP_GRAPH_SEG_GRAPHCONTEXT_H

#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/utils/digital.h>

#include "model/GraphSegInput.h"
#include "utils.h"

namespace App::Graph{
template<class TNeighborhood>
struct Context{
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef DGtal::Z2i::Domain Domain;

  typedef TNeighborhood Neighborhood;

  Context(const GraphSegInput& gfi, const DigitalSet& ds, const Neighborhood& neighborhood):gfi(gfi),
                                                                                            neighborhood(neighborhood),
                                                                                            ds(ds){}

  Context(const Context& context)=delete;
  Context(Context&& context)=delete;

  const GraphSegInput& gfi;
  const DigitalSet& ds;

  Neighborhood neighborhood;
};


}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_GRAPHCONTEXT_H
