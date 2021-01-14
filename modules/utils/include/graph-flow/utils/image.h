#ifndef GRAPH_FLOW_UTILS_IMAGE_H
#define GRAPH_FLOW_UTILS_IMAGE_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/utils/digital/representation.h>
#include <graph-flow/utils/digital/contour.h>

#include <opencv2/opencv.hpp>

namespace GraphFlow::Utils::Image {
void setHighlightMask(cv::Mat &outputImage, const cv::Mat &baseImage,
                      const cv::Mat &mask,
                      cv::Vec3b color = cv::Vec3b(150, 250, 250));
}
#endif