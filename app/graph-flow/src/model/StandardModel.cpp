#include "model/StandardModel.h"

namespace StandardModel
{
    HardConstraintVector prepareHardConstraints(const InputData& id, const DigitalSet& ds, const DigitalSet& pixelMask)
    {
        HardConstraintVector hcv(1);
        hcv[0] = new FixedPixels(id.radius,ds,pixelMask);

        return hcv;
    }

    TerminalWeightVector prepareTerminalWeights(const InputData& id, const DigitalSet& ds)
    {
        using namespace GraphFlow::Utils;

        auto dtInterior = Digital::interiorDistanceTransform(ds.domain(),ds);
        auto dtExterior = Digital::exteriorDistanceTransform(ds.domain(),ds);

        return prepareTerminalWeights(id,dtInterior,dtExterior);
    }

    TerminalWeightVector prepareTerminalWeights(const InputData& id, const DTL2& dtInterior, const DTL2& dtExterior)
    {
        TerminalWeightVector twv(2);
        twv[0] = new Foreground(dtInterior,id.optBand,id.radius);
        twv[1] = new Background(dtExterior,id.optBand,id.radius);

        return twv;
    }

    EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds)
    {
        EdgeWeightVector ewv(1);
        ewv[0] = new Curvature(id.radius,id.h,ds);

        return ewv;
    }

}