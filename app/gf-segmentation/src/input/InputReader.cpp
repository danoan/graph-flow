#include "input/InputReader.h"

#include "input/InputData.h"

namespace App {
void usage(char *argv[]) {
  std::cerr
      << "Usage: " << argv[0]
      << " GrabcutObjectFilepath OutputFolder \n"
         "[-R Balance coefficient disk radius (default: 6)]\n"
         "[-r Validation disk radius (default: 6)]\n"
         "[-G Data term penalization at candidate selection  (default:0.5)]\n"
         "[-K Curvature term penalization at candidate selection "
         "(default:1.0)]\n"
         "[-g Data term penalization at validation  (default:0.5)]\n"
         "[-k Curvature term penalization at validation (default:1.0)]\n"
         "[-a Length term penalization at validation (default:0.01)]\n"
         "[-O Optimization band (default:2)]\n"
         "[-N neighborhood size (default:2)]\n"
         "[-H neighborhood type (morphology, random) (default:morphology)]\n"
         "[-j Grabcut iterations (default:1)]\n"
         "[-i Number of iterations (default: 10)]\n"
         "[-t Tolerance. Stop if change between iterations is smaller than "
         "tolerance (>=0) (default:-1, never stop)]\n"
         "[-n Maximum number of threads (default:4)]\n"
         "[-v Validation weight mode (automatic-correction-length-data, automatic-correction-length, automatic-correction-data, manual) (default: automatic-correction-length-data)\n"
         "[-w print energy value]\n"
         "[-s save figures]\n"
         "[-d display flow]"
      << std::endl;
}

InputData readInput(int argc, char *argv[]) {
  InputData id;

  int opt;
  while ((opt = getopt(argc, argv, "R:r:G:K:g:k:a:O:N:H:j:i:t:n:v:wsd")) != -1) {
    switch (opt) {
      case 'R': {
        id.radius = std::atof(optarg);
        break;
      }
      case 'r': {
        id.vradius = std::atof(optarg);
        break;
      }
      case 'G': {
        id.dataWeightCandidate = std::atof(optarg);
        break;
      }
      case 'K': {
        id.curvatureWeightCandidate = std::atof(optarg);
        break;
      }
      case 'g': {
        id.dataWeightValidation = std::atof(optarg);
        break;
      }
      case 'k': {
        id.curvatureWeightValidation = std::atof(optarg);
        break;
      }
      case 'a': {
        id.alpha = std::atof(optarg);
        break;
      }
      case 'O': {
        id.optBand = std::atoi(optarg);
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
      case 'j': {
        id.grabcutIterations = std::atoi(optarg);
        break;
      }
      case 'i': {
        id.iterations = std::atoi(optarg);
        break;
      }
      case 't': {
        id.tolerance = std::atof(optarg);
        break;
      }
      case 'n': {
        id.nThreads = std::atoi(optarg);
        break;
      }
      case 'v': {
        if( strcmp(optarg,"automatic-correction-length-data")==0 )
          id.validationWeightMode = InputData::AutomaticCorrectionLengthData;
        else if( strcmp(optarg,"automatic-correction-length")==0 )
          id.validationWeightMode = InputData::AutomaticCorrectionLength;
        else if( strcmp(optarg,"automatic-correction-data")==0 )
          id.validationWeightMode = InputData::AutomaticCorrectionData;
        else if( strcmp(optarg,"manual")==0 )
          id.validationWeightMode = InputData::Manual;
        else throw std::runtime_error("Validation weight setting type not recognized.\n");
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

  if (optind>=argc-1){
    std::cerr << "Please specify a Grabcut object (the output of the grabcut application) and an output folder.\n";
    exit(0);
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

std::string resolveValidationWeightMode(InputData::ValidationWeightMode vm) {
  if (vm == InputData::AutomaticCorrectionLengthData)
    return "automatic-correction-length-data";
  else if (vm == InputData::AutomaticCorrectionLength)
    return "automatic-correection-length";
  else if (vm == InputData::AutomaticCorrectionData)
    return "automatic-correection-data";
  else if (vm == InputData::Manual)
    return "manual";
  else
    return "unknown";
}

void writeInputData(const InputData &id, std::ostream &os) {
  os << "GrabcutObject filepath:" << id.gcoFilepath << "\n"
     << "Balance coefficient disk radius:" << id.radius << "\n"
     << "Validation disk radius:" << id.vradius << "\n"
     << "Data weight candidate:" << id.dataWeightCandidate << "\n"
     << "Curvature weight candidate:" << id.curvatureWeightCandidate << "\n"
     << "Data weight validation:" << id.dataWeightValidation << "\n"
     << "Curvature weight validation:" << id.curvatureWeightValidation << "\n"
     << "Length penalization:" << id.alpha << "\n"
     << "Opt band:" << id.optBand << "\n"
     << "Neighborhood size:" << id.neighborhoodSize << "\n"
     << "Neighborhood type:" << resolveNeighborhoodType(id.neighborhoodType)
     << "Grabcut iterations:" << id.grabcutIterations << "\n"
     << "Iterations:" << id.iterations << "\n"
     << "Validation weight mode:" << resolveValidationWeightMode(id.validationWeightMode) << "\n"
     << "\n"
     << "Save figures:" << (id.saveAllFigures ? "True" : "False") << "\n"
     << "Display flow:" << (id.displayFlow ? "True" : "False") << "\n"
     << "Print energy value:" << (id.printEnergyValue ? "True" : "False")
     << "\n"
     << "Max number of threads:" << id.nThreads << "\n"
     << "Grabcut filepath:" << id.gcoFilepath << "\n"
     << "Output folder:" << id.outputFolder << "\n";
}
}  // namespace App
