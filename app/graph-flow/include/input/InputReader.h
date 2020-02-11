#ifndef GRAPH_FLOW_INPUTREADER_H
#define GRAPH_FLOW_INPUTREADER_H

#include <unistd.h>
#include <iostream>
#include "InputData.h"

void usage(char* argv[]);
InputData readInput(int argc, char* argv[]);

std::string resolveEnergyName(InputData::EnergyType et);
void writeInputData(const InputData& id, std::ostream& os);

#endif //GRAPH_FLOW_INPUTREADER_H
