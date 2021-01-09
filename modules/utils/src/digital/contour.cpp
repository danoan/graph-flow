#include "graph-flow/utils/digital/contour.h"

namespace GraphFlow::Utils::Digital::Contour {

void computeBoundaryCurve(Curve& boundOut, const DigitalSet& dsIn) {
  using namespace DGtal::Z2i;

  typedef DGtal::SurfelAdjacency<KSpace::dimension> SurfelAdjacency;
  typedef DGtal::Surfaces<KSpace> Surfaces;

  typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;
  typedef DGtal::functors::SimpleThresholdForegroundPredicate<Image2D>
      ThreshPredicate;

  // Using extended domain because tracker has difficult to continue
  // when using a tight domain.
  Domain extDomain(dsIn.domain().lowerBound() - Point(1, 1),
                   dsIn.domain().upperBound() + Point(1, 1));
  KSpace KImage;

  KImage.init(extDomain.lowerBound(), extDomain.upperBound(), true);

  DGtal::Z2i::SCell imageBel = Surfaces::findABel(KImage, dsIn, 10000);

  SurfelAdjacency SAdj(true);

  std::vector<DGtal::Z2i::SCell> boundarySCells;
  Surfaces::track2DBoundary(boundarySCells, KImage, SAdj, dsIn, imageBel);
  boundOut.initFromSCellsVector(boundarySCells);
}

}  // namespace GraphFlow::Utils::Digital::Contour