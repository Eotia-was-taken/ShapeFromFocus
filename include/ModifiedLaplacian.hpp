//  *******************************************************************
//                  Shree K. Nayar, Yasuo Nakagawa
//      Shape From Focus: An Effective Approach for Rough Surfaces
//  Proceedings., IEEE International Conference on Robotics and Automation. IEEE, 1990.
//  *******************************************************************
//

#ifndef ModifiedLaplacian_hpp
#define ModifiedLaplacian_hpp
#include "FocusMeasureOperator.hpp"
class ModifiedLaplacian: public FocusMeasureOperator
{
    public:
        ModifiedLaplacian(const cv::Mat& img);
        ~ModifiedLaplacian();
    private:
        cv::Mat modifiedLaplacian;
        void computeModifiedLaplacian(const cv::Mat& img, cv::Mat& modifiedLaplacian);
        virtual float getFocusMeasure(const cv::Mat& img, const cv::Size& window, int row, int col);

};

#endif /* ModifiedLaplacian_hpp */
