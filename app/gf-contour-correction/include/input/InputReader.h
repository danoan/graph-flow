#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_INPUTREADER_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_INPUTREADER_H

#include <unistd.h>

#include <cstring>
#include <iostream>

#include "InputData.h"

namespace App {
void usage(char *argv[]);
InputData readInput(int argc, char *argv[]);

std::string resolveNeighborhoodType(InputData::NeighborhoodType nt);
std::string resolveValidationWeightMode(InputData::ValidationWeightMode vm);
void writeInputData(const InputData &id, std::ostream &os);
}  // namespace App

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_INPUTREADER_H
