#ifndef GRAPH_FLOW_APP_GENERATE_TEST_IMAGES_UTILS_H_
#define GRAPH_FLOW_APP_GENERATE_TEST_IMAGES_UTILS_H_

#include <random>

#include <DGtal/helpers/StdDefs.h>
#include <opencv2/core.hpp>
#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/derivates/Misc.h>


#include "ShapeAndImage.h"

namespace App::Utils{
using DigitalSet=DGtal::Z2i::DigitalSet;
using Point=DGtal::Z2i::Point;
using NoiseFunction=void(*)(cv::Mat&, const cv::Mat&, double);

void rotate(cv::Mat& cvOut, const cv::Mat& cvIn, Point center);
DigitalSet rotate(const DigitalSet& dsIn);

ShapeAndImage addNoise(const DigitalSet& dsIn, NoiseFunction nf, double noiseRatio);
void randomNoise(cv::Mat& cvOut, const cv::Mat& cvIn, double ratio);

DigitalSet disturbContour(const DigitalSet& dsIn, int damagePoints);
}


#endif //GRAPH_FLOW_APP_GENERATE_TEST_IMAGES_UTILS_H_
