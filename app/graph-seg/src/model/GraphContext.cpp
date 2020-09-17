#include "model/graph/GraphModel.h"

namespace GraphModel
{
    double regionValue(double& fgv, double& bgv,const DigitalSet& ds, const CVMatDistribution& fgDistr, const CVMatDistribution& bgDistr)
    {
        const cv::Mat& img = fgDistr.img;
        bgv=0;
        fgv=0;
        for(auto p:ds.domain())
        {
            int prow=img.rows-p[1];
            int pcol=p[0];

            if(ds(p))
            {
                fgv+=-log( (fgDistr)(prow,pcol) );
            }else
            {
                bgv+=-log( (bgDistr)(prow,pcol) );
            }
        }

        return (fgv+bgv);
    }

    double evaluateData(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
      double fgv,bgv;
      double rv = id.regionalTermWeight*regionValue(fgv,bgv,ds,*DD.fgDistr,*DD.bgDistr);
      return rv;
    }

    HardConstraintVector prepareHardConstraints(const InputData& id, const DigitalSet& ds, const DigitalSet& pixelMask)
    {
        HardConstraintVector hcv(1);
        hcv[0] = new FixedPixels(id.radius,ds,pixelMask);

        return hcv;
    }

    TerminalWeightVector prepareTerminalWeights(const InputData& id, const DTL2& dtInterior, const DTL2& dtExterior,const DataDistribution& DD, const DigitalSet& ds)
    {
        TerminalWeightVector twv(4);
        twv[0] = new ForegroundHard(dtInterior,id.optBand,id.radius);
        twv[1] = new BackgroundHard(dtExterior,id.optBand,id.radius);

        twv[2] = new Foreground(*DD.fgDistr,id.regionalTermWeight);
        twv[3] = new Background(*DD.bgDistr,id.regionalTermWeight);

        return twv;
    }

    EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds, const cv::Mat& colorImage)
    {
        EdgeWeightVector ewv(2);
        ewv[0] = new Curvature(id.radius,id.h,ds,id.curvatureTermWeight);
        ewv[1] = new Homogeneity(colorImage,1.0);

        return ewv;
    }

}