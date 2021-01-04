#include <DIPaCUS/base/Shapes.h>
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
    DigitalSet ball = DIPaCUS::Shapes::ball(h, 0, 0, radius);
    saveDigitalSetAsImage(ball,imageOutputPath);
  }catch(std::exception ex){
    std::cerr << ex.what() << std::endl;
  }

  REQUIRE(boost::filesystem::exists(imageOutputPath));
  boost::filesystem::remove_all(tempOutputFolder);
}