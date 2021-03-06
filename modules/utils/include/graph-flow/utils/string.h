#ifndef GRAPH_FLOW_UTILS_STRING_H
#define GRAPH_FLOW_UTILS_STRING_H

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

namespace GraphFlow::Utils::String {
std::string fixedStrLength(int l, double v, int ndigits = 4);

std::string fixedStrLength(int l, std::string str);

std::string nDigitsString(int num, int digits);
}  // namespace GraphFlow::Utils::String

#endif  // GRAPH_FLOW_UTILS_STRING_H
