#ifndef GRAPH_FLOW_APP_GRAPH_SEG_GRAPHSEGINPUT_H
#define GRAPH_FLOW_APP_GRAPH_SEG_GRAPHSEGINPUT_H

#include <DGtal/helpers/StdDefs.h>
#include "input/InputData.h"
#include "model/image/DataDistribution.h"

namespace App {
struct GraphSegInput {
  typedef DGtal::Z2i::DigitalSet DigitalSet;

  GraphSegInput(const InputData &id, const DigitalSet &inputDS, const App::Image::DataDistribution &dataDistribution) :
      inputData(id),
      inputDS(inputDS),
      dataDistribution(dataDistribution) {}

  const InputData &inputData;
  const DigitalSet &inputDS;
  const App::Image::DataDistribution &dataDistribution;
};
}
#endif //GRAPH_FLOW_APP_GRAPH_SEG_GRAPHSEGINPUT_H
