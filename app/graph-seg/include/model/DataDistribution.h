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

    void rerunGrabcut(const InputData& id)
    {
        GrabCutObject _gco = BTools::Utils::GrabCutIO::read(id.gcoFilepath);

        cv::Mat fgMask,bgMask,pbfgMask;
        BTools::Utils::GrabCutIO::getSeedMasks(_gco,fgMask,bgMask,pbfgMask);

        gco.inputImage = _gco.inputImage;
        gco.seeds = _gco.seeds;

        gco.grabCutMask = cv::Mat::zeros(_gco.inputImage.size(),CV_8UC1);
        if(pbfgMask.size>0)
        {
            cv::Mat sureBGMask = cv::Mat::zeros(gco.inputImage.size(),CV_8UC1);
            cv::bitwise_not(pbfgMask,sureBGMask);

            gco.grabCutMask.setTo(cv::GrabCutClasses::GC_BGD,sureBGMask);
            gco.grabCutMask.setTo(cv::GrabCutClasses::GC_PR_BGD,pbfgMask);
        }else
        {
            gco.grabCutMask = cv::GrabCutClasses::GC_PR_BGD;
        }

        gco.grabCutMask.setTo(cv::GrabCutClasses::GC_BGD,bgMask);
        gco.grabCutMask.setTo(cv::GrabCutClasses::GC_FGD,fgMask);


        cv::Mat bgModel;
        cv::Mat fgModel;

        cv::grabCut(gco.inputImage,
                    gco.grabCutMask,
                    cv::Rect(),
                    bgModel,
                    fgModel,
                    id.grabcutIterations,
                    cv::GC_INIT_WITH_MASK);

        fgGMM=GMM(fgModel);
        bgGMM=GMM(bgModel);

        gco.segMask = cv::Mat::zeros(gco.inputImage.size(),CV_8UC1);

        cv::compare(gco.grabCutMask,
                    cv::GC_PR_FGD,
                    gco.segMask,
                    cv::CMP_EQ);

        gco.segMask.setTo(255,fgMask);
        gco.inputImage.copyTo(segResultImg,gco.segMask);
    }

    DataDistribution(const InputData& id):inputData(id),fgGMM(fgModel),bgGMM(bgModel)
    {
        rerunGrabcut(id);

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
