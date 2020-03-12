#ifndef GRAPH_FLOW_HOMOGENEITY_H
#define GRAPH_FLOW_HOMOGENEITY_H

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/derivates/Misc.h>

#include <graph-flow/core/EdgeWeight.h>

class Homogeneity:public GraphFlow::Core::EdgeWeight
{
public:
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef EdgeWeight::Point Point;

    typedef std::map<Point,double> PointMap;


public:

    Homogeneity(const cv::Mat& colorImage,double boundaryWeight):img(colorImage),boundaryWeight(boundaryWeight)
    {}


    double operator()(const Point& p1, const Point& p2)
    {
        cv::Vec3d v1 = img.at<cv::Vec3b>( img.rows - p1[1], p1[0]);
        cv::Vec3d v2 = img.at<cv::Vec3b>( img.rows - p2[1], p2[0]);

        cv::Vec3d diff = v1-v2;
        double s = pow(diff[0],2) + pow(diff[1],2) + pow(diff[2],2);

        Point pdiff = p1-p2;
        double d = pow(pdiff[0],2) + pow(pdiff[1],2);
        double v = exp(-s*1.0/d); 

        return v;
    }

    double weight() const{ return boundaryWeight;}
    bool normalize() const{ return true;}

private:
    const cv::Mat& img;
    double boundaryWeight;

};


#endif //GRAPH_FLOW_CURVATURE_H
