#include "graph-flow/utils/energy.h"

namespace GraphFlow::Utils::Energy
{
    double elastica(const DigitalSet& ds,double ballRadius,double h,double alpha)
    {
        using namespace DGtal::Z2i;
        using namespace GEOC::API::GridCurve;

        const Domain& domain = ds.domain();
        KSpace kspace;
        kspace.init(domain.lowerBound(),domain.upperBound(),true);

        Curve curve;
        DIPaCUS::Misc::computeBoundaryCurve(curve,ds);
        Length::EstimationsVector lengthEV;
        Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED>(kspace,curve.begin(),curve.end(),lengthEV,h,NULL);

        GEOC::Estimator::Standard::IICurvatureExtraData iiData(true,ballRadius);
        Curvature::EstimationsVector curvatureEV;
        Curvature::identityOpen<Curvature::EstimationAlgorithms::ALG_II>(kspace,curve.begin(),curve.end(),curvatureEV,h,&iiData);

        double value=0;
        for(int i=0;i<curvatureEV.size();++i)
        {
            value+=pow(curvatureEV[i],2)*lengthEV[i] + alpha*lengthEV[i];
        }

        return value;

    }
}