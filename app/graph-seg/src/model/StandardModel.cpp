#include "model/StandardModel.h"

namespace StandardModel
{
    double boundaryCoefficient(const Point& p, const DigitalSet& ds, const cv::Mat& img, const DigitalSet& kernel)
    {
        cv::Vec3d in=0;
        cv::Vec3d out=0;
        double nInn=0;
        double nOut=0;
        for(const Point& kp:kernel)
        {
            Point np = p+kp;
            int nprow = img.rows - np[1];
            int npcol = np[0];

            if(ds(np))
            {
                in += img.at<cv::Vec3b>(nprow, npcol)/255.0;
                ++nInn;
            }
            else
            {
                out+=img.at<cv::Vec3b>(nprow,npcol)/255.0;
                ++nOut;
            }

        }

        double mIn = (in[0]+in[1]+in[2])/nInn;
        double mOut = (out[0]+out[1]+out[2])/nOut;

        double c=std::fabs( (mIn-mOut) );
        c=3-c;

        return exp(c);
    }

    double boundaryValueAlternative(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        const cv::Mat& img = DD.fgDistr->img;

        DigitalSet boundary(ds.domain());
        DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(boundary,ds);

        DigitalSet kernel = DIPaCUS::Shapes::ball(1.0,0,0,10);


        double v=0;
        for(auto p:boundary)
        {
            v+=boundaryCoefficient(p,ds,img,kernel);
        }

        if(boundary.empty()) return v;
        v=v/( (double) boundary.size() );

        return v;
    }

    double boundaryValue(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        const cv::Mat& img = DD.fgDistr->img;

        DigitalSet boundary(ds.domain());
        DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(boundary,ds);

        Homogeneity homogeneity(img,id.boundaryTermWeight);

        double v=0;
//        Point neigh[8]={Point(0,1),Point(1,0),Point(-1,0),Point(0,-1),
//                        Point(1,1),Point(1,-1),Point(-1,1), Point(-1,-1)};
        Point neigh[4]={Point(0,1),Point(1,0),Point(-1,0),Point(0,-1)};
        for(auto p:boundary)
        {
            for(auto n:neigh)
            {
                auto np = p+n;
                v+=homogeneity.operator()(p,np);
            }

        }

        if(boundary.empty()) return v;
        v=v/( (double) boundary.size() );

        return v;


    }

    double regionValue(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        double fgv=0;
        double bgv=0;
        return regionValue(fgv,bgv,id,ds,DD);
    }

    double regionValue(double& fgv, double& bgv,const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        const cv::Mat& img = DD.fgDistr->img;
        bgv=0;
        fgv=0;
        for(auto p:ds.domain())
        {
            int prow=img.rows-p[1];
            int pcol=p[0];

            if(ds(p))
            {
                fgv+=-log( 1- (*DD.bgDistr)(prow,pcol) );
            }else
            {
                bgv+=-log( 1-(*DD.fgDistr)(prow,pcol) );
            }
        }

        //bgv-fgv. If greater than 0, alpha should be 1, so the shape shrinks.
        return (fgv+bgv);
    }

    double evaluateData(double& fgv, double& bgv, const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        double bv = id.boundaryTermWeight*boundaryValue(id,ds,DD);
        double rv = id.regionalTermWeight*regionValue(fgv,bgv,id,ds,DD);

//        std::cout << "(" << bv << "," << rv << "), ";

        return rv+bv;
    }

    double evaluateData(const InputData& id,const DigitalSet& ds, const DataDistribution& DD)
    {
        double fgv,bgv;
        return evaluateData(fgv,bgv,id,ds,DD);
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
        ewv[1] = new Homogeneity(colorImage,id.boundaryTermWeight);

        return ewv;
    }

}