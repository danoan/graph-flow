#include <opencv2/imgproc.hpp>

namespace GraphFlow::Utils::Digital::Morphology {
struct StructuringElement {
  typedef unsigned char Size;
  enum Type {
    RECT = cv::MORPH_RECT,
    CROSS = cv::MORPH_CROSS,
    CIRCLE = cv::MORPH_ELLIPSE
  };

  StructuringElement(Type type, Size size) : type(type), size(size) {}

  const Type type;
  const Size size;
};
}  // namespace GraphFlow::Utils::Digital::Morphology