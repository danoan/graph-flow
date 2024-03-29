#ifndef GRAPH_FLOW_APP_INPUTREADER_H
#define GRAPH_FLOW_APP_INPUTREADER_H

#include <unistd.h>

#include <cstring>
#include <iostream>

#include "InputData.h"

namespace App {
void usage(char* argv[]);
InputData readInput(int argc, char* argv[]);

std::string resolveNeighborhoodType(InputData::NeighborhoodType nt);
void writeInputData(const InputData& id, size_t nPixels, std::ostream& os);
}  // namespace App

#endif  // GRAPH_FLOW_APP_INPUTREADER_H
