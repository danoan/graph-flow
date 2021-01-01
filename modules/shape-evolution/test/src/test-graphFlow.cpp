#include "catch.hpp"
#include <string>
#include <sstream>

#include <DIPaCUS/base/Shapes.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/shape-evolution/shape-evolution.h>

using namespace GraphFlow::ShapeEvolution;
using namespace GraphFlow::Core::Neighborhood;

TEST_CASE("shape evolution execution", "[shape-evolution]") {
  using namespace DGtal::Z2i;

  DigitalSet ds = DIPaCUS::Shapes::square(0.5,0,0,20);
  GraphFlowInput gfi(ds);
  gfi.h = 0.5;
  gfi.iterations = 30;

  Morphology M(Morphology::MorphologyElement::CIRCLE, 2);
  
  std::string s;
  std::stringstream ss(s);

  IterationCallback callback = [](const GraphFlowIteration& gfIteration)->void{
     const DigitalSet& ds = gfIteration.ds;

    switch(gfIteration.iterationState){
      case GraphFlowIteration::Init:
      {
        REQUIRE(gfIteration.iteration==0);        
        break;
      }
      case GraphFlowIteration::Running:
      {
        REQUIRE(gfIteration.iteration>0);        
        break;
      }
      case GraphFlowIteration::End:
      {
        REQUIRE(gfIteration.iteration==31);        
        REQUIRE(gfIteration.value == Catch::Approx(1.22).margin(0.1));
        break;
      }
    }

  };

  graphFlow(gfi, M, ss,callback);
}