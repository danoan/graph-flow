#ifndef GRAPH_FLOW_SEED_SELECTOR_INPUTDATA_H
#define GRAPH_FLOW_SEED_SELECTOR_INPUTDATA_H

#include <unistd.h>

#include <iostream>
#include <string>

namespace SeedSelector {
struct InputData {
  InputData() : once(false) {}

  std::string outputFolder;
  std::string imagePath;

  std::string unknownImageMask;
  std::string fgImageMask;
  std::string bgImageMask;
  std::string segImageMask;

  std::string testModeString;
  bool testModeFlag{false};

  bool once;
};

void usage(char* argv[]);
InputData readInput(int argc, char* argv[]);
}  // namespace SeedSelector

#endif  // GRAPH_FLOW_SEED_SELECTOR_INPUTDATA_H
