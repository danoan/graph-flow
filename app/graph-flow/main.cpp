#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>

#include <graph-flow/utils/display.h>
#include <graph-flow/utils/string.h>

#include "input/InputData.h"
#include "input/InputReader.h"
#include "model/GraphFlowInput.h"
#include "model/GraphFlowIteration.h"

#include "utils.h"
#include "graph-flow.h"

using namespace DGtal::Z2i;
using namespace GraphFlow::Core;
using namespace GraphFlow::Utils;


std::pair<DigitalSet,DigitalSet> prepareShapeAndMask(const InputData& id)
{
    DigitalSet _ds = Digital::resolveShape(id.shapeName,id.h);
    Point lb,ub;

    _ds.computeBoundingBox(lb,ub);
    Point border(20/id.h,20/id.h);
    Point shift = -lb+border;

    DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,border);
    DigitalSet pixelMask = getPixelMask(id.pixelMaskFilepath,ds.domain(),shift);

    return std::make_pair(ds,pixelMask);
}


int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    boost::filesystem::create_directories(id.outputFolder);

    auto shapeAndMask = prepareShapeAndMask(id);
    DigitalSet& ds = shapeAndMask.first;
    DigitalSet& pixelMask = shapeAndMask.second;

    if(pixelMask.size()>0)
        Display::saveDigitalSetAsImage(pixelMask,id.outputFolder + "/pixelMask.pgm");

    GraphFlowInput gfi(id,ds,pixelMask);

    std::ofstream ofsInputData(id.outputFolder + "/inputData.txt");
    writeInputData(id,ofsInputData);
    ofsInputData.flush(); ofsInputData.close();

    std::ofstream ofsEnergy(id.outputFolder + "/energy.txt");


    IterationCallback iterationCallback=[&id,&ofsEnergy](const GraphFlowIteration& gfIteration)->void
    {
        Display::saveDigitalSetAsImage(gfIteration.ds,id.outputFolder+"/" + String::nDigitsString(gfIteration.iteration,4) + ".pgm");
        writeEnergyData(gfIteration,ofsEnergy);
    };
    
    Timer T;
    T.start();
    graphFlow(gfi,ofsEnergy,iterationCallback);
    ofsEnergy << "#Execution time: ";
    T.end(ofsEnergy);
    ofsEnergy.flush(); ofsEnergy.close();

    return 0;
}


