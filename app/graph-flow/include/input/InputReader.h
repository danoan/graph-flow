#ifndef GRAPH_FLOW_APP_GRAPH_FLOW_INPUTREADER_H
#define GRAPH_FLOW_APP_GRAPH_FLOW_INPUTREADER_H

#include <cstring>
#include <unistd.h>
#include <iostream>
#include "InputData.h"

namespace App{
void usage(char* argv[]);
InputData readInput(int argc, char* argv[]);

std::string resolveNeighborhoodType(InputData::NeighborhoodType nt);
void writeInputData(const InputData &id, size_t nPixels, std::ostream &os);
}


#endif //GRAPH_FLOW_APP_GRAPH_FLOW_INPUTREADER_H
