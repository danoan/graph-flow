#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/core/neighborhood/RandomNeighborhood.h>
#include <graph-flow/contour-correction/graph-seg.h>
#include <graph-flow/contour-correction/model/GraphSegInput.h>
#include <graph-flow/contour-correction/model/GraphSegIteration.h>
#include <graph-flow/contour-correction/model/image/DataDistribution.h>
#include <graph-flow/utils/display.h>
#include <graph-flow/utils/image.h>
#include <graph-flow/utils/string.h>
#include <graph-flow/utils/timer.h>

#include <boost/filesystem.hpp>

#include "input/InputData.h"
#include "input/InputReader.h"

using namespace DGtal::Z2i;
using namespace GraphFlow;

DigitalSet prepareShape(const ContourCorrection::Image::DataDistribution& DD) {
  const cv::Mat& segResult = DD.segResultImg;

  Domain imgDomain(Point(0, 0), Point(segResult.cols - 1, segResult.rows - 1));
  DigitalSet tempDS(imgDomain);

  // Convert inputImg to 1-channel grayscale image.
  cv::Mat grayscale(segResult.size(), segResult.type());
  if (segResult.type() != CV_8UC1)
    cv::cvtColor(segResult, grayscale, cv::COLOR_RGB2GRAY, 1);
  else
    grayscale = segResult;

  DIPaCUS::Representation::CVMatToDigitalSet(tempDS, grayscale, 1);
  return tempDS;
}

void renderSegmentation(cv::Mat& bcImage, const DigitalSet& ds,
                        const ContourCorrection::Image::DataDistribution& DD) {
  cv::Mat foregroundMask = cv::Mat::zeros(DD.segResultImg.size(), CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(foregroundMask, ds);
  Utils::Image::setHighlightMask(bcImage, DD.gco.inputImage, foregroundMask);
}

void setGraphSegInput(const App::InputData& id,
                      ContourCorrection::GraphSegInput& gsi) {
  gsi.iterations = id.iterations;
  gsi.radius = id.radius;
  gsi.vradius = id.vradius;
  gsi.alpha = id.alpha;
  gsi.optBand = id.optBand;
  gsi.tolerance = id.tolerance;
  gsi.grabcutIterations = id.grabcutIterations;
  gsi.regionalTermWeight = id.regionalTermWeight;
  gsi.curvatureTermWeight = id.curvatureTermWeight;
  gsi.nThreads = id.nThreads;
  gsi.neighborhoodSize = id.neighborhoodSize;
}

int main(int argc, char* argv[]) {
  App::InputData id = App::readInput(argc, argv);
  boost::filesystem::create_directories(id.outputFolder);

  std::ofstream ofsInputData(id.outputFolder + "/inputData.txt");
  writeInputData(id, ofsInputData);
  ofsInputData.flush();
  ofsInputData.close();

  std::ofstream ofsEnergy(id.outputFolder + "/energy.txt");
  ofsEnergy << "#Grabcut execution time: ";
  Utils::Timer T_grabcut;
  T_grabcut.start();
  IO::Seed::GrabCutObject gco = IO::Seed::read(id.gcoFilepath);
  ContourCorrection::Image::DataDistribution DD(gco, id.grabcutIterations);
  T_grabcut.end(ofsEnergy);

  Domain imgDomain(Point(0, 0),
                   Point(DD.segResultImg.cols - 1, DD.segResultImg.rows - 1));
  DigitalSet ds = prepareShape(DD);

  ContourCorrection::GraphSegInput gsi(ds, DD);
  setGraphSegInput(id, gsi);

  std::string windowName = "IterationViewer";

  ContourCorrection::IterationCallback iterationCallback =
      [&DD, &windowName, &id, &ofsEnergy](
          const ContourCorrection::GraphSegIteration& gsIteration) -> void {
    const DigitalSet& ds = gsIteration.ds;
    App::Utils::writeEnergyData(gsIteration, ofsEnergy);

    switch (gsIteration.iterationState) {
      case ContourCorrection::GraphSegIteration::Init: {
        if (id.saveAllFigures) {
          Utils::Display::saveDigitalSetAsImage(
              ds, id.outputFolder + "/" +
                      Utils::String::nDigitsString(gsIteration.iteration, 4) +
                      ".png");
        }

        if (id.displayFlow) {
          cv::namedWindow(windowName);
        }
        break;
      }
      case ContourCorrection::GraphSegIteration::Running: {
        if (id.saveAllFigures) {
          Utils::Display::saveDigitalSetAsImage(
              ds, id.outputFolder + "/" +
                      Utils::String::nDigitsString(gsIteration.iteration, 4) + ".png");
        }

        if (id.printEnergyValue) {
          App::Utils::writeEnergyData(gsIteration, std::cout);
        }

        if (id.displayFlow) {
          cv::Mat bcImage;
          renderSegmentation(bcImage, ds, DD);
          cv::imshow(windowName, bcImage);
          cv::waitKey(10);
        }

        break;
      }
      case ContourCorrection::GraphSegIteration::End: {
        Utils::Display::saveDigitalSetAsImage(ds, id.outputFolder + "/mask-seg.png");

        if (id.displayFlow) {
          cv::Mat bcImage;
          renderSegmentation(bcImage, ds, DD);
          cv::imshow(windowName, bcImage);

          std::cout << "End of segmentation. Press any key to continue."
                    << std::endl;
          cv::waitKey(0);
        }
      }
    }
  };

  Utils::Timer T_graphSeg;
  T_graphSeg.start();

  DigitalSet outputDS(imgDomain);
  switch (id.neighborhoodType) {
    case App::InputData::Morphology: {
      Core::Neighborhood::Morphology M(
          Core::Neighborhood::Morphology::MorphologyElement::CIRCLE,
          id.neighborhoodSize);
      outputDS = ContourCorrection::graphSeg(gsi, M, ofsEnergy, iterationCallback);
      break;
    }
    case App::InputData::Random: {
      Core::Neighborhood::Random R(id.neighborhoodSize);
      outputDS = ContourCorrection::graphSeg(gsi, R, ofsEnergy, iterationCallback);
      break;
    }
  }

  ofsEnergy << "#Execution time: ";
  T_graphSeg.end(ofsEnergy);
  ofsEnergy.flush();
  ofsEnergy.close();

  App::Utils::outputImages(gsi.dataDistribution.gco,
                           gsi.dataDistribution.segResultImg, outputDS,
                           id.outputFolder);

  return 0;
}