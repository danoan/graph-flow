#ifndef GRAPH_FLOW_VARIANCE_H
#define GRAPH_FLOW_VARIANCE_H

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/derivates/Misc.h>

#include <graph-flow/core/EdgeWeight.h>

#include "model/Stats.h"

class Variance:public GraphFlow::Core::TerminalWeight
{
public:
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef TerminalWeight::Point Point;

public:

    Variance(const DigitalSet& ds, const cv::Mat& colorImage):
    img(colorImage),
    SF(ds.size()),
    SB(ds.domain().size()-ds.size())
    {
        for(auto p:ds.domain())
        {
            int row=img.rows-p[1];
            int col = p[0];

            if( ds(p) )
            {
                SF.add(&img.at<cv::Vec3b>(row,col));
            }else
            {
                SB.add(&img.at<cv::Vec3b>(row,col));
            }
        }

        SF.resolve();
        SB.resolve();
    }


    double operator()(const Point& p)
    {
        int row=img.rows-p[1];
        int col=p[0];

        const cv::Vec3b& c = img.at<cv::Vec3b>(row,col);

        double v1=pow(SF.mean[0] - c(0),2);
        double v2=pow(SF.mean[1] - c(1),2);
        double v3=pow(SF.mean[2] - c(2),2);

        double v = (v1-SF.var[0]) + (v2-SF.var[1]) + (v3-SF.var[2]);
        v/=pow(255,2);
        return exp(-v);
    }

    double weight() const{ return 1.0;}
    bool normalize() const{ return true;}
    TerminalType type() const{ return TerminalType::Source; }

private:
    Stats SF,SB;
    const cv::Mat& img;

};


#endif //GRAPH_FLOW_VARIANCE_H
