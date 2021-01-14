#include "graph-flow/utils/digital/shapes.h"

namespace GraphFlow::Utils::Digital::Shapes {
DigitalSet NGon(double h, double x0, double y0, double radius, int sides,
                double rotation) {
  typedef DGtal::Z2i::Space Space;
  DGtal::NGon2D<Space> ngon(x0, y0, radius, sides, rotation);
  return digitizeShape(ngon, h);
}

DigitalSet square(double h, double x0, double y0, double radius,
                  double rotation) {
  return NGon(h, x0, y0, radius, 4, rotation);
}

DigitalSet triangle(double h, double x0, double y0, double radius,
                    double rotation) {
  return NGon(h, x0, y0, radius, 3, rotation);
}

DigitalSet ball(double h, double x0, double y0, double radius) {
  typedef DGtal::Z2i::Space Space;
  DGtal::Ball2D<Space> ball(x0, y0, radius);
  return digitizeShape(ball, h);
}

DigitalSet flower(double h, double x0, double y0, double radius,
                  double smallRadius, int k, double rotation) {
  typedef DGtal::Z2i::Space Space;
  DGtal::AccFlower2D<Space> flower(x0, y0, radius, smallRadius, k, rotation);
  return digitizeShape(flower, h);
}

DigitalSet ellipse(double h, double x0, double y0, double largerRadius,
                   double smallerRadius, double rotation) {
  typedef DGtal::Z2i::Space Space;
  DGtal::Ellipse2D<Space> ellipse(x0, y0, largerRadius, smallerRadius,
                                  rotation);
  return digitizeShape(ellipse, h);
}

DigitalSet bean(double h, double x, double y, double k) {
  BeanShape bean(x, y, k);
  return digitizeShape(bean, h);
}

DigitalSet resolveShape(const std::string& shape, double gridStep,
                        double radius) {
  using namespace DGtal::Z2i;

  if (shape == "triangle")
    return triangle(gridStep, 0, 0, radius);
  else if (shape == "square")
    return square(gridStep, 0, 0, radius);
  else if (shape == "pentagon")
    return NGon(gridStep, 0, 0, radius, 5);
  else if (shape == "heptagon")
    return NGon(gridStep, 0, 0, radius, 7);
  else if (shape == "ball")
    return ball(gridStep, 0, 0, radius);
  else if (shape == "flower")
    return flower(gridStep, 0, 0, radius, radius / 2.0, 2);
  else if (shape == "ellipse")
    return ellipse(gridStep, 0, 0, radius, radius / 2);
  else if (shape == "bean")
    return bean(gridStep, 0, 0, 0.1);
  else {
    cv::Mat img = cv::imread(shape, CV_8UC1);
    Domain domain(DGtal::Z2i::Point(0, 0),
                  DGtal::Z2i::Point(img.cols - 1, img.rows - 1));
    DigitalSet ds(domain);
    GraphFlow::Utils::Digital::Representation::CVMatToDigitalSet(ds, img, 1);
    return ds;
  }
}
}  // namespace GraphFlow::Utils::Digital::Shapes