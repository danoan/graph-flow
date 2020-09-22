#include "model/graph/GraphContext.h"

namespace App::Graph
{
Context::Context(const GraphSegInput& gfi, const DigitalSet& ds, const RandomNeighborhood& neighborhood)
:gfi(gfi),
neighborhood(neighborhood),
ds(ds){}
}