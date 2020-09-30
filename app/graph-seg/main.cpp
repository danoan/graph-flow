#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>

#include <graph-flow/utils/display.h>
#include <graph-flow/utils/string.h>
#include <graph-flow/utils/ring.h>

#include "input/InputData.h"
#include "input/InputReader.h"
#include "model/GraphSegInput.h"
#include "model/GraphSegIteration.h"

#include "utils/utils.h"
#include "graph-seg.h"

using namespace DGtal::Z2i;
using namespace GraphFlow::Core;
using namespace GraphFlow::Utils;

DGtal::Z2i::DigitalSet diskMask(const DGtal::Z2i::Domain& domain, double radius,int padding,Point border=Point(100,100)){
  using namespace DGtal::Z2i;

  DigitalSet ds(domain);
  ds.clear();

  Point lb,ub;
  lb = domain.lowerBound();
  ub = domain.upperBound();

  int minX = border[0] + lb[0] + radius;
  int minY = border[0] + lb[1] + radius;

  int maxX = ub[0]-border[1] - radius;
  int maxY = ub[1]-border[1] - radius;

  for(int x=minX;x<maxX;x+=padding){
    for(int y=minY;y<maxY;y+=padding){
      DigitalSet ballDS = DIPaCUS::Shapes::ball(1.0,x,y,radius);
      ds += ballDS;
    }
  }

  return ds;

}


DigitalSet prepareShape(const cv::Mat& cvImg)
{
  Point ub(cvImg.cols-1,cvImg.rows-1);
  Point lb(0,0);

  Domain domain(lb,ub);
  DigitalSet mask = diskMask(domain,8,20);

  return mask;
}

void renderSegmentation(cv::Mat& cvImgOut, const cv::Mat& cvImgIn,const DigitalSet& ds){
  cv::Mat foregroundMask = cv::Mat::zeros(cvImgIn.size(),
                                          CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(foregroundMask, ds);
  BTools::Utils::setHighlightMask(cvImgOut, cvImgIn, foregroundMask);
}

int main(int argc, char* argv[])
{
  App::InputData id = App::readInput(argc,argv);
  boost::filesystem::create_directories(id.outputFolder);

  std::ofstream ofsInputData(id.outputFolder + "/inputData.txt");
  writeInputData(id,ofsInputData);
  ofsInputData.flush(); ofsInputData.close();

  std::ofstream ofsEnergy(id.outputFolder + "/energy.txt");

  cv::Mat cvImg = cv::imread(id.inputImageFilepath,cv::IMREAD_COLOR);
  Domain imgDomain(Point(0,0),
                   Point(cvImg.cols-1,
                         cvImg.rows-1));

  DigitalSet ds = prepareShape(cvImg);
  App::GraphSegInput gsi(id,ds,cvImg);

  std::string windowName="IterationViewer";

  App::IterationCallback iterationCallback=[&cvImg,&windowName,&id,&ofsEnergy](const App::GraphSegIteration& gfIteration)->void
  {
    const DigitalSet& ds = gfIteration.ds;
    App::Utils::writeEnergyData(gfIteration,ofsEnergy);

    switch(gfIteration.iterationState){
      case App::GraphSegIteration::Init:{
        if(id.displayFlow){
          cv::namedWindow(windowName);
          cv::Mat bcImage;
          renderSegmentation(bcImage,cvImg,ds);
          cv::imshow(windowName, bcImage);
          cv::waitKey(10);
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
          renderSegmentation(bcImage,cvImg,ds);
          cv::imshow(windowName, bcImage);
          cv::waitKey(10);
        }

        break;
      }
      case App::GraphSegIteration::End:{
        Display::saveDigitalSetAsImage(ds,id.outputFolder+"/mask-seg.png");

        if(id.displayFlow) {
          cv::Mat bcImage;
          renderSegmentation(bcImage,cvImg,ds);
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

  App::Utils::outputImages(cvImg,outputDS,id.outputFolder);

  return 0;
}