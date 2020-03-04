#include "input/InputReader.h"

void usage(char* argv[])
{
    std::cerr << "Usage: " << argv[0] << " GrabcutObjectFilepath OutputFolder \n"
                                         "[-i Number of iterations (default: 10)]\n"
                                         "[-r Estimation ball radius (default: 5)]\n"
                                         "[-e Energy (elastica, selastica. default: elastica)]\n"
                                         "[-h Grid step (default:0.25)]\n"
                                         "[-a Length penalization (default:0.01)]\n"
                                         "[-g Regional term penalization (default:1)]\n"
                                         "[-b Boundary term penalization (default:2)]\n"
                                         "[-k Curvature term penalization (default:0.5)]\n"
                                         "[-G Grabcut iterations (default:1)]\n"
                                         "[-O Optimization band (default:2)]\n"
                                         "[-n Maximum number of threads (default:4)]\n"
                                         "[-N neighborhood size (default:2)]\n"
                                         "[-w print energy value]\n"
                                         "[-P Pixel mask filepath]" << std::endl;
}



InputData readInput(int argc, char* argv[])
{
    InputData id;

    int opt;
    while( (opt=getopt(argc,argv,"i:r:e:h:a:g:b:k:G:O:n:N:P:w"))!=-1)
    {
        switch(opt)
        {
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
            case 'g':
            {
                id.regionalTermWeight = std::atof(optarg);
                break;
            }
            case 'b':
            {
                id.boundaryTermWeight = std::atof(optarg);
                break;
            }
            case 'k':
            {
                id.curvatureTermWeight = std::atof(optarg);
                break;
            }
            case 'G':
            {
                id.grabcutIterations= std::atoi(optarg);
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
            case 'P':
            {
                id.pixelMaskFilepath = optarg;
                break;
            }
            case 'w':
            {
                id.printEnergyValue = true;
                break;
            }
            default:
            {
                usage(argv);
                exit(1);
            }
        }
    }

    id.gcoFilepath = argv[optind++];
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
    os << "GrabcutObject filepath:" << id.gcoFilepath<< "\n"
    << "Ball radius:" << id.radius << "\n"
    << "Grid step:" << id.h  << "\n"
    << "Opt band:" << id.optBand  << "\n"
    << "Energy:" << resolveEnergyName(id.energy) << "\n"
    << "Length penalization:" << id.alpha  << "\n"
    << "Regional term:" << id.regionalTermWeight << "\n"
    << "Boundary term:" << id.boundaryTermWeight << "\n"
    << "Curvature term:" << id.curvatureTermWeight << "\n"
    << "Iterations:" << id.iterations  << "\n"
    << "neighborhood size:" << id.neighborhoodSize  << "\n"
    << "Max number of threads:" << id.nThreads  << "\n"
    << "Output folder:" << id.outputFolder  << "\n"
    << "Pixel mask filepath:" << id.pixelMaskFilepath << "\n";
}
