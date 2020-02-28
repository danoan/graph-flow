#ifndef GRAPH_FLOW_STATS_H
#define GRAPH_FLOW_STATS_H

#include <vector>
#include <opencv2/core.hpp>

struct Stats
{
    Stats(int n):n(n),count(0),c1(0),c2(0),c3(0)
    {
        colors.resize(n);
    }

    void add(const cv::Vec3b* v)
    {
        c1+=(*v)(0);
        c2+=(*v)(1);
        c3+=(*v)(2);

        colors[count++]=v;
    }

    void resolve()
    {
        mean[0]=c1/n;
        mean[1]=c2/n;
        mean[2]=c3/n;

        var[0]=var[1]=var[2]=0;
        for(int i=0;i<n;++i)
        {
            var[0]+= pow( (*colors[i])(0) - mean[0],2)/(n-1);
            var[1]+= pow( (*colors[i])(1) - mean[1],2)/(n-1);
            var[2]+= pow( (*colors[i])(2) - mean[2],2)/(n-1);
        }

        det = pow( var[0] + var[1] + var[2],2);

    }

    std::vector<const cv::Vec3b*> colors;
    int count;

    double n;
    double c1,c2,c3;
    double mean[3],var[3];
    double det;
};

#endif //GRAPH_FLOW_STATS_H
