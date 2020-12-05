#ifndef GRAPH_FLOW_SUMMARY_FLOW_SUMMARY_FLOW_INPUTREADER_H
#define GRAPH_FLOW_SUMMARY_FLOW_SUMMARY_FLOW_INPUTREADER_H

#include <unistd.h>

#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <string>

#include "InputData.h"

namespace SummaryFlow {
namespace InputReader {
void usage(int argc, char* argv[]);
InputData readInput(int argc, char* argv[]);
}  // namespace InputReader
}  // namespace SummaryFlow

#endif  // EXHAUSTIVE_GC_INPUTREADER_H
