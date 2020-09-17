#include <random>

#include <DGtal/helpers/StdDefs.h>

#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/base/Shapes.h>

#include <BTools/io/seed/GrabCutObject.h>
#include <BTools/utils/imgUtils.h>

using Point = DGtal::Z2i::Point;
using Domain = DGtal::Z2i::Domain;
using DigitalSet = DGtal::Z2i::DigitalSet;

void injectRandomSeeds(int nCenters, int radius, DigitalSet& ds){
  Point ub = ds.domain().upperBound();

  std::random_device rd;
  std::default_random_engine re;
  std::uniform_int_distribution<int> distCols(2*radius,ub[0]-2*radius);
  std::uniform_int_distribution<int> distRows(2*radius,ub[1]-2*radius);

  while(nCenters>0){
    Point p( distCols(re),distRows(re) );
    ds += DIPaCUS::Shapes::ball(1.0,p[0],p[1],radius);
    nCenters--;
  }
}

int main(int argc, char* argv[])
{

  std::string gcoFilepath = argv[1];
  int nCenters = atoi(argv[2]);
  int radius = atoi(argv[3]);
  std::string outputFilepath = argv[4];
  std::string maskSegFilepath= argv[5];

  BTools::IO::Seed::GrabCutObject gco = BTools::IO::Seed::read(gcoFilepath);
  boost::filesystem::path p(outputFilepath);
  boost::filesystem::create_directories(p.remove_filename());

  cv::Mat segMask = cv::imread(maskSegFilepath,cv::IMREAD_GRAYSCALE);

  Point lb(0,0);
  Point ub( segMask.cols-1, segMask.rows-1);

  Domain domain(lb,ub);
  DigitalSet ds(domain);
  DIPaCUS::Representation::CVMatToDigitalSet(ds,segMask);


  injectRandomSeeds(nCenters,radius,ds);
  BTools::Utils::exportImageFromDigitalSet(ds,domain,outputFilepath);


  return 0;
}
