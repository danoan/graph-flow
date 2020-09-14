#ifndef GRAPH_FLOW_DATADISTRIBUTION_H
#define GRAPH_FLOW_DATADISTRIBUTION_H

#include <BTools/io/seed/GrabCutObject.h>

#include "input/InputData.h"
#include "model/GMM.h"
#include "model/CVMatDistribution.h"
#include "utils.h"


struct DataDistribution
{
    typedef BTools::IO::Seed::GrabCutObject GrabCutObject;

    void rerunGrabcut(const InputData& id)
    {
        GrabCutObject _gco = BTools::IO::Seed::read(id.gcoFilepath);

        cv::Mat fgMask,bgMask,pbfgMask;
        BTools::IO::Seed::getSeedMasks(_gco,fgMask,bgMask,pbfgMask);

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

        setSeeds(fgMask,bgMask);
    }

    void setSeeds(const cv::Mat& fgMask,const cv::Mat& bgMask){
      for(int r=0;r<fgMask.rows;++r){
        const unsigned char* Ri = fgMask.ptr<unsigned char>(r);
        for(int c=0;c<fgMask.cols;++c){
          if( Ri[c]==255 ) fgSeeds.insert( Point(c,fgMask.rows - r-1) );
        }
      }

      for(int r=0;r<bgMask.rows;++r){
        const unsigned char* Ri = bgMask.ptr<unsigned char>(r);
        for(int c=0;c<bgMask.cols;++c){
          if( Ri[c]==255 ) bgSeeds.insert( Point(c,bgMask.rows - r-1) );
        }
      }


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

    std::set<Point> fgSeeds;
    std::set<Point> bgSeeds;
};

#endif //GRAPH_FLOW_DATADISTRIBUTION_H
