#include "graph-flow/utils/digital/shapes.h"

namespace GraphFlow::Utils::Digital::Shapes {
template <typename TShape>
DigitalSet Shapes::digitizeShape(const TShape &shape, double h) {
  using namespace DGtal::Z2i;
  
  BOOST_CONCEPT_ASSERT((DGtal::concepts::CEuclideanBoundedShape<TShape>));

  DGtal::GaussDigitizer<Space, TShape> gd;
  gd.attach(shape);
  gd.init(shape.getLowerBound(), shape.getUpperBound(), h);

  Domain domain(gd.getDomain().lowerBound() - Point(1, 1),
                gd.getDomain().upperBound() + Point(1, 1));
  DigitalSet output(domain);
  DGtal::Shapes<Domain>::digitalShaper(output, gd);

  return output;
}
}  // namespace GraphFlow::Utils::Digital::Shapes