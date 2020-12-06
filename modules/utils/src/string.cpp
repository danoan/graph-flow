#include "graph-flow/utils/string.h"

namespace GraphFlow::Utils::String {
std::string fixedStrLength(int l, double v,int ndigits) {

  std::stringstream ss;

  ss << std::setprecision(ndigits) << std::fixed << v;

  std::string sOut = ss.str();
  while (sOut.length() < l) sOut += " ";

  return sOut;
}

std::string fixedStrLength(int l, std::string str) {
  std::string out = str;
  while (out.length() < l) out += " ";

  return out;
}

std::string nDigitsString(int num, int digits) {
  std::string s = "";
  int numSize = num == 0 ? 1 : log10(abs(num)) + 1;
  int lZero = digits - numSize;
  while (lZero > 0) {
    s += std::to_string(0);
    --lZero;
  }
  s += std::to_string(num);
  return s;
}
}  // namespace GraphFlow::Utils::String