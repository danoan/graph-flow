#ifndef GRAPH_FLOW_UTILS_H
#define GRAPH_FLOW_UTILS_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/utils/string.h>
#include <graph-flow/utils/energy.h>

#include "input/InputData.h"
#include "model/GraphSegIteration.h"
#include "model/GMM.h"

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;

void writeEnergyData(const GraphSegIteration& gsIteration,std::ostream& os);
void writeEnergyData(std::ostream& os);
double evaluateEnergy(const InputData& id, const DigitalSet& ds);
DigitalSet getPixelMask(const std::string& pixelMaskFilepath, const Domain& domain, const Point& shift);
void initGMMs( const cv::Mat& img, const cv::Mat& mask, GMM& bgdGMM, GMM& fgdGMM );


#endif //GRAPH_FLOW_UTILS_H
