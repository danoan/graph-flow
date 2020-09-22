#include "graph-flow/utils/ring.h"

namespace GraphFlow::Utils::Shapes{
RingShape::RingShape(const double x, const double y, const double smallR, const double bigR){
  smallCircle = circle( Point(x,y),smallR);
  bigCircle = circle( Point(x,y),bigR);

  lb = Point(x-bigR,y-bigR);
  ub = Point(x+bigR,y+bigR);
}

RingShape::CirclePredicate RingShape::circle(const RealPoint& center, const double radius)
{
  return [center,radius](const RealPoint& p){ return ( pow(center[0] - p[0],2) + pow(center[1]-p[1],2) - pow(radius,2) ) <= 0; };
}

DGtal::Orientation RingShape::orientation(const RealPoint& aPoint) const
{
  if( !smallCircle(aPoint) && bigCircle(aPoint) ) return DGtal::Orientation::INSIDE;
  else return DGtal::Orientation::OUTSIDE;
}

DGtal::Z2i::DigitalSet ringMask(const DGtal::Z2i::Domain& domain,double smallR, double bigR,int border){
  using namespace DGtal::Z2i;

  DigitalSet ds(domain);
  ds.clear();

  Point lb,ub;
  lb = domain.lowerBound();
  ub = domain.upperBound();

  int minX = lb[0]+bigR;
  int minY = lb[1]+bigR;

  int maxX = ub[0]-bigR;
  int maxY = ub[1]-bigR;

  for(int x=minX;x<maxX;x+=border){
    for(int y=minY;y<maxY;y+=border){
      RingShape ring(x,y,smallR,bigR);
      ds += DIPaCUS::Shapes::digitizeShape(ring,1.0);
    }
  }

  return ds;

}

}