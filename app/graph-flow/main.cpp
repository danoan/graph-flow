#include <boost/filesystem.hpp>

#include <opencv2/highgui.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>

#include <graph-flow/utils/display.h>
#include <graph-flow/utils/string.h>

#include "input/InputData.h"
#include "input/InputReader.h"
#include "model/GraphFlowInput.h"
#include "model/GraphFlowIteration.h"

#include "utils.h"
#include "graph-flow.h"

using namespace DGtal::Z2i;
using namespace GraphFlow::Core;
using namespace GraphFlow::Utils;


std::pair<DigitalSet,DigitalSet> prepareShapeAndMask(const InputData& id)
{
  DigitalSet _ds = Digital::resolveShape(id.shapeName,id.h);
  Point lb,ub;

  _ds.computeBoundingBox(lb,ub);
  Point border(id.border/id.h,id.border/id.h);
  Point shift = -lb+border;

  DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,border);
  DigitalSet pixelMask = getPixelMask(id.pixelMaskFilepath,ds.domain(),shift);

  return std::make_pair(ds,pixelMask);
}


int main(int argc, char* argv[])
{
  InputData id = readInput(argc,argv);

  boost::filesystem::create_directories(id.outputFolder);

  auto shapeAndMask = prepareShapeAndMask(id);
  DigitalSet& ds = shapeAndMask.first;
  DigitalSet& pixelMask = shapeAndMask.second;

  if(pixelMask.size()>0)
    Display::saveDigitalSetAsImage(pixelMask,id.outputFolder + "/pixelMask.pgm");

  GraphFlowInput gfi(id,ds,pixelMask);

  std::ofstream ofsInputData(id.outputFolder + "/inputData.txt");
  writeInputData(id,ofsInputData);
  ofsInputData.flush(); ofsInputData.close();

  std::ofstream ofsEnergy(id.outputFolder + "/energy.txt");

  std::string windowName="IterationViewer";
  if(id.displayFlow){
    cv::namedWindow(windowName);
  }

  IterationCallback iterationCallback=[&windowName,&id,&ofsEnergy](const GraphFlowIteration& gfIteration)->void
  {
    const DigitalSet& ds = gfIteration.ds;

    writeEnergyData(gfIteration,ofsEnergy);
    if(id.saveAllFigures){
      Display::saveDigitalSetAsImage(ds,id.outputFolder+"/" + String::nDigitsString(gfIteration.iteration,4) + ".pgm");
    }

    if(id.printEnergyValue){
      writeEnergyData(gfIteration,std::cout);
    }

    if(id.displayFlow){
      DigitalSet::Point size = ds.domain().upperBound() - ds.domain().lowerBound() + DigitalSet::Point(1,1);
      cv::Mat cvImg = cv::Mat::zeros( size[1],size[0],CV_8UC1);
      DIPaCUS::Representation::digitalSetToCVMat(cvImg,gfIteration.ds);
      cv::imshow(windowName,cvImg);


      if(gfIteration.iterationState==GraphFlowIteration::End){
        std::cout << "End of flow. Press any key to continue." << std::endl;
        cv::waitKey(0);
      }else{
        cv::waitKey(10);  
      }      
      
    }

  };

  Timer T;
  T.start();
  graphFlow(gfi,ofsEnergy,iterationCallback);
  ofsEnergy << "#Execution time: ";
  T.end(ofsEnergy);
  ofsEnergy.flush(); ofsEnergy.close();

  return 0;
}


