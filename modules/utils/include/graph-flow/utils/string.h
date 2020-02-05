#ifndef GRAPH_FLOW_UTILS_STRING_H
#define GRAPH_FLOW_UTILS_STRING_H

#include <string>
#include <cmath>

namespace GraphFlow::Utils::String
{
    std::string fixedStrLength(int l,double v);

    std::string fixedStrLength(int l,std::string str);

    std::string nDigitsString(int num, int digits);
}

#endif //GRAPH_FLOW_UTILS_STRING_H
