#include "graph-flow/utils/energy.h"

namespace GraphFlow::Utils::Energy
{
    void computeBoundaryCurve(Curve& boundOut,
                              const DigitalSet& dsIn)
    {
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Domain Domain;

        typedef DGtal::SurfelAdjacency<KSpace::dimension> SurfelAdjacency;
        typedef DGtal::Surfaces<KSpace> Surfaces;

        typedef DIPaCUS::Representation::Image2D Image2D;
        typedef DGtal::functors::SimpleThresholdForegroundPredicate<Image2D> ThreshPredicate;

        //Using extended domain because tracker has difficult to continue
        //when using a tight domain.
        Domain extDomain( dsIn.domain().lowerBound() - Point(1,1), dsIn.domain().upperBound() + Point(1,1) );
        KSpace KImage;

        KImage.init(extDomain.lowerBound(),extDomain.upperBound(),true);

        Point pIn=*dsIn.begin();
        Point pOut=dsIn.domain().lowerBound();
        while(dsIn(pOut)) pOut = pOut+Point(1,0);

        DGtal::Z2i::SCell imageBel = Surfaces::findABel(KImage, dsIn, pIn,pOut);

        SurfelAdjacency SAdj(true);

        std::vector<DGtal::Z2i::SCell> boundarySCells;
        Surfaces::track2DBoundary(boundarySCells,
                                  KImage,
                                  SAdj,
                                  dsIn,
                                  imageBel);

        boundOut.initFromSCellsVector(boundarySCells);
    }

    double elastica(const DigitalSet& ds,double ballRadius,double h,double alpha)
    {
        using namespace DGtal::Z2i;
        using namespace GEOC::API::GridCurve;

        const Domain& domain = ds.domain();
        KSpace kspace;
        kspace.init(domain.lowerBound(),domain.upperBound(),true);

        std::vector<DIPaCUS::Misc::ConnectedComponent> vcc;
        DIPaCUS::Misc::getConnectedComponents(vcc,ds);

        double value=0;
        DigitalSet tempDS(ds.domain());
        for(auto cc:vcc)
        {
            if(cc.size()<10) continue;

            tempDS.clear();
            tempDS.insert(cc.begin(),cc.end());

            Curve curve;
            computeBoundaryCurve(curve,tempDS);

            Length::EstimationsVector lengthEV;
            Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED>(kspace,curve.begin(),curve.end(),lengthEV,h,NULL);

            GEOC::Estimator::Standard::IICurvatureExtraData iiData(true,ballRadius);
            Curvature::EstimationsVector curvatureEV;
            GEOC::Estimator::Standard::IICurvature(tempDS,curve.begin(),curve.end(),curvatureEV,h,&iiData);

            for(int i=0;i<curvatureEV.size();++i)
            {
                value+=pow(curvatureEV[i],2)*lengthEV[i] + alpha*lengthEV[i];
            }
        }


        return value;

    }

    double sElastica(const DigitalSet& ds,double ballRadius,double h,double alpha)
    {
        using namespace DGtal::Z2i;
        using namespace GEOC::API::GridCurve;

        const Domain& domain = ds.domain();
        KSpace kspace;
        kspace.init(domain.lowerBound(),domain.upperBound(),true);

        std::vector<DIPaCUS::Misc::ConnectedComponent> vcc;
        DIPaCUS::Misc::getConnectedComponents(vcc,ds);

        double value=0;
        DigitalSet tempDS(ds.domain());
        for(auto cc:vcc)
        {
            if(cc.size()<10) continue;

            tempDS.clear();
            tempDS.insert(cc.begin(),cc.end());

            Curve curve;
            computeBoundaryCurve(curve,tempDS);
            Length::EstimationsVector lengthEV;
            Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED>(kspace,curve.begin(),curve.end(),lengthEV,h,NULL);

            GEOC::Estimator::Standard::IICurvatureExtraData iiData(true,ballRadius);
            Curvature::EstimationsVector curvatureEV;
            Curvature::identityOpen<Curvature::EstimationAlgorithms::ALG_II>(kspace,curve.begin(),curve.end(),curvatureEV,h,&iiData);


            for(int i=0;i<curvatureEV.size();++i)
            {
                value+=pow(curvatureEV[i],2)*h + alpha*lengthEV[i];
            }
        }

        return value;

    }
}