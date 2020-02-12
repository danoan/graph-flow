#ifndef GRAPH_FLOW_DATADISTRIBUTION_H
#define GRAPH_FLOW_DATADISTRIBUTION_H

#include <BTools/utils/model/GrabCutObject.h>

#include "input/InputData.h"
#include "model/GMM.h"
#include "model/CVMatDistribution.h"
#include "utils.h"


struct DataDistribution
{
    typedef BTools::Utils::GrabCutIO::GrabCutObject GrabCutObject;

    DataDistribution(const InputData& id):inputData(id),fgGMM(fgModel),bgGMM(bgModel)
    {
        gco = BTools::Utils::GrabCutIO::read(id.gcoFilepath);

        segResultImg = cv::Mat::zeros(gco.inputImage.size(),gco.inputImage.type());
        gco.inputImage.copyTo(segResultImg,gco.segMask);

        initGMMs(gco.inputImage,gco.grabCutMask,bgGMM,fgGMM);

        fgDistr = new CVMatDistribution(gco.inputImage,fgGMM);
        bgDistr = new CVMatDistribution(gco.inputImage,bgGMM);
    }

    const InputData& inputData;
    GrabCutObject gco;
    cv::Mat segResultImg;

    cv::Mat fgModel,bgModel;
    GMM fgGMM,bgGMM;

    CVMatDistribution* fgDistr;
    CVMatDistribution* bgDistr;
};

#endif //GRAPH_FLOW_DATADISTRIBUTION_H
