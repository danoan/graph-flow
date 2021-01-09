#include "graph-flow/utils/digital/types/Neighborhood.h"

namespace GraphFlow::Utils::Digital::Neighborhood {
EightNeighborhoodPredicate::EightNeighborhoodPredicate(const DigitalSet &DS)
    : myDigitalSet(DS) {
  lowerBound = DS.domain().lowerBound();
  upperBound = DS.domain().upperBound();
};

bool EightNeighborhoodPredicate::operator()(const Point &aPoint) const {
  Point np;
  int s = 0;
  int ceil = 5;

  s += myDigitalSet(aPoint);
  for (int i = 0; i < 4; ++i) {
    np = aPoint + filter[i];
    if (np[0] < lowerBound[0] || np[1] < lowerBound[1]) {
      ceil -= 1;
      continue;
    }

    if (np[0] > upperBound[0] || np[1] > upperBound[1]) {
      ceil -= 1;
      continue;
    }

    s += myDigitalSet(np) ? 1 : 0;
  }

  return !(s > 0 && s < ceil);
}

bool EightNeighborhoodPredicate::operator()(
    const Domain::ConstIterator &it) const {
  return (*this)(*it);
}

FourNeighborhoodPredicate::FourNeighborhoodPredicate(const DigitalSet &DS)
    : myDigitalSet(DS) {
  lowerBound = DS.domain().lowerBound();
  upperBound = DS.domain().upperBound();
}

bool FourNeighborhoodPredicate::operator()(const Point &aPoint) const {
  Point np;
  int s = 0;
  int ceil = 9;

  s += myDigitalSet(aPoint);
  for (int i = 0; i < 8; ++i) {
    np = aPoint + filter[i];
    if (np[0] < lowerBound[0] || np[1] < lowerBound[1]) {
      ceil -= 1;
      continue;
    }
    if (np[0] > upperBound[0] || np[1] > upperBound[1]) {
      ceil -= 1;
      continue;
    }

    s += myDigitalSet(np) ? 1 : 0;
  }

  return !(s > 0 && s < ceil);
}

bool FourNeighborhoodPredicate::operator()(
    const Domain::ConstIterator &it) const {
  return (*this)(*it);
}
}  // namespace GraphFlow::Utils::Digital::Neighborhood