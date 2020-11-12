#include <boost/filesystem.hpp>

#include <opencv2/highgui.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>

#include <graph-flow/utils/display.h>
#include <graph-flow/utils/string.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/core/neighborhood/RandomNeighborhood.h>

#include "input/InputData.h"
#include "input/InputReader.h"
#include "model/GraphFlowInput.h"
#include "model/GraphFlowIteration.h"

#include "utils.h"
#include "graph-flow.h"

using namespace DGtal::Z2i;
using namespace GraphFlow::Core;
using namespace GraphFlow::Utils;


DigitalSet prepareShapeAndMask(const App::InputData& id)
{
  DigitalSet _ds = Digital::resolveShape(id.shapeName,id.h);
  Point lb,ub;

  _ds.computeBoundingBox(lb,ub);
  Point border(id.border/id.h,id.border/id.h);
  Point shift = -lb+border;

  return DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,border);
}

int main(int argc, char* argv[])
{
  App::InputData id = App::readInput(argc,argv);
  boost::filesystem::create_directories(id.outputFolder);

  DigitalSet ds = prepareShapeAndMask(id);
  App::GraphFlowInput gfi(id,ds);

  std::ofstream ofsInputData(id.outputFolder + "/inputData.txt");
  writeInputData(id,ds.size(),ofsInputData);
  ofsInputData.flush(); ofsInputData.close();

  std::ofstream ofsEnergy(id.outputFolder + "/energy.txt");
  std::string windowName="IterationViewer";

  App::IterationCallback iterationCallback=[&windowName,&id,&ofsEnergy](const App::GraphFlowIteration& gfIteration)->void
  {
    const DigitalSet& ds = gfIteration.ds;

    switch(gfIteration.iterationState){
      case App::GraphFlowIteration::Init:
      {
        if(id.saveAllFigures){
          Display::saveDigitalSetAsImage(ds,id.outputFolder+"/" + String::nDigitsString(gfIteration.iteration,4) + ".png");
        }

        if(id.displayFlow){
          cv::namedWindow(windowName);
        }
        break;
      }
      case App::GraphFlowIteration::Running:
      {
        if(id.saveAllFigures){
          Display::saveDigitalSetAsImage(ds,id.outputFolder+"/" + String::nDigitsString(gfIteration.iteration,4) + ".png");
        }

        if(id.printEnergyValue){
          App::Utils::writeEnergyData(gfIteration,std::cout);
        }

        if(id.displayFlow){
          DigitalSet::Point size = ds.domain().upperBound() - ds.domain().lowerBound() + DigitalSet::Point(1,1);
          cv::Mat cvImg = cv::Mat::zeros( size[1],size[0],CV_8UC1);
          DIPaCUS::Representation::digitalSetToCVMat(cvImg,gfIteration.ds);
          cv::imshow(windowName,cvImg);
          cv::waitKey(10);
          break;
        }

        App::Utils::writeEnergyData(gfIteration,ofsEnergy);
      }
      case App::GraphFlowIteration::End:
      {
        if(id.displayFlow){
          std::cout << "End of flow. Press any key to continue." << std::endl;
          cv::waitKey(0);
        }
        break;
      }
    }

  };

  Timer T;
  T.start();

  switch(id.neighborhoodType){
    case App::InputData::Morphology:{
      GraphFlow::Core::Neighborhood::Morphology M(GraphFlow::Core::Neighborhood::Morphology::MorphologyElement::CIRCLE,id.neighborhoodSize);
      graphFlow(gfi,M,ofsEnergy,iterationCallback);
      break;
    }
    case App::InputData::Random:{
      GraphFlow::Core::Neighborhood::Random R(id.neighborhoodSize);
      graphFlow(gfi,R,ofsEnergy,iterationCallback);
      break;
    }
  }

  ofsEnergy << "#Execution time: ";
  T.end(ofsEnergy);
  ofsEnergy.flush(); ofsEnergy.close();

  return 0;
}


