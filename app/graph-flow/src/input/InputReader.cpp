#include <cstring>
#include "input/InputReader.h"

void usage(char* argv[])
{
    std::cerr << "Usage: " << argv[0] << " OutputFolder \n"
                                         "[-S Shape name(triangle, square, pentagon, heptagon, ball, ellipse, flower, bean, wave. default: square)]\n"
                                         "[-i Number of iterations (default: 10)]\n"
                                         "[-r Estimation ball radius (default: 5)]\n"
                                         "[-e Energy (elastica, selastica. default: elastica)]\n"
                                         "[-h Grid step (default:0.25)]\n"
                                         "[-a Length penalization (default:0.01)]\n"
                                         "[-b Curvature penalization (default:1.0)]\n"
                                         "[-O Optimization band (default:2)]\n"
                                         "[-n Maximum number of threads (default:4)]\n"
                                         "[-N Neighborhood size (default:2)]\n"
                                         "[-B Border width (automatic gridstep scaling) (default:20)]\n"
                                         "[-P Pixel mask filepath]" << std::endl;
}



InputData readInput(int argc, char* argv[])
{
    InputData id;

    int opt;
    while( (opt=getopt(argc,argv,"S:i:r:e:h:a:b:O:n:N:B:P:"))!=-1)
    {
        switch(opt)
        {
            case 'S':
            {
                id.shapeName = optarg;
                break;
            }
            case 'i':
            {
                id.iterations = std::atoi(optarg);
                break;
            }
            case 'r':
            {
                id.radius= std::atof(optarg);
                break;
            }
            case 'e':
            {
                if(strcmp(optarg,"elastica")==0) id.energy=InputData::EnergyType::Elastica;
                else if(strcmp(optarg,"selastica")==0) id.energy=InputData::EnergyType::SElastica;
                else throw std::runtime_error("Unrecognized energy!");
                break;
            }
            case 'h':
            {
                id.h= std::atof(optarg);
                break;
            }
            case 'a':
            {
                id.alpha = std::atof(optarg);
                break;
            }
            case 'b':
            {
                id.beta = std::atof(optarg);
                break;
            }
            case 'O':
            {
                id.optBand = std::atoi(optarg);
                break;
            }
            case 'n':
            {
                id.nThreads= std::atoi(optarg);
                break;
            }
            case 'N':
            {
                id.neighborhoodSize = std::atoi(optarg);
                break;
            }
            case 'B':
            {
                id.border= std::atoi(optarg);
                break;
            }
            case 'P':
            {
                id.pixelMaskFilepath = optarg;
                break;
            }
            default:
            {
                usage(argv);
                exit(1);
            }
        }
    }

    id.outputFolder = argv[optind++];
    return id;
}

std::string resolveEnergyName(InputData::EnergyType et)
{
    if(et==InputData::EnergyType::Elastica) return "elastica";
    else if(et==InputData::EnergyType::SElastica) return "selastica";
    else return "unknown";
}

void writeInputData(const InputData& id, std::ostream& os)
{
    os << "Shape name:" << id.shapeName << "\n"
    << "Ball radius:" << id.radius << "\n"
    << "Grid step:" << id.h  << "\n"
    << "Opt band:" << id.optBand  << "\n"
    << "Energy:" << resolveEnergyName(id.energy) << "\n"
    << "Length penalization:" << id.alpha  << "\n"
    << "Curvature penalization:" << id.beta  << "\n"
    << "Iterations:" << id.iterations  << "\n"
    << "neighborhood size:" << id.neighborhoodSize  << "\n"
    << "Max number of threads:" << id.nThreads  << "\n"
    << "Output folder:" << id.outputFolder  << "\n"
    << "Pixel mask filepath:" << id.pixelMaskFilepath << "\n";
}
