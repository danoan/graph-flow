#include <random>

#include <DGtal/helpers/StdDefs.h>
#include <opencv2/core.hpp>
#include <DIPaCUS/base/Shapes.h>

#include "ShapeAndImage.h"
#include "bean.h"
#include "utils.h"

using namespace DGtal::Z2i;


int main(int argc, char* argv[]){
  std::string outputFilepath (argv[1]);
  int nBeans = std::atoi(argv[2]);
  double radius = std::atof(argv[3]);
  int damagePoints = std::atoi(argv[4]);
  double noiseRatio = std::atof(argv[5]);

  Domain domain( Point(0,0),Point(200,200));
  App::ShapeAndImage si = App::Bean::bean(domain,radius,noiseRatio,damagePoints,nBeans);

  cv::imwrite(outputFilepath,si.cvImg);
  return 0;
}