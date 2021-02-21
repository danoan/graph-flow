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

void extractAll2DSCellContoursFromMask(
    std::vector<std::vector<SCell> >& aVectSCellContour2D,
    const KSpace& aKSpace,
    const DGtal::SurfelAdjacency<KSpace::dimension>& aSurfelAdj,
    const DigitalSet& mask, const DigitalSet& pp) {
  using namespace DGtal::Z2i;

  std::set<SCell> candidateBels;
  Point incrList[2] = {Point(1, 0), Point(0, 1)};
  auto it = mask.begin();
  while (it != mask.end()) {
    auto p = *it;
    bool in_here = pp(p);
    int k = -1;
    for (auto incr : incrList) {
      ++k;
      auto np = p + incr;

      if (!mask(np)) continue;
      bool in_further = pp(np);
      if (in_here != in_further) {
        Cell pCell =
            aKSpace.uSpel(p);  // a unica coisa eh como eu recupero uma cell.
        candidateBels.insert(
            aKSpace.sIncident(aKSpace.signs(pCell, in_here), k, true));
        break;
      }
    }
    ++it;
  }
  while (!candidateBels.empty()) {
    std::vector<SCell> aContour;
    SCell aLinel = *(candidateBels.begin());

    DGtal::Surfaces<KSpace>::track2DBoundary(aContour, aKSpace, aSurfelAdj, pp,
                                             aLinel);
    aVectSCellContour2D.push_back(aContour);
    // removing cells from boundary;
    for (unsigned int i = 0; i < aContour.size(); i++) {
      SCell sc = aContour.at(i);
      candidateBels.erase(sc);
    }
  }
}

}  // namespace GraphFlow::Utils::Digital::Contour