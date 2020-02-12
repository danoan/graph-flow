#include "model/StandardModel.h"

namespace StandardModel
{
    double evaluateData(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        double value=0;
        for(auto p:ds.domain())
        {
            if( ds(p) )
                value+=-log( (*DD.fgDistr)( DD.fgDistr->img.rows-p[1],p[0]) );
            else
                value+=-log( (*DD.bgDistr)( DD.bgDistr->img.rows-p[1],p[0]) );
        }
        return id.dataTermWeight*value/( (double) ds.domain().size() );
    }

    HardConstraintVector prepareHardConstraints(const InputData& id, const DigitalSet& ds, const DigitalSet& pixelMask)
    {
        HardConstraintVector hcv(1);
        hcv[0] = new FixedPixels(id.radius,ds,pixelMask);

        return hcv;
    }

    TerminalWeightVector prepareTerminalWeights(const DataDistribution& DD, double dataTermWeight)
    {
        TerminalWeightVector twv(2);
        twv[0] = new Foreground(*DD.fgDistr,dataTermWeight);
        twv[1] = new Background(*DD.bgDistr,dataTermWeight);

        return twv;
    }

    EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds)
    {
        EdgeWeightVector ewv(1);
        ewv[0] = new Curvature(id.radius,ds);

        return ewv;
    }

}