#ifndef GRAPH_FLOW_APP_GENERATE_TEST_IMAGES_BEAN_H_
#define GRAPH_FLOW_APP_GENERATE_TEST_IMAGES_BEAN_H_

#include <DGtal/helpers/StdDefs.h>

#include "ShapeAndImage.h"
#include "utils.h"

namespace App::Bean{
using DigitalSet=DGtal::Z2i::DigitalSet;
using Domain=DGtal::Z2i::Domain;

DigitalSet generate(const Domain& domain,double radius, int damagePoints, int nBeans);
ShapeAndImage bean(const Domain& domain,double radius,double noiseRatio,int damagePoints,int nBeans);
}

#endif //GRAPH_FLOW_APP_GENERATE_TEST_IMAGES_BEAN_H_
