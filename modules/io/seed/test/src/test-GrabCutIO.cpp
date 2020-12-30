#include <graph-flow/io/seed/GrabCutObject.h>

#include <iostream>

#include "catch.hpp"

using namespace GraphFlow::IO::Seed;

// void write(const GrabCutObject& gco, const std::string& outputPath);

TEST_CASE("read GrabCutObject", "[GrabCutIO]") {
  std::string inputGCFile = MY_MAIN_DIR;
  inputGCFile += "/modules/io/seed/test/input/coala.xml";

  GrabCutObject gco = read(inputGCFile);

  REQUIRE(gco.grabCutMask.rows == 481);
  REQUIRE(gco.grabCutMask.cols == 321);

  REQUIRE(gco.segMask.rows == 481);
  REQUIRE(gco.segMask.cols == 321);

  REQUIRE(gco.inputImage.rows == 481);
  REQUIRE(gco.inputImage.cols == 321);

  REQUIRE(gco.seeds.rows == 481);
  REQUIRE(gco.seeds.cols == 321);
}

TEST_CASE("write GrabCutObject", "[GrabCutIO]") {
  std::string inputGCFile = MY_MAIN_DIR;
  inputGCFile += "/modules/io/seed/test/input/coala.xml";

  GrabCutObject gco = read(inputGCFile);

  std::string outputFolder = MY_MAIN_DIR;
  outputFolder += "/temp_io";

  boost::filesystem::create_directories(outputFolder);
  std::string outputFilepath = outputFolder + "/gco-write-test.xml";
  write(gco,outputFilepath);

  REQUIRE(boost::filesystem::exists(outputFilepath));
  GrabCutObject gco2 = read(inputGCFile);  

  REQUIRE(gco2.grabCutMask.rows == 481);
  REQUIRE(gco2.grabCutMask.cols == 321);  

  boost::filesystem::remove_all(outputFolder);  
}