#include "utils/data-term.h"

namespace App::Utils::DataTerm{

cv::Vec3d avgColor(const DigitalSet& dsMask, const cv::Mat& cvImg){
  cv::Vec3d avgC(0,0,0);
  for(auto p:dsMask){
    int c = p[0];
    int r = cvImg.rows-1 - p[1];

    cv::Vec3d color = cvImg.at<cv::Vec3b>(r,c)/255.0;
    avgC+=color;
  }
  return avgC/( (double) dsMask.size() );
}

double chanvese_region_term(const DigitalSet& dsMask,const cv::Mat& cvImg,const cv::Vec3d& avgColor){
  double s=0;
  for(auto p:dsMask){
    int c = p[0];
    int r = cvImg.rows-1 - p[1];

    cv::Vec3d color = cvImg.at<cv::Vec3b>(r,c)/255.0;
    color-=avgColor;
    s+= pow(color[0],2)+pow(color[1],2)+pow(color[2],2);
  }

  return s;
}

double chanvese(const InputData& id,const DigitalSet& ds, const cv::Mat& cvImgIn){
  std::vector<DIPaCUS::Misc::ConnectedComponent> vcc;
  DIPaCUS::Misc::getConnectedComponents(vcc,ds);

  double s=0;
  cv::Vec3d avgF = avgColor(ds,cvImgIn);
  s+=chanvese_region_term(ds,cvImgIn,avgF);


  DigitalSet background(ds.domain());
  background.assignFromComplement(ds);
  cv::Vec3d avgB = avgColor(background,cvImgIn);
  s+=chanvese_region_term(background,cvImgIn,avgB);

  return s;
}

}