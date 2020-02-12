#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>
#include <BTools/utils/model/GrabCutObject.h>

#include <graph-flow/utils/display.h>
#include <graph-flow/utils/string.h>

#include "input/InputData.h"
#include "input/InputReader.h"
#include "model/DataDistribution.h"
#include "model/GraphSegInput.h"
#include "model/GraphSegIteration.h"

#include "utils.h"
#include "graph-seg.h"

using namespace DGtal::Z2i;
using namespace GraphFlow::Core;
using namespace GraphFlow::Utils;



DigitalSet prepareShape(const DataDistribution& DD, Point initialBorder)
{
    const cv::Mat& segResult = DD.segResultImg;

    Domain tempDomain(Point(0,0),
                      Point(segResult.cols-1,
                            segResult.rows-1)
    );
    DigitalSet tempDS(tempDomain);

    //Convert inputImg to 1-channel grayscale image.
    cv::Mat grayscale(segResult.size(),
                      segResult.type());
    if(segResult.type()!=CV_8UC1)
        cv::cvtColor(segResult,grayscale,cv::COLOR_RGB2GRAY,1);
    else
        grayscale = segResult;

    DIPaCUS::Representation::CVMatToDigitalSet(tempDS,
                                               grayscale,
                                               1);

    return tempDS;
}

int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    boost::filesystem::create_directories(id.outputFolder);


    DataDistribution DD(id);
    DigitalSet ds = prepareShape(DD,Point(20,20));
    GraphSegInput gsi(id,ds,DD);


    std::ofstream ofsInputData(id.outputFolder + "/inputData.txt");
    writeInputData(id,ofsInputData);
    ofsInputData.flush(); ofsInputData.close();

    std::ofstream ofsEnergy(id.outputFolder + "/energy.txt");


    IterationCallback iterationCallback=[&id,&ofsEnergy](const GraphSegIteration& gfIteration)->void
    {
//        Display::saveDigitalSetAsImage(gfIteration.ds,id.outputFolder+"/" + String::nDigitsString(gfIteration.iteration,4) + ".pgm");
        writeEnergyData(gfIteration,ofsEnergy);
    };

    Timer T;
    T.start();
    DigitalSet outputDS=graphSeg(gsi,ofsEnergy,iterationCallback);
    ofsEnergy << "#Execution time: ";
    T.end(ofsEnergy);
    ofsEnergy.flush(); ofsEnergy.close();

    outputImages(gsi.dataDistribution.gco,outputDS,id.outputFolder);

    return 0;
}
