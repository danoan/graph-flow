#ifndef GRAPH_FLOW_CURVATURE_H
#define GRAPH_FLOW_CURVATURE_H

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/derivates/Misc.h>

#include <graph-flow/core/EdgeWeight.h>

class Curvature:public GraphFlow::Core::EdgeWeight
{
public:
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef DIPaCUS::Misc::DigitalBallIntersection DigitalBallIntersection;
    typedef EdgeWeight::Point Point;

    typedef std::map<Point,double> PointMap;

private:

    double computeAreaDifference(const Point& p)
    {
        intersectionSet->clear();
        DBI->operator()(*intersectionSet,p);
        return pow( DBI->digitalBall().size()/2.0 -(double) intersectionSet->size(),2);
    }

public:

    Curvature(double radius, const DigitalSet& ds):radius(radius)
    {
        DBI = new DigitalBallIntersection(radius,ds);
        intersectionSet = new DigitalSet(DBI->domain());
    }

    ~Curvature()
    {
        delete DBI;
        delete intersectionSet;
    }

    double operator()(const Point& p1, const Point& p2)
    {
        if(pm.find(p1)==pm.end())
            pm[p1] = computeAreaDifference(p1);

        if(pm.find(p2)==pm.end())
            pm[p2] = computeAreaDifference(p2);

        return (pm[p1]+pm[p2])/2.0;
    }

    double weight() const{ return 1.0;}
    bool normalize() const{ return true;}

private:
    PointMap pm;
    double radius;
    DigitalBallIntersection* DBI;
    DigitalSet* intersectionSet;
};


#endif //GRAPH_FLOW_CURVATURE_H
