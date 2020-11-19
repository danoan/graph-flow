#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_UTILS_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_UTILS_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/image-segmentation/model/GraphSegIteration.h>
#include <graph-flow/image-segmentation/model/image/GMM.h>
#include <graph-flow/io/seed/GrabCutObject.h>
#include <graph-flow/utils/image.h>
#include <graph-flow/utils/string.h>
#include <opencv2/imgproc/types_c.h>

namespace App::Utils {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;

typedef GraphFlow::IO::Seed::GrabCutObject GrabCutObject;
typedef GraphFlow::ImageSegmentation::GraphSegIteration GraphSegIteration;

void writeEnergyData(const GraphSegIteration &gsIteration, std::ostream &os);
void outputImages(const GrabCutObject &gco, const cv::Mat &segResultImg,
                  const DigitalSet &outputDS, const std::string &outputFolder);
}  // namespace App::Utils

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_UTILS_H
