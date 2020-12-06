#ifndef GRAPH_FLOW_GRABCUT_INPUTDATA_H
#define GRAPH_FLOW_GRABCUT_INPUTDATA_H

#include <unistd.h>

#include <iostream>

namespace GrabCut {
struct InputData {
  InputData() : showSeg(false), iterations(1) {}

  std::string imgPath;
  std::string outputObject;
  std::string outputSegImage;

  std::string unknownMask;
  std::string fgSeedMask;
  std::string bgSeedMask;
  std::string lastSegmentationMask;

  int iterations;

  bool showSeg;
};

void usage(char* argv[]);
InputData readInput(int argc, char* argv[]);

}  // namespace GrabCut

#endif  // BGRAPH_FLOW_GRABCUT_INPUTDATA_H
