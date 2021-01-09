#ifndef GRAPH_FLOW_UTILS_DISPLAY_H
#define GRAPH_FLOW_UTILS_DISPLAY_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/writers/GenericWriter.h>
#include <graph-flow/utils/digital/representation.h>

namespace GraphFlow::Utils::Display {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;
typedef std::set<Point> PointSet;

void saveDigitalSetAsImage(const Domain& domain, const PointSet& ps,
                           const std::string& outputFilepath);
void saveDigitalSetAsImage(const DGtal::Z2i::DigitalSet& ds,
                           const std::string& outputFilepath);
}  // namespace GraphFlow::Utils::Display

#endif  // GRAPH_FLOW_UTILS_DISPLAY_H
