#include "utils.h"

void writeEnergyData(const GraphSegIteration& gsIteration,std::ostream& os)
{
    using namespace GraphFlow::Utils;
    int colLength=20;
    
    os << String::fixedStrLength(colLength,gsIteration.iteration)
    << String::fixedStrLength(colLength,gsIteration.value) << "\n";
}

void writeEnergyData(std::ostream& os)
{
    using namespace GraphFlow::Utils;
    int colLength=20;
    os << String::fixedStrLength(colLength,"#Iteration")
    << String::fixedStrLength(colLength,"Energy value") << "\n";
}

double evaluateEnergy(const InputData& id, const DigitalSet& ds)
{
    using namespace GraphFlow::Utils;

    double s=0;
    if(id.energy==InputData::EnergyType::Elastica) s+=Energy::elastica(ds,id.radius,id.h,id.alpha);
    else if(id.energy==InputData::EnergyType::SElastica) s+=Energy::sElastica(ds,id.radius,id.h,id.alpha);
    else throw std::runtime_error("Unrecognized energy!");

    return s;
}

DigitalSet getPixelMask(const std::string& pixelMaskFilepath, const Domain& domain, const Point& shift)
{
    DigitalSet _dsOutput(domain);
    if(pixelMaskFilepath=="") return _dsOutput;

    DIPaCUS::Representation::imageAsDigitalSet(_dsOutput,pixelMaskFilepath,1);
    
    DigitalSet dsOutput(domain);
    for(auto p:_dsOutput) dsOutput.insert(p+shift);
    return dsOutput;
}

void initGMMs( const cv::Mat& img, const cv::Mat& mask, GMM& bgdGMM, GMM& fgdGMM )
{
    const int kMeansItCount = 10;
    const int kMeansType = cv::KMEANS_PP_CENTERS;

    cv::Mat bgdLabels, fgdLabels;
    std::vector<cv::Vec3f> bgdSamples, fgdSamples;
    cv::Point p;
    for( p.y = 0; p.y < img.rows; p.y++ )
    {
        for( p.x = 0; p.x < img.cols; p.x++ )
        {
            if( mask.at<uchar>(p) == cv::GC_BGD || mask.at<uchar>(p) == cv::GC_PR_BGD )
                bgdSamples.push_back( (cv::Vec3f)img.at<cv::Vec3b>(p) );
            else // GC_FGD | GC_PR_FGD
                fgdSamples.push_back( (cv::Vec3f)img.at<cv::Vec3b>(p) );
        }
    }

    cv::Mat _bgdSamples( (int)bgdSamples.size(), 3, CV_32FC1, &bgdSamples[0][0] );
    cv::kmeans( _bgdSamples, GMM::componentsCount, bgdLabels,
                cv::TermCriteria( cv::TermCriteria::MAX_ITER, kMeansItCount, 0.0), 0, kMeansType );

    cv::Mat _fgdSamples( (int)fgdSamples.size(), 3, CV_32FC1, &fgdSamples[0][0] );
    cv::kmeans( _fgdSamples, GMM::componentsCount, fgdLabels,
                cv::TermCriteria( cv::TermCriteria::MAX_ITER, kMeansItCount, 0.0), 0, kMeansType );

    bgdGMM.initLearning();
    for( int i = 0; i < (int)bgdSamples.size(); i++ )
        bgdGMM.addSample( bgdLabels.at<int>(i,0), bgdSamples[i] );
    bgdGMM.endLearning();

    fgdGMM.initLearning();
    for( int i = 0; i < (int)fgdSamples.size(); i++ )
        fgdGMM.addSample( fgdLabels.at<int>(i,0), fgdSamples[i] );
    fgdGMM.endLearning();
}
