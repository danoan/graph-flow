#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>
#include <BTools/io/seed/GrabCutObject.h>

#include <graph-flow/utils/display.h>
#include <graph-flow/utils/string.h>
#include <graph-flow/utils/ring.h>

#include "input/InputData.h"
#include "input/InputReader.h"
#include "model/image/DataDistribution.h"
#include "model/GraphSegInput.h"
#include "model/GraphSegIteration.h"

#include "utils/utils.h"
#include "graph-seg.h"

using namespace DGtal::Z2i;
using namespace GraphFlow::Core;
using namespace GraphFlow::Utils;

DGtal::Z2i::DigitalSet diskMask(const DGtal::Z2i::Domain& domain,double radius,int border){
  using namespace DGtal::Z2i;

  DigitalSet ds(domain);
  ds.clear();

  Point lb,ub;
  lb = domain.lowerBound();
  ub = domain.upperBound();

  int minX = lb[0]+radius;
  int minY = lb[1]+radius;

  int maxX = ub[0]-radius;
  int maxY = ub[1]-radius;

  for(int x=minX;x<maxX;x+=border){
    for(int y=minY;y<maxY;y+=border){
      DigitalSet ballDS = DIPaCUS::Shapes::ball(1.0,x,y,radius);
      ds += ballDS;
    }
  }

  return ds;

}

void setRingMask(App::InputData& id){
  auto _gco = BTools::IO::Seed::read(id.gcoFilepath);

  Point ub(_gco.inputImage.cols-1,_gco.inputImage.rows-1);
  Point lb(0,0);
  Domain domain(lb,ub);

//  DigitalSet mask = Shapes::ringMask(domain,10,20,50);
  DigitalSet mask = diskMask(domain,8,20);
  Display::saveDigitalSetAsImage(mask,"temp.pgm");

  id.randomSeedsFilepath = "temp.pgm";
}

void convertImagesToDoubleRepr(App::Image::DataDistribution& DD){
  cv::Mat o1(DD.gco.inputImage.size(),CV_64FC1);
  DD.gco.inputImage.convertTo(o1,CV_64FC1);
  DD.gco.inputImage = o1;
}

DigitalSet prepareShape(const App::Image::DataDistribution& DD)
{
  const cv::Mat& segMask = DD.gco.segMask;


  Domain imgDomain(Point(0,0),
                   Point(segMask.cols-1,
                         segMask.rows-1)
  );
  DigitalSet tempDS(imgDomain);

  //Convert inputImg to 1-channel grayscale image.
  cv::Mat grayscale(segMask.size(),
                    segMask.type());
  if(segMask.type()!=CV_8UC1)
    cv::cvtColor(segMask,grayscale,cv::COLOR_RGB2GRAY,1);
  else
    grayscale = segMask;

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
  setRingMask(id);
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
        if(id.displayFlow){
          cv::namedWindow(windowName);
          cv::Mat bcImage;
          renderSegmentation(bcImage,ds,DD);
          cv::imshow(windowName, bcImage);
          cv::waitKey(10);
        }
        break;
      }
      case App::GraphSegIteration::Running:{
        if(id.saveAllFigures){
          Display::saveDigitalSetAsImage(ds,id.outputFolder+"/" + String::nDigitsString(gfIteration.iteration,4) + ".pgm");
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
        Display::saveDigitalSetAsImage(ds,id.outputFolder+"/mask-seg.pgm");

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
  DigitalSet outputDS=App::graphSeg(gsi,ofsEnergy,iterationCallback);

  ofsEnergy << "#Execution time: ";
  T_graphSeg.end(ofsEnergy);
  ofsEnergy.flush(); ofsEnergy.close();

  App::Utils::outputImages(gsi.dataDistribution.gco,gsi.dataDistribution.segResultImg,outputDS,id.outputFolder);

  return 0;
}