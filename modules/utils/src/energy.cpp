#include "graph-flow/utils/energy.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/colormaps/TickedColorMap.h"
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

    double elastica(const DigitalSet& ds,double ballRadius,double h,double alpha,double beta)
    {
        using namespace DGtal::Z2i;
        using namespace GEOC::API::GridCurve;

        const Domain& domain = ds.domain();
        KSpace kspace;
        kspace.init(domain.lowerBound(),domain.upperBound(),true);

        std::vector< SCell > belVector;
        typedef DGtal::SurfelAdjacency<KSpace::dimension> SurfelAdjacency;
        SurfelAdjacency SAdj(true);

        std::set<SCell> bdry;
        DGtal::Surfaces<KSpace>::sMakeBoundary( bdry, kspace, ds,
                       kspace.lowerBound(),
                       kspace.upperBound() );

        while(!bdry.empty()) {
            std::set<SCell> aConnectedSCellSet;
            SCell aCell = *(bdry.begin());
            belVector.push_back(aCell);
            DGtal::Surfaces<KSpace>::trackBoundary(aConnectedSCellSet, kspace, SAdj, ds, aCell);
            for(auto it=aConnectedSCellSet.begin();it!=aConnectedSCellSet.end();++it) bdry.erase(*it);

        }

        double value=0;
        for(auto scell:belVector)
        {

            std::vector<DGtal::Z2i::SCell> orderedSCells;
            DGtal::Surfaces<KSpace>::track2DBoundary(orderedSCells,
                                      kspace,
                                      SAdj,
                                      ds,
                                      scell);
            Curve curve;
            curve.initFromSCellsVector(orderedSCells);



            if(curve.size()<10){ value+=pow(1.0/h,2); continue; }

            Length::EstimationsVector lengthEV;
            Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED>(kspace,curve.begin(),curve.end(),lengthEV,h,NULL);

            GEOC::Estimator::Standard::IICurvatureExtraData iiData(true,ballRadius);
            Curvature::EstimationsVector curvatureEV;
            GEOC::Estimator::Standard::IICurvature(ds,curve.begin(),curve.end(),curvatureEV,h,&iiData);

            for(int i=0;i<curvatureEV.size();++i)
            {
                value+=alpha*lengthEV[i] + beta*pow(curvatureEV[i],2)*lengthEV[i];
            }
        }


        return value;

    }

    double sElastica(const DigitalSet& ds,double ballRadius,double h,double alpha,double beta)
    {
        using namespace DGtal::Z2i;
        using namespace GEOC::API::GridCurve;

        const Domain& domain = ds.domain();
        KSpace kspace;
        kspace.init(domain.lowerBound(),domain.upperBound(),true);

        std::vector< SCell > belVector;
        typedef DGtal::SurfelAdjacency<KSpace::dimension> SurfelAdjacency;
        SurfelAdjacency SAdj(true);

        std::set<SCell> bdry;
        DGtal::Surfaces<KSpace>::sMakeBoundary( bdry, kspace, ds,
                                                kspace.lowerBound(),
                                                kspace.upperBound() );

        while(!bdry.empty()) {
            std::set<SCell> aConnectedSCellSet;
            SCell aCell = *(bdry.begin());
            belVector.push_back(aCell);
            DGtal::Surfaces<KSpace>::trackBoundary(aConnectedSCellSet, kspace, SAdj, ds, aCell);
            for(auto it=aConnectedSCellSet.begin();it!=aConnectedSCellSet.end();++it) bdry.erase(*it);

        }

        double value=0;
        for(auto scell:belVector)
        {

            std::vector<DGtal::Z2i::SCell> orderedSCells;
            DGtal::Surfaces<KSpace>::track2DBoundary(orderedSCells,
                                                     kspace,
                                                     SAdj,
                                                     ds,
                                                     scell);
            Curve curve;
            curve.initFromSCellsVector(orderedSCells);
            if(curve.size()<10){ value+=1.0/h; continue; }


            Length::EstimationsVector lengthEV;
            Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED>(kspace,curve.begin(),curve.end(),lengthEV,h,NULL);

            GEOC::Estimator::Standard::IICurvatureExtraData iiData(true,ballRadius);
            Curvature::EstimationsVector curvatureEV;
            Curvature::identityOpen<Curvature::EstimationAlgorithms::ALG_II>(kspace,curve.begin(),curve.end(),curvatureEV,h,&iiData);


            for(int i=0;i<curvatureEV.size();++i)
            {
                value+=alpha*lengthEV[i] + beta*pow(curvatureEV[i],2)*h;
            }
        }

        return value;

    }
}