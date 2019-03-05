//
//  DepthEstimationGaussianInterpolation.hpp
//  ShapeFromFocus
//
//  Here the "Depth Estimation by Gaussian Interpolation" proposed in
//  *****************************************************************
//                  Shree K. Nayar, Yasuo Nakagawa
//      Shape From Focus: An Effective Approach for Rough Surfaces
//  Proceedings., IEEE International Conference on Robotics and Automation. IEEE, 1990.
//  *****************************************************************
//  is implemented

//  Created by Maxim Dolgich on 24.01.19.
//

#ifndef DepthEstimationGaussianInterpolation_hpp
#define DepthEstimationGaussianInterpolation_hpp

#include "DepthReconstruction.hpp"

class DepthEstimationGaussianInterpolation: DepthReconstruction
{
    public:
        // While the original definition uses a number of measurement of k = 3 for the Gaussian interpolation
        // in order to save on computation and assuming a more accurate depth estimation, the parameter can be
        // freely defined here.
        DepthEstimationGaussianInterpolation(const std::vector<cv::Mat>& focusMeasures, const cv::Mat focalLengths, int k);
        ~DepthEstimationGaussianInterpolation();
        cv::Mat reconstructDepthMap();
    private:
        std::vector<cv::Mat> focusMeasures;
        cv::Mat focalLengths;
        int k;
        float computeDelta(const int middle);
        float computeMean(const int middle, int row, int col);
        float pixelwiseDepth(int row, int col);
};

#endif /* DepthEstimationGaussianInterpolation_hpp */
