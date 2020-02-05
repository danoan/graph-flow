#include "graph-flow/utils/display.h"

namespace GraphFlow::Utils::Display
{
    void saveDigitalSetAsImage(const Domain& domain, const PointSet& ps, const std::string& outputFilepath)
    {
        DigitalSet ds(domain);
        ds.insert(ps.begin(),ps.end());
        saveDigitalSetAsImage(ds,outputFilepath);
    }

    void saveDigitalSetAsImage(const DigitalSet& ds,const std::string& outputFilepath)
    {
        typedef DIPaCUS::Representation::Image2D Image2D;
        Image2D image(ds.domain());


        DIPaCUS::Representation::digitalSetToImage(image,ds);
        DGtal::GenericWriter<Image2D>::exportFile(outputFilepath,image);
    }
}