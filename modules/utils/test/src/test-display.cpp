#include <graph-flow/utils/digital/shapes.h>
#include <graph-flow/utils/display.h>

#include <boost/filesystem.hpp>

#include "catch.hpp"

using namespace GraphFlow::Utils::Display;

TEST_CASE("save digital set as image", "[display]") {
  using namespace DGtal::Z2i;

  double h = 1.0;
  double radius = 10;

  std::string tempOutputFolder = MY_MAIN_DIR;
  tempOutputFolder += "/temp_diplay";
  std::string imageOutputPath = tempOutputFolder + "/ball.png";

  boost::filesystem::create_directories(tempOutputFolder);

  try {
    DigitalSet ball = GraphFlow::Utils::Digital::Shapes::ball(h, 0, 0, radius);
    saveDigitalSetAsImage(ball,imageOutputPath);
  }catch(std::exception ex){
    std::cerr << ex.what() << std::endl;
  }

  REQUIRE(boost::filesystem::exists(imageOutputPath));
  boost::filesystem::remove_all(tempOutputFolder);
}

TEST_CASE("save set of points with domain as an image", "[display]") {
  using namespace DGtal::Z2i;

  std::string tempOutputFolder = MY_MAIN_DIR;
  tempOutputFolder += "/temp_diplay";
  std::string imageOutputPath = tempOutputFolder + "/point-set.png";

  boost::filesystem::create_directories(tempOutputFolder);

  try {
    std::set<Point> ps;
    ps.insert(Point(5,5));
    Domain domain(Point(0,0),Point(10,10));

    saveDigitalSetAsImage(domain,ps,imageOutputPath);
  }catch(std::exception ex){
    std::cerr << ex.what() << std::endl;
  }

  REQUIRE(boost::filesystem::exists(imageOutputPath));
  boost::filesystem::remove_all(tempOutputFolder);
}