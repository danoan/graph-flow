#include "utils/data-term.h"

namespace App::Utils::DataTerm{

double diffDataValue(const DigitalSet& diffSet,const App::Image::DataDistribution& DD,bool fg){
  const cv::Mat& img = DD.segResultImg;

  const App::Image::CVMatDistribution* distr;
  if(fg) distr = DD.fgDistr;
  else distr = DD.bgDistr;

  double v=0;
  for(auto p:diffSet)
  {
    int prow=img.rows-p[1]-1;
    int pcol=p[0];

    v+=-log( (*distr)(prow,pcol) );
  }

  return v;
}

double regionValue(double& fgv, double& bgv,const DigitalSet& ds, const App::Image::CVMatDistribution& fgDistr, const App::Image::CVMatDistribution& bgDistr)
{
  const cv::Mat& img = fgDistr.img;
  bgv=0;
  fgv=0;
  for(auto p:ds.domain())
  {
    int prow=img.rows-p[1]-1;
    int pcol=p[0];

    if(ds(p))
    {
      fgv+=-log( (fgDistr)(prow,pcol) );
    }else
    {
      bgv+=-log( (bgDistr)(prow,pcol) );
    }
  }

  return (fgv+bgv);
}

cv::Vec3d avgColor(const DigitalSet& dsMask, const cv::Mat& cvImg){
  cv::Vec3d avgC(0,0,0);
  for(auto p:dsMask){
    int c = p[0];
    int r = cvImg.rows-1 - p[1];

//    cv::Vec3d color = cvImg.at<cv::Vec3b>(r,c)/255.0;
    cv::Vec3d color = cvImg.at<cv::Vec3b>(r,c);
    avgC+=color;
  }
  return avgC/( (double) dsMask.size() );
}

double chanvese_region_term(const DigitalSet& dsMask,const cv::Mat& cvImg,const cv::Vec3d& avgColor){
  double s=0;
  for(auto p:dsMask){
    int c = p[0];
    int r = cvImg.rows-1 - p[1];

//    cv::Vec3d color = cvImg.at<cv::Vec3b>(r,c)/255.0;
    cv::Vec3d color = cvImg.at<cv::Vec3b>(r,c);
    color-=avgColor;
    s+= pow(color[0],2)+pow(color[1],2)+pow(color[2],2);
  }

  return s;
}

double chanvese(const InputData& id,const DigitalSet& ds, const App::Image::DataDistribution& DD){
  std::vector<DIPaCUS::Misc::ConnectedComponent> vcc;
  DIPaCUS::Misc::getConnectedComponents(vcc,ds);

  double s=0;
//  for(auto cc:vcc){
//    DigitalSet ccDS(ds.domain());
//    ccDS.insert(cc.begin(),cc.end());
//
//    cv::Vec3d avgC = avgColor(ccDS,DD.gco.inputImage);
//    s+=chanvese_region_term(ccDS,DD.gco.inputImage,avgC);
//  }

  cv::Vec3d avgF = avgColor(ds,DD.gco.inputImage);
  s+=chanvese_region_term(ds,DD.gco.inputImage,avgF);


  DigitalSet background(ds.domain());
  background.assignFromComplement(ds);
  cv::Vec3d avgB = avgColor(background,DD.gco.inputImage);
  s+=chanvese_region_term(background,DD.gco.inputImage,avgB);

  return s;
}

}