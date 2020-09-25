#include "bean.h"

namespace App::Bean{
DigitalSet generate(const Domain& domain,double radius, int damagePoints, int nBeans){
  using namespace DGtal::Z2i;

  Point lb = domain.lowerBound();
  Point ub = domain.upperBound();
  Point border(4*radius,4*radius);

  lb += border;
  ub -= border;

  std::random_device rd;
  std::uniform_int_distribution dX(lb[0],ub[0]);
  std::uniform_int_distribution dY(lb[1],ub[1]);

  DigitalSet outDS(domain);
  while(nBeans>0){
    DigitalSet beanDS = DIPaCUS::Shapes::bean(1.0,dX(rd),dY(rd),1.0/radius);
    DigitalSet temp(domain);
    temp.insert(beanDS.begin(),beanDS.end());

    DigitalSet rotated = App::Utils::rotate(temp);

    DigitalSet tempDS = App::Utils::disturbContour(rotated,damagePoints);
    outDS.insert(tempDS.begin(),tempDS.end());
    --nBeans;
  }

  return outDS;
}



ShapeAndImage bean(const Domain& domain,double radius,double noiseRatio,int damagePoints,int nBeans){
  DigitalSet outDS = generate(domain,radius,damagePoints,nBeans);
  return App::Utils::addNoise(outDS,App::Utils::randomNoise, noiseRatio);
}
}