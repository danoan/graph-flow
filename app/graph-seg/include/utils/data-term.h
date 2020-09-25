#ifndef GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_UTILS_DATA_TERM_H_
#define GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_UTILS_DATA_TERM_H_

#include <DGtal/helpers/StdDefs.h>
#include <opencv2/core.hpp>
#include <DIPaCUS/derivates/Misc.h>

#include "input/InputData.h"
namespace App::Utils::DataTerm{
typedef DGtal::Z2i::DigitalSet DigitalSet;

double chanvese(const InputData& id,const DigitalSet& ds, const cv::Mat& cvImgIn);
double chanvese_region_term(const DigitalSet& dsMask,const cv::Mat& cvImg,const cv::Vec3d& avgColor);
cv::Vec3d avgColor(const DigitalSet& dsMask, const cv::Mat& cvImg);

}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_UTILS_DATA_TERM_H_
