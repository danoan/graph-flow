#include "InputReader.h"

void usage(char* argv[])
{
    std::cerr << "Usage: " << argv[0] << " OutputFolder \n"
                                         "[-S Shape name(triangle, square, pentagon, heptagon, ball, ellipse, flower, bean, wave. default: square)]\n"
                                         "[-i Number of iterations (default: 10)]\n"
                                         "[-r Estimation ball radius (default: 5)]\n"
                                         "[-h Grid step (default:0.25)]\n"
                                         "[-a Length penalization (default:0.01)]\n"
                                         "[-O Optimization band (default:2)]\n"
                                         "[-n Maximum number of threads (default:4)]\n"
                                         "[-N Neighborhood size (default:2)]" << std::endl;
}



InputData readInput(int argc, char* argv[])
{
    InputData id;

    int opt;
    while( (opt=getopt(argc,argv,"S:i:r:h:a:O:n:N:"))!=-1)
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