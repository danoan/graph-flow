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



        cv::Mat fgMask=cv::Mat::zeros(gco.grabCutMask.size(),gco.grabCutMask.type());
        cv::compare(gco.grabCutMask,
                    cv::GC_FGD,
                    fgMask,
                    cv::CMP_EQ);
        cv::Mat gcOutMask=gco.grabCutMask;


        grabCut(gco.inputImage,gcOutMask,cv::Rect(),bgModel,fgModel,10,cv::GC_INIT_WITH_MASK);

        cv::Mat segMask= cv::Mat::zeros(gco.inputImage.size(),CV_8UC1);
        cv::compare(gcOutMask,
                    cv::GC_PR_FGD,
                    segMask,
                    cv::CMP_EQ);

        segMask.setTo(255,fgMask);
        gco.inputImage.copyTo(segResultImg,segMask);

        fgGMM=GMM(fgModel);
        bgGMM=GMM(bgModel);

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
