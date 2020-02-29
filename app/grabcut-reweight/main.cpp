#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>
#include <BTools/utils/model/GrabCutObject.h>

#include <graph-flow/utils/display.h>
#include <graph-flow/utils/string.h>
#include <opencv/cv.hpp>
#include <graph-flow/utils/digital.h>

#include "input/InputData.h"
#include "input/InputReader.h"

using namespace DGtal::Z2i;

typedef BTools::Utils::GrabCutIO::GrabCutObject GrabCutObject;


void grabCut( cv::InputArray _img, cv::InputOutputArray _mask, cv::Rect rect,
              cv::InputOutputArray _bgdModel, cv::InputOutputArray _fgdModel,
              const DGtal::Z2i::DigitalSet& shape, const DGtal::Z2i::DigitalSet& optRegion, double radius, double kweight,
              int iterCount, int mode );

auto maskPair(const GrabCutObject& gco)
{
    cv::Mat fgMask=cv::Mat::zeros(gco.grabCutMask.size(),gco.grabCutMask.type());
    cv::compare(gco.grabCutMask,
                cv::GC_FGD,
                fgMask,
                cv::CMP_EQ);

    cv::Mat bgMask=cv::Mat::zeros(gco.grabCutMask.size(),gco.grabCutMask.type());
    cv::compare(gco.grabCutMask,
                cv::GC_BGD,
                bgMask,
                cv::CMP_EQ);

    return std::make_pair(fgMask,bgMask);
}

DigitalSet prepareShape(const cv::Mat& inputImage)
{
    Domain tempDomain(Point(0,0),
                      Point(inputImage.cols-1,
                            inputImage.rows-1)
    );
    DigitalSet tempDS(tempDomain);

    //Convert inputImg to 1-channel grayscale image.
    cv::Mat grayscale(inputImage.size(),
                      inputImage.type());
    if(inputImage.type()!=CV_8UC1)
        cv::cvtColor(inputImage,grayscale,cv::COLOR_RGB2GRAY,1);
    else
        grayscale = inputImage;

    DIPaCUS::Representation::CVMatToDigitalSet(tempDS,
                                               grayscale,
                                               1);

    return tempDS;
}

DigitalSet prepareShape(const GrabCutObject& gco)
{
    cv::Mat bgModel;
    cv::Mat fgModel;


    auto fgBg = maskPair(gco);
    auto fgMask = fgBg.first;
    cv::Mat gcOutMask=gco.grabCutMask;


    grabCut(gco.inputImage,gcOutMask,cv::Rect(),bgModel,fgModel,100,cv::GC_INIT_WITH_MASK);

    cv::Mat segMask= cv::Mat::zeros(gco.inputImage.size(),CV_8UC1);
    cv::compare(gcOutMask,
                cv::GC_PR_FGD,
                segMask,
                cv::CMP_EQ);

    segMask.setTo(255,fgMask);

    cv::Mat segResultImg = cv::Mat::zeros(gco.inputImage.size(),CV_8UC3);
    gco.inputImage.copyTo(segResultImg,segMask);

    cv::imshow("GrabCut",
               segResultImg);
    cv::waitKey(0);

    return prepareShape(segResultImg);
}

int main(int argc, char* argv[]) {
    InputData id = readInput(argc, argv);

    boost::filesystem::create_directories(id.outputFolder);

    GrabCutObject gco = BTools::Utils::GrabCutIO::read(id.gcoFilepath);

    Domain imgDomain(Point(0, 0),
                     Point(gco.inputImage.cols - 1,
                           gco.inputImage.rows - 1));

    DigitalSet shape = prepareShape(gco);


    cv::namedWindow("GrabCut");

    for(int i=0;i<id.iterations;++i)
    {

        Point lb,ub;
        shape.computeBoundingBox(lb,ub);
        Point optBandBorder(id.optBand+1,id.optBand+1);
        Domain reducedDomain(lb-2*optBandBorder,ub+2*optBandBorder);

        auto dtInterior = GraphFlow::Utils::Digital::interiorDistanceTransform(reducedDomain,shape);
        auto dtExterior = GraphFlow::Utils::Digital::exteriorDistanceTransform(reducedDomain,shape);


        DigitalSet _optRegion = GraphFlow::Utils::Digital::level(dtInterior,id.optBand,0);
        _optRegion += GraphFlow::Utils::Digital::level(dtExterior,id.optBand,0);
        DigitalSet optRegion(shape.domain());
        for(auto p:_optRegion) if(shape.domain().isInside(p)) optRegion.insert(p);






        cv::Mat bgModel;
        cv::Mat fgModel;


        auto fgBg = maskPair(gco);
        auto fgMask = fgBg.first;
        cv::Mat gcOutMask=gco.grabCutMask;


        grabCut(gco.inputImage,gcOutMask,cv::Rect(),bgModel,fgModel,shape,optRegion,id.radius,id.curvatureTermWeight,1,cv::GC_INIT_WITH_MASK);

        cv::Mat segMask= cv::Mat::zeros(gco.inputImage.size(),CV_8UC1);
        cv::compare(gcOutMask,
                    cv::GC_PR_FGD,
                    segMask,
                    cv::CMP_EQ);

        segMask.setTo(255,fgMask);

        cv::Mat segResultImg = cv::Mat::zeros(gco.inputImage.size(),CV_8UC3);
        gco.inputImage.copyTo(segResultImg,segMask);

        cv::imshow("GrabCut",
                   segResultImg);
        cv::waitKey(200);

        shape.clear();
        shape = prepareShape(segResultImg);

    }


    return 0;
}