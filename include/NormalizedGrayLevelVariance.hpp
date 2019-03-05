//  Implementation of the normalized gray-level variance focus measure operator as proposed
//  in
//  *******************************************************************
//                  Shree K. Nayar, Yasuo Nakagawa
//      Shape From Focus: An Effective Approach for Rough Surfaces
//  Proceedings., IEEE International Conference on Robotics and Automation. IEEE, 1990.
//  *******************************************************************
//

#ifndef NormalizedGrayLevelVariance_hpp
#define NormalizedGrayLevelVariance_hpp

#include "FocusMeasureOperator.hpp"
class NormalizedGrayLevelVariance: public FocusMeasureOperator
{
public:
    NormalizedGrayLevelVariance(const cv::Mat& img);
    ~NormalizedGrayLevelVariance();
private:
    float grayLevelMeanValue;
    cv::Mat floatImg;
    virtual float getFocusMeasure(const cv::Mat& img, const cv::Size& window, int row, int col);
};

#endif /* NormalizedGrayLevelVariance_hpp */
