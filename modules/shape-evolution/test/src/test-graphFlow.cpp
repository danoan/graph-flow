#include "catch.hpp"
#include <string>
#include <sstream>

#include <graph-flow/utils/digital/shapes.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/core/neighborhood/RandomNeighborhood.h>
#include <graph-flow/shape-evolution/shape-evolution.h>

using namespace GraphFlow::ShapeEvolution;
using namespace GraphFlow::Core::Neighborhood;

TEST_CASE("shape evolution execution", "[shape-evolution]") {
  using namespace DGtal::Z2i;

  DigitalSet ds = GraphFlow::Utils::Digital::Shapes::flower(0.5,0,0,20);

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
        REQUIRE(gfIteration.iteration<40);    
        //REQUIRE(gfIteration.value == Catch::Approx(1.22).margin(0.1));
        break;
      }
    }

  };

  Morphology M(Morphology::MorphologyElement::CIRCLE, 2);
  Random R(20);
  GraphFlowInput gfi(ds);
  gfi.h = 0.5;

  SECTION("fixed number of iterations") {    
    gfi.iterations = 31;
    graphFlow(gfi, M, ss,callback);
  }

  SECTION("unlimited number of iterations") {    
    gfi.iterations = -1;
    graphFlow(gfi, M, ss,callback);
  }

  SECTION("positive tolerance") {    
    gfi.iterations = 31;
    gfi.tolerance = 1e-1;

    graphFlow(gfi, M, ss,callback);
  }    

  SECTION("random neighborhood") {    
    gfi.iterations = 10;
    graphFlow(gfi, R, ss,callback);
  }  

}