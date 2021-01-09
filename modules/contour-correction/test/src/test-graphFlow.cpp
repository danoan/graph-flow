#include "catch.hpp"
#include <string>
#include <sstream>

#include <graph-flow/utils/digital/shapes.h>
#include <graph-flow/utils/digital/representation.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/contour-correction/graph-seg.h>
#include <graph-flow/io/seed/GrabCutObject.h>

using namespace DGtal::Z2i;
using namespace GraphFlow::ContourCorrection;
using namespace GraphFlow::Core::Neighborhood;
using namespace GraphFlow::IO;

DigitalSet prepareShape(const Image::DataDistribution& DD) {
  const cv::Mat& segResult = DD.segResultImg;

  Domain imgDomain(Point(0, 0), Point(segResult.cols - 1, segResult.rows - 1));
  DigitalSet tempDS(imgDomain);

  // Convert inputImg to 1-channel grayscale image.
  cv::Mat grayscale(segResult.size(), segResult.type());
  if (segResult.type() != CV_8UC1)
    cv::cvtColor(segResult, grayscale, cv::COLOR_RGB2GRAY, 1);
  else
    grayscale = segResult;

  GraphFlow::Utils::Digital::Representation::CVMatToDigitalSet(tempDS, grayscale, 1);
  return tempDS;
}

TEST_CASE("contour correction execution", "[contour-correction]") {
  std::string gcoInputFilepath = MY_MAIN_DIR;
  gcoInputFilepath += "/modules/contour-correction/test/input/coala.xml";

  Seed::GrabCutObject gco = Seed::read(gcoInputFilepath);
  Image::DataDistribution DD(gco, 10);

  DigitalSet ds = prepareShape(DD);
  GraphSegInput gsi(ds, DD);
  gsi.h = 0.25;
  gsi.iterations = 10;

  Morphology M(Morphology::MorphologyElement::CIRCLE, 2);
  
  std::string s;
  std::stringstream ss(s);

  IterationCallback callback = [](const GraphSegIteration& gsIteration)->void{
     const DigitalSet& ds = gsIteration.ds;

    switch(gsIteration.iterationState){
      case GraphSegIteration::Init:
      {
        REQUIRE(gsIteration.iteration==0);        
        break;
      }
      case GraphSegIteration::Running:
      {
        REQUIRE(gsIteration.iteration>0);        
        break;
      }
      case GraphSegIteration::End:
      {
        REQUIRE(gsIteration.iteration==11);        
        break;
      }
    }

  };

  graphSeg(gsi, M, ss,callback);
}