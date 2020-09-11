#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>
#include <BTools/io/seed/GrabCutObject.h>

#include <graph-flow/utils/display.h>
#include <graph-flow/utils/string.h>

#include "input/InputData.h"
#include "input/InputReader.h"
#include "model/DataDistribution.h"
#include "model/GraphSegInput.h"
#include "model/GraphSegIteration.h"

#include "utils.h"
#include "graph-seg.h"

using namespace DGtal::Z2i;
using namespace GraphFlow::Core;
using namespace GraphFlow::Utils;



DigitalSet prepareShape(const DataDistribution& DD, int initialDilation)
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
  Domain dilatedDomain(imgDomain.lowerBound() - Point(initialDilation,initialDilation), imgDomain.upperBound() + Point(initialDilation,initialDilation));
  DigitalSet dilated(dilatedDomain);

  DIPaCUS::Morphology::dilate(dilated,tempDS,DIPaCUS::Morphology::StructuringElement(DIPaCUS::Morphology::StructuringElement::RECT,initialDilation));
  DigitalSet finalDS(imgDomain);
  for(auto p:dilated) if(imgDomain.isInside(p)) finalDS.insert(p);

  return finalDS;
}

int main(int argc, char* argv[])
{
  InputData id = readInput(argc,argv);
  boost::filesystem::create_directories(id.outputFolder);

  std::ofstream ofsInputData(id.outputFolder + "/inputData.txt");
  writeInputData(id,ofsInputData);
  ofsInputData.flush(); ofsInputData.close();

  std::ofstream ofsEnergy(id.outputFolder + "/energy.txt");
  ofsEnergy << "#Grabcut execution time: ";
  Timer T_grabcut;
  T_grabcut.start();
  DataDistribution DD(id);
  T_grabcut.end(ofsEnergy);


  Domain imgDomain(Point(0,0),
                   Point(DD.segResultImg.cols-1,
                         DD.segResultImg.rows-1));
  DigitalSet ds = prepareShape(DD,id.initialDilation);
  GraphSegInput gsi(id,ds,DD);

  std::string windowName="IterationViewer";
  if(id.displayFlow){
    cv::namedWindow(windowName);
  }


  IterationCallback iterationCallback=[&DD,&windowName,&id,&ofsEnergy](const GraphSegIteration& gfIteration)->void
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

      cv::Mat foregroundMask = cv::Mat::zeros(DD.segResultImg.size(),
                                              CV_8UC1);
      DIPaCUS::Representation::digitalSetToCVMat(foregroundMask,ds);

      cv::Mat bcImage;
      BTools::Utils::setHighlightMask(bcImage,DD.gco.inputImage,foregroundMask);
      cv::imshow(windowName,bcImage);
      cv::waitKey(10);
    }

  };

  Timer T_graphSeg;
  T_graphSeg.start();
  DigitalSet outputDS=graphSeg(gsi,ofsEnergy,iterationCallback);

  ofsEnergy << "#Execution time: ";
  T_graphSeg.end(ofsEnergy);
  ofsEnergy.flush(); ofsEnergy.close();

  outputImages(gsi.dataDistribution.gco,gsi.dataDistribution.segResultImg,outputDS,id.outputFolder);

  return 0;
}