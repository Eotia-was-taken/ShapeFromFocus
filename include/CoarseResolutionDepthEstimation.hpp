//
//  Implementation of the coarse depth estimation reconstruction method as
//  proposed in
//  *******************************************************************
//                  Shree K. Nayar, Yasuo Nakagawa
//      Shape From Focus: An Effective Approach for Rough Surfaces
//  Proceedings., IEEE International Conference on Robotics and Automation. IEEE, 1990.
//  *******************************************************************
//
//


#ifndef CoarseResolutionDepthEstimation_hpp
#define CoarseResolutionDepthEstimation_hpp

#include "DepthReconstruction.hpp"


class CoarseResolutionDepthEstimation : public DepthReconstruction
{
    public:
        CoarseResolutionDepthEstimation( const std::vector<cv::Mat>& focusMeasures, const cv::Mat& focalLengths);
        ~CoarseResolutionDepthEstimation();
        cv::Mat reconstructDepthMap();
    private:
        std::vector<cv::Mat> focusMeasures;
        cv::Mat focalLengths;
};
#endif /* CoarseResolutionDepthEstimation_hpp */
