#include "input/InputReader.h"

#include "input/InputData.h"

namespace App {
void usage(char *argv[]) {
  std::cerr
      << "Usage: " << argv[0]
      << " GrabcutObjectFilepath OutputFolder \n"
         "[-i Number of iterations (default: 10)]\n"
         "[-r Estimation ball radius (default: 5)]\n"
         "[-v Validation ball radius (default: 5)]\n"
         "[-a Length penalization (default:0.01)]\n"
         "[-g Regional term penalization (default:1)]\n"
         "[-k Curvature term penalization (default:0.5)]\n"
         "[-t Tolerance. Stop if change between iterations is smaller than "
         "tolerance (>=0) (default:-1, never stop)]\n"
         "[-G Grabcut iterations (default:1)]\n"
         "[-O Optimization band (default:2)]\n"
         "[-n Maximum number of threads (default:4)]\n"
         "[-N neighborhood size (default:2)]\n"
         "[-H neighborhood type (morphology, random) (default:morphology)]\n"
         "[-w print energy value]\n"
         "[-s save figures]\n"
         "[-d display flow]"
      << std::endl;
}

InputData readInput(int argc, char *argv[]) {
  InputData id;

  int opt;
  while ((opt = getopt(argc, argv, "i:r:v:a:g:k:t:G:O:n:N:H:wsd")) != -1) {
    switch (opt) {
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
      case 'a': {
        id.alpha = std::atof(optarg);
        break;
      }
      case 'g': {
        id.regionalTermWeight = std::atof(optarg);
        break;
      }
      case 'k': {
        id.curvatureTermWeight = std::atof(optarg);
        break;
      }
      case 't': {
        id.tolerance = std::atof(optarg);
        break;
      }
      case 'G': {
        id.grabcutIterations = std::atoi(optarg);
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
      case 'H': {
        if (strcmp(optarg, "morphology") == 0)
          id.neighborhoodType = InputData::Morphology;
        else if (strcmp(optarg, "random") == 0)
          id.neighborhoodType = InputData::Random;
        else
          throw std::runtime_error("Invalid neighborhood type.");
        break;
      }
      case 'w': {
        id.printEnergyValue = true;
        break;
      }
      case 's': {
        id.saveAllFigures = true;
        break;
      }
      case 'd': {
        id.displayFlow = true;
        break;
      }
      default: {
        usage(argv);
        exit(1);
      }
    }
  }

  id.gcoFilepath = argv[optind++];
  id.outputFolder = argv[optind++];
  return id;
}

std::string resolveNeighborhoodType(InputData::NeighborhoodType nt) {
  if (nt == InputData::Morphology)
    return "morphology";
  else if (nt == InputData::Random)
    return "random";
  else
    return "unknown";
}

void writeInputData(const InputData &id, std::ostream &os) {
  os << "GrabcutObject filepath:" << id.gcoFilepath << "\n"
     << "Estimation radius:" << id.radius << "\n"
     << "Opt band:" << id.optBand << "\n"
     << "Grabcut iterations:" << id.grabcutIterations << "\n"
     << "Length penalization:" << id.alpha << "\n"
     << "Regional term:" << id.regionalTermWeight << "\n"
     << "Curvature term:" << id.curvatureTermWeight << "\n"
     << "Iterations:" << id.iterations << "\n"
     << "Neighborhood size:" << id.neighborhoodSize << "\n"
     << "Neighborhood type:" << resolveNeighborhoodType(id.neighborhoodType)
     << "\n"
     << "Save figures:" << (id.saveAllFigures ? "True" : "False") << "\n"
     << "Display flow:" << (id.displayFlow ? "True" : "False") << "\n"
     << "Print energy value:" << (id.printEnergyValue ? "True" : "False")
     << "\n"
     << "Max number of threads:" << id.nThreads << "\n"
     << "Output folder:" << id.outputFolder << "\n";
}
}  // namespace App
