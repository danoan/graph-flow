#include "utils.h"

void writeEnergyData(const GraphFlowIteration& gfIteration,std::ostream& os)
{
    using namespace GraphFlow::Utils;
    int colLength=20;

    os << String::fixedStrLength(colLength,gfIteration.iteration)
    << String::fixedStrLength(colLength,gfIteration.value) << "\n";
}

void writeEnergyData(std::ostream& os)
{
    using namespace GraphFlow::Utils;
    int colLength=20;
    os << String::fixedStrLength(colLength,"#Iteration")
    << String::fixedStrLength(colLength,"Energy value") << "\n";
}

double evaluateEnergy(const InputData& id, const DigitalSet& ds)
{
    using namespace GraphFlow::Utils;
    return Energy::elastica(ds,id.vradius,id.h,id.alpha,id.beta);
}

DigitalSet getPixelMask(const std::string& pixelMaskFilepath, const Domain& domain, const Point& shift)
{
    DigitalSet _dsOutput(domain);
    if(pixelMaskFilepath=="") return _dsOutput;

    DIPaCUS::Representation::imageAsDigitalSet(_dsOutput,pixelMaskFilepath,1);
    
    DigitalSet dsOutput(domain);
    for(auto p:_dsOutput) dsOutput.insert(p+shift);
    return dsOutput;
}
