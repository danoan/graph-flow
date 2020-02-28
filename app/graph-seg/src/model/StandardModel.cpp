#include "model/StandardModel.h"

namespace StandardModel
{
    double boundaryValue(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        const cv::Mat& img = DD.fgDistr->img;

        DigitalSet boundary(ds.domain());
        DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(boundary,ds);

        cv::Mat blurred(DD.segResultImg.rows,DD.segResultImg.cols,DD.segResultImg.type());
        cv::blur(DD.segResultImg,blurred,cv::Size(5,5));

        double M=pow(255,2);
        double v=0;
        for(auto p:boundary)
        {
            int prow = img.rows - p[1];
            int pcol = p[0];

            cv::Vec3d diff = img.at<cv::Vec3b>(prow,pcol)-blurred.at<cv::Vec3b>(prow,pcol);
            for(int i=0;i<3;++i) diff[i]=std::fabs(diff[i]);
            diff/=M;
            v+=exp( pow(1-diff[0],2)+pow(1-diff[1],2)+pow(1-diff[2],2) );
        }

        v=v/( (double) boundary.size() );

        return v;
    }

    double regionValue(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        const cv::Mat& img = DD.fgDistr->img;
        double v=0;
        for(auto p:ds.domain())
        {
            int prow=img.rows-p[1];
            int pcol=p[0];

            if(ds(p))
            {
                v+=-log( 1- (*DD.bgDistr)(prow,pcol) );
            }else
            {
                v+=-log( 1-(*DD.fgDistr)(prow,pcol) );
            }
        }

        return v;
    }

    double evaluateData(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        double bv = boundaryValue(id,ds,DD);
        double rv = regionValue(id,ds,DD);

        return id.dataTermWeight*(bv+rv);

    }

    HardConstraintVector prepareHardConstraints(const InputData& id, const DigitalSet& ds, const DigitalSet& pixelMask)
    {
        HardConstraintVector hcv(1);
        hcv[0] = new FixedPixels(id.radius,ds,pixelMask);

        return hcv;
    }

    TerminalWeightVector prepareTerminalWeights(const InputData& id, const DTL2& dtInterior, const DTL2& dtExterior,const DataDistribution& DD, double dataTermWeight, const DigitalSet& ds)
    {
        TerminalWeightVector twv(4);
        twv[0] = new ForegroundHard(dtInterior,id.optBand,id.radius);
        twv[1] = new BackgroundHard(dtExterior,id.optBand,id.radius);

        twv[2] = new Foreground(*DD.fgDistr,dataTermWeight);
        twv[3] = new Background(*DD.bgDistr,dataTermWeight);

        return twv;
    }

    EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds, const cv::Mat& colorImage)
    {
        EdgeWeightVector ewv(2);
        ewv[0] = new Curvature(id.radius,id.h,ds);
//        ewv[0] = new Homogeneity(colorImage);
        ewv[1] = new Blur(ds,colorImage);

        return ewv;
    }

}