//
//  TenengradVariance.hpp
//  ShapeFromFocus
//
//  Implementation of the Tenengrad variance focus measure operator as proposed
//  in
//  *******************************************************************
//                  Shree K. Nayar, Yasuo Nakagawa
//      Shape From Focus: An Effective Approach for Rough Surfaces
//  Proceedings., IEEE International Conference on Robotics and Automation. IEEE, 1990.
//  *******************************************************************
//

#ifndef TenengradVariance_hpp
#define TenengradVariance_hpp
#include "FocusMeasureOperator.hpp"
class TenengradVariance: public FocusMeasureOperator
{
    public:
        //void getFocusMap(const cv:: Mat& img, const cv::Size& window, cv::Mat& depthMap);
        TenengradVariance(const cv::Mat& img);
        ~TenengradVariance();
    private:
        cv::Mat gradMagnitude;
        float gradMeanValue;
        virtual float getFocusMeasure(const cv::Mat& img, const cv::Size& window, int row, int col);
        float computeGradVarianceStep(int x, int y);
};
#endif /* TenengradVariance_hpp */
