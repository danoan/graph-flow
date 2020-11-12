#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/writers/GenericWriter.h>

#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/Neighborhood.h>
#include <DIPaCUS/derivates/Misc.h>

#include <opencv2/opencv.hpp>

namespace GraphFlow::Utils::Image {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;
typedef DIPaCUS::Representation::Image2D Image2D;
void setHighlightMask(cv::Mat& outputImage, const cv::Mat& baseImage,
                      const cv::Mat& mask);

void exportImageFromDigitalSet(const DigitalSet& ds,
                               const std::string& outputFilepath);

void exportImageFromDigitalSet(const DigitalSet& ds, const Domain& domain,
                               const std::string& outputFilepath);
}  // namespace GraphFlow::Utils::Image