#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/date_time.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/volumes/distance/DistanceTransformation.h>
#include <DGtal/io/writers/GenericWriter.h>

#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/Transform.h>
#include <DIPaCUS/derivates/Misc.h>
#include <DIPaCUS/base/Shapes.h>



using namespace DGtal::Z2i;

typedef lemon::ListDigraph ListDigraph;












struct FlowGraph
{

};

FlowGraph::NodeWeightEvaluation weightFunction(double radius)
{
    return [radius](const DigitalSet& ds, const Point& p, bool sourceTarget)->double
    {
        if(sourceTarget) return pow( M_PI*pow(radius,2),2)*1000;
        else
        {
            DigitalSet ball = DIPaCUS::Shapes::ball(1.0,p[0],p[1],radius);
            DigitalSet intersection(ball.domain());
            DIPaCUS::SetOperations::setIntersection(intersection,ball,ds);

            return pow(ball.size()/2.0 -(double) intersection.size(),2);
        }
    };
}



struct Candidate
{
    Candidate(const DigitalSet &dsInput) : dsInput(dsInput) {}
    ~Candidate(){delete dsOutput;}

    void evaluate(double radius,double h,double alpha, int optBand)
    {
        FlowGraph fg(dsInput,optBand,weightFunction(radius));
        dsOutput = new DigitalSet( fg.output );

        cutValue = elastica(*dsOutput,radius,h,alpha);
    }


    DigitalSet dsInput;
    DigitalSet* dsOutput;
    double cutValue;
};


int main(int argc, char* argv[])
{
    double shapeRadius=20;

    std::string shapeName = argv[1];
    int iterations = std::atoi(argv[2]);
    double radius = std::atof(argv[3]);
    double h = std::atof(argv[4]);
    double alpha = std::atof(argv[5]);
    int optBand = std::atoi(argv[6]);
    std::string outputFolder=argv[7];

    boost::filesystem::create_directories(outputFolder);

    DigitalSet _ds = resolveShape(shapeName,shapeRadius,h);
    DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,Point(20,20));

    Candidate* candidates[3];

    saveDigitalSetAsImage(ds, outputFolder+"/initial.pgm");
    Timer::start();
    for(int i=0;i<iterations;++i)
    {
        candidates[0]=new Candidate(ds);
        candidates[1]=new Candidate( DigitalSet(dilate(ds)) );
        candidates[2]=new Candidate( DigitalSet(erode(ds)) );

        for(int k=0;k<3;++k) candidates[k]->evaluate(radius,h,alpha,optBand);
        std::sort(candidates,candidates+3,[](const Candidate* c1, const Candidate* c2)->bool{return c1->cutValue < c2->cutValue;});

        DigitalSet* dsOutput = candidates[0]->dsOutput;
        saveDigitalSetAsImage(*dsOutput, outputFolder+"/" + std::to_string(i) + ".pgm");
        ds.clear();
        ds.insert(dsOutput->begin(),dsOutput->end());

        for(int k=0;k<3;++k) delete candidates[k];
    }


    Timer::end(std::cout);


    return 0;
}