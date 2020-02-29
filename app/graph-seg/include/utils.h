#ifndef GRAPH_FLOW_UTILS_H
#define GRAPH_FLOW_UTILS_H

#include <DGtal/helpers/StdDefs.h>
#include <BTools/utils/imgUtils.h>
#include <BTools/utils/model/GrabCutObject.h>

#include <graph-flow/utils/string.h>
#include <graph-flow/utils/energy.h>

#include "input/InputData.h"
#include "model/GraphSegIteration.h"
#include "model/GMM.h"

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;

typedef BTools::Utils::GrabCutIO::GrabCutObject GrabCutObject;

void writeEnergyData(const GraphSegIteration& gsIteration,std::ostream& os);
void writeEnergyData(std::ostream& os);
double evaluateEnergy(const InputData& id, const DigitalSet& ds);
DigitalSet getPixelMask(const std::string& pixelMaskFilepath, const Domain& domain, const Point& shift);

void initGMMs( const cv::Mat& img, const cv::Mat& mask, GMM& bgdGMM, GMM& fgdGMM );
cv::Mat highlightBorder(const DigitalSet& ds, const cv::Vec3b& color=cv::Vec3b(255,255,255));
void outputImages(const GrabCutObject& gco,const DigitalSet& outputDS,const std::string& outputFolder);
void outputImages(const GrabCutObject& gco,const cv::Mat& segResultImg,const DigitalSet& outputDS,const std::string& outputFolder);


#endif //GRAPH_FLOW_UTILS_H
