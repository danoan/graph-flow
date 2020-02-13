#include "model/StandardModel.h"

namespace StandardModel
{
    double evaluateData(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        const cv::Mat& img = DD.fgDistr->img;
        double value=0;
        for(auto p:ds.domain())
        {
            if( ds(p) )
                value+=-log( (*DD.fgDistr)( img.rows-p[1],p[0]) );
            else
                value+=-log( (*DD.bgDistr)( img.rows-p[1],p[0]) );
        }


        return id.dataTermWeight*value;
    }

    HardConstraintVector prepareHardConstraints(const InputData& id, const DigitalSet& ds, const DigitalSet& pixelMask)
    {
        HardConstraintVector hcv(1);
        hcv[0] = new FixedPixels(id.radius,ds,pixelMask);

        return hcv;
    }

    TerminalWeightVector prepareTerminalWeights(const InputData& id, const DTL2& dtInterior, const DTL2& dtExterior,const DataDistribution& DD, double dataTermWeight)
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
        EdgeWeightVector ewv(1);
        ewv[0] = new Curvature(id.radius,id.h,ds);
//        ewv[1] = new Homogeneity(colorImage);

        return ewv;
    }

}