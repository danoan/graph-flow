#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/Neighborhood.h>
#include <DIPaCUS/derivates/Misc.h>

#include <opencv2/opencv.hpp>

namespace GraphFlow::Utils::Image {
void setHighlightMask(cv::Mat &outputImage, const cv::Mat &baseImage,
                      const cv::Mat &mask);
}