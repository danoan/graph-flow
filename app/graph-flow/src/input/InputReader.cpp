#include "input/InputReader.h"

namespace App {
void usage(char *argv[]) {
  std::cerr << "Usage: " << argv[0] << " OutputFolder \n"
                                       "[-S Shape name(triangle, square, pentagon, heptagon, ball, ellipse, flower, bean, wave. default: square)]\n"
                                       "[-i Number of iterations (default: 10)]\n"
                                       "[-r Estimation ball radius (default: 5)]\n"
                                       "[-v Validation ball radius (default: 5)]\n"
                                       "[-h Grid step (default:0.25)]\n"
                                       "[-a Length penalization (default:0.01)]\n"
                                       "[-b Curvature penalization (default:1.0)]\n"
                                       "[-O Optimization band (default:2)]\n"
                                       "[-n Maximum number of threads (default:4)]\n"
                                       "[-N Neighborhood size (default:2)]\n"
                                       "[-B Border width (automatic gridstep scaling) (default:20)]\n"
                                       "[-H Neighborhood type (morphology,random) (default:morphology)]\n"
                                       "[-P Pixel mask filepath]\n"
                                       "[-w Output energy at each iteration]\n"
                                       "[-d Display flow]\n"
                                       "[-s Save figures]" << std::endl;
}

InputData readInput(int argc, char *argv[]) {
  InputData id;

  int opt;
  while ((opt = getopt(argc, argv, "S:i:r:v:h:a:b:O:n:N:B:H:P:wds"))!=-1) {
    switch (opt) {
      case 'S': {
        id.shapeName = optarg;
        break;
      }
      case 'i': {
        id.iterations = std::atoi(optarg);
        break;
      }
      case 'r': {
        id.radius = std::atof(optarg);
        break;
      }
      case 'v': {
        id.vradius = std::atof(optarg);
        break;
      }
      case 'h': {
        id.h = std::atof(optarg);
        break;
      }
      case 'a': {
        id.alpha = std::atof(optarg);
        break;
      }
      case 'b': {
        id.beta = std::atof(optarg);
        break;
      }
      case 'O': {
        id.optBand = std::atoi(optarg);
        break;
      }
      case 'n': {
        id.nThreads = std::atoi(optarg);
        break;
      }
      case 'N': {
        id.neighborhoodSize = std::atoi(optarg);
        break;
      }
      case 'B': {
        id.border = std::atoi(optarg);
        break;
      }
      case 'H': {
        if( strcmp(optarg,"morphology")==0 ) id.neighborhoodType = InputData::Morphology;
        else if(strcmp(optarg,"random")==0 ) id.neighborhoodType = InputData::Random;
        else throw std::runtime_error("Invalid neighborhood type");
        break;
      }
      case 'P': {
        id.pixelMaskFilepath = optarg;
        break;
      }
      case 'w': {
        id.printEnergyValue = true;
        break;
      }
      case 'd': {
        id.displayFlow = true;
        break;
      }
      case 's': {
        id.saveAllFigures = true;
        break;
      }
      default: {
        usage(argv);
        exit(1);
      }
    }
  }

  id.outputFolder = argv[optind++];
  return id;
}

std::string resolveNeighborhoodType(InputData::NeighborhoodType nt){
  if(nt==InputData::Morphology) return "Morphology";
  else if(nt==InputData::Random) return "Random";
  else return "Unknown";
}

void writeInputData(const InputData &id, size_t nPixels, std::ostream &os) {
  os << "Shape name:" << id.shapeName << "\n"
     << "Number of pixels:" << nPixels << "\n"
     << "Estimation radius:" << id.radius << "\n"
     << "Validation radius:" << id.vradius << "\n"
     << "Grid step:" << id.h << "\n"
     << "Opt band:" << id.optBand << "\n"
     << "Length penalization:" << id.alpha << "\n"
     << "Curvature penalization:" << id.beta << "\n"
     << "Iterations:" << id.iterations << "\n"
     << "Neighborhood size:" << id.neighborhoodSize << "\n"
     << "Neighborhood type:" << resolveNeighborhoodType(id.neighborhoodType) << "\n"
     << "Max number of threads:" << id.nThreads << "\n"
     << "Output folder:" << id.outputFolder << "\n"
     << "Pixel mask filepath:" << id.pixelMaskFilepath << "\n"
     << "Print energy value:" << (id.printEnergyValue ? "True" : "False") << "\n"
     << "Display flow:" << (id.displayFlow ? "True" : "False") << "\n"
     << "Save figures:" << (id.saveAllFigures ? "True" : "False") << "\n";
}
}