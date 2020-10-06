#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>
#include <BTools/io/seed/GrabCutObject.h>

#include <graph-flow/utils/display.h>
#include <graph-flow/utils/string.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/core/neighborhood/RandomNeighborhood.h>

#include "input/InputData.h"
#include "input/InputReader.h"
#include "model/image/DataDistribution.h"
#include "model/GraphSegInput.h"
#include "model/GraphSegIteration.h"

#include "utils.h"
#include "graph-seg.h"

using namespace DGtal::Z2i;
using namespace GraphFlow::Core;
using namespace GraphFlow::Utils;



DigitalSet prepareShape(const App::Image::DataDistribution& DD)
{
  const cv::Mat& segResult = DD.segResultImg;


  Domain imgDomain(Point(0,0),
                   Point(segResult.cols-1,
                         segResult.rows-1)
  );
  DigitalSet tempDS(imgDomain);

  //Convert inputImg to 1-channel grayscale image.
  cv::Mat grayscale(segResult.size(),
                    segResult.type());
  if(segResult.type()!=CV_8UC1)
    cv::cvtColor(segResult,grayscale,cv::COLOR_RGB2GRAY,1);
  else
    grayscale = segResult;

  DIPaCUS::Representation::CVMatToDigitalSet(tempDS,
                                             grayscale,
                                             1);
  return tempDS;
}

void renderSegmentation(cv::Mat& bcImage, const DigitalSet& ds, const App::Image::DataDistribution& DD){
  cv::Mat foregroundMask = cv::Mat::zeros(DD.segResultImg.size(),
                                          CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(foregroundMask, ds);
  BTools::Utils::setHighlightMask(bcImage, DD.gco.inputImage, foregroundMask);
}

int main(int argc, char* argv[])
{
  App::InputData id = App::readInput(argc,argv);
  boost::filesystem::create_directories(id.outputFolder);

  std::ofstream ofsInputData(id.outputFolder + "/inputData.txt");
  writeInputData(id,ofsInputData);
  ofsInputData.flush(); ofsInputData.close();

  std::ofstream ofsEnergy(id.outputFolder + "/energy.txt");
  ofsEnergy << "#Grabcut execution time: ";
  Timer T_grabcut;
  T_grabcut.start();
  App::Image::DataDistribution DD(id);
  T_grabcut.end(ofsEnergy);


  Domain imgDomain(Point(0,0),
                   Point(DD.segResultImg.cols-1,
                         DD.segResultImg.rows-1));
  DigitalSet ds = prepareShape(DD);
  App::GraphSegInput gsi(id,ds,DD);

  std::string windowName="IterationViewer";

  App::IterationCallback iterationCallback=[&DD,&windowName,&id,&ofsEnergy](const App::GraphSegIteration& gfIteration)->void
  {
    const DigitalSet& ds = gfIteration.ds;
    App::Utils::writeEnergyData(gfIteration,ofsEnergy);

    switch(gfIteration.iterationState){
      case App::GraphSegIteration::Init:{
        if(id.saveAllFigures){
          Display::saveDigitalSetAsImage(ds,id.outputFolder+"/" + String::nDigitsString(gfIteration.iteration,4) + ".png");
        }

        if(id.displayFlow){
          cv::namedWindow(windowName);
        }
        break;
      }
      case App::GraphSegIteration::Running:{
        if(id.saveAllFigures){
          Display::saveDigitalSetAsImage(ds,id.outputFolder+"/" + String::nDigitsString(gfIteration.iteration,4) + ".png");
        }

        if(id.printEnergyValue){
          App::Utils::writeEnergyData(gfIteration,std::cout);
        }

        if(id.displayFlow) {
          cv::Mat bcImage;
          renderSegmentation(bcImage,ds,DD);
          cv::imshow(windowName, bcImage);
          cv::waitKey(10);
        }

        break;
      }
      case App::GraphSegIteration::End:{
        Display::saveDigitalSetAsImage(ds,id.outputFolder+"/mask-seg.png");

        if(id.displayFlow) {
          cv::Mat bcImage;
          renderSegmentation(bcImage,ds,DD);
          cv::imshow(windowName, bcImage);

          std::cout << "End of segmentation. Press any key to continue." << std::endl;
          cv::waitKey(0);
        }
      }
    }
  };

  Timer T_graphSeg;
  T_graphSeg.start();

  DigitalSet outputDS(imgDomain);
  switch(id.neighborhoodType){
    case App::InputData::Morphology:{
      GraphFlow::Core::Neighborhood::Morphology M(GraphFlow::Core::Neighborhood::Morphology::MorphologyElement::CIRCLE,id.neighborhoodSize);
      outputDS=App::graphSeg(gsi,M,ofsEnergy,iterationCallback);
      break;
    }
    case App::InputData::Random:{
      GraphFlow::Core::Neighborhood::Random R(id.neighborhoodSize);
      outputDS=App::graphSeg(gsi,R,ofsEnergy,iterationCallback);
      break;
    }
  }

  ofsEnergy << "#Execution time: ";
  T_graphSeg.end(ofsEnergy);
  ofsEnergy.flush(); ofsEnergy.close();

  App::Utils::outputImages(gsi.dataDistribution.gco,gsi.dataDistribution.segResultImg,outputDS,id.outputFolder);

  return 0;
}