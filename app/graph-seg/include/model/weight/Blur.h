#ifndef GRAPH_FLOW_BLUR_H
#define GRAPH_FLOW_BLUR_H

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/derivates/Misc.h>

#include <graph-flow/core/EdgeWeight.h>

class Blur:public GraphFlow::Core::EdgeWeight
{
public:
    typedef DGtal::Z2i::DigitalSet DigitalSet;

public:

    Blur(const DigitalSet& ds, const cv::Mat& colorImage):
            img(colorImage)
    {
        blurred = cv::Mat::zeros(colorImage.size(),colorImage.type());
        cv::blur(img,blurred,cv::Size(5,5));
    }

    double computePointCoefficient(const Point& p)
    {
        double M=255.0;
        int prow = img.rows - p[1];
        int pcol = p[0];

        cv::Vec3d diff = img.at<cv::Vec3b>(prow,pcol)-blurred.at<cv::Vec3b>(prow,pcol );
        for(int i=0;i<3;++i) diff[i]=std::fabs(diff[i]);
        diff/=M;

        return pow(1-diff[0],2)+pow(1-diff[1],2)+pow(1-diff[2],2);
    }

    double operator()(const Point& p1, const Point& p2)
    {

        double c1 = computePointCoefficient(p1);
        double c2 = computePointCoefficient(p2);

        return c1+c2;
    }

    double weight() const{ return 1.0;}
    bool normalize() const{ return true;}

private:
    const cv::Mat& img;
    cv::Mat blurred;

};


#endif //GRAPH_FLOW_BLUR_H
