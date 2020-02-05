#ifndef GRAPH_FLOW_INPUTREADER_H
#define GRAPH_FLOW_INPUTREADER_H

#include <unistd.h>
#include <iostream>
#include "InputData.h"

void usage(char* argv[]);
InputData readInput(int argc, char* argv[]);

#endif //GRAPH_FLOW_INPUTREADER_H
