#include "graph-flow/utils/display.h"

namespace GraphFlow::Utils::Display
{
void saveDigitalSetAsImage(const Domain& domain, const PointSet& ps, const std::string& outputFilepath)
{
  DigitalSet ds(domain);
  ds.insert(ps.begin(),ps.end());
  saveDigitalSetAsImage(ds,outputFilepath);
}

void saveDigitalSetAsImage(const DigitalSet& ds,const std::string& outputFilepath)
{
  const Domain& domain = ds.domain();
  const Point& lb = domain.lowerBound();
  const Point& ub = domain.upperBound();
  Point dims = ub-lb + Point(1,1);

  cv::Mat cvImgGray = cv::Mat::zeros(dims[1],dims[0],CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(cvImgGray,ds);

  cv::Mat cvImg = cv::Mat::zeros(cvImgGray.rows,cvImgGray.cols,CV_8UC3);
  cv::cvtColor(cvImgGray,cvImg,cv::COLOR_GRAY2RGB,3);

  cv::imwrite(outputFilepath,cvImgGray);
}
}