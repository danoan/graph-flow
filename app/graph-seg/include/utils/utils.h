#ifndef GRAPH_FLOW_APP_GRAPH_SEG_UTILS_H
#define GRAPH_FLOW_APP_GRAPH_SEG_UTILS_H

#include <opencv2/imgproc/types_c.h>

#include <DGtal/helpers/StdDefs.h>

#include <graph-flow/io/seed/GrabCutObject.h>
#include <graph-flow/utils/string.h>
#include <graph-flow/utils/energy.h>
#include <graph-flow/utils/image.h>

#include "input/InputData.h"
#include "model/GraphSegIteration.h"

namespace App::Utils {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;

typedef GraphFlow::IO::Seed::GrabCutObject GrabCutObject;

void writeEnergyData(const GraphSegIteration &gsIteration, std::ostream &os);
double evaluateEnergy(const InputData &id, const DigitalSet &ds);
void outputImages(const cv::Mat cvImgIn,
             const DigitalSet &outputDS,
             const std::string &outputFolder);
}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_UTILS_H
