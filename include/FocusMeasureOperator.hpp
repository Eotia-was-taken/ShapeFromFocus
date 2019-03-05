

#ifndef FocusMeasureOperator_hpp
#define FocusMeasureOperator_hpp

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class FocusMeasureOperator
{
    public:
        void getFocusMap(const cv:: Mat& img, const cv::Size& window, cv::Mat& depthMap);
        void computeIndices(int &x, int &y, int i, int j, const cv::Size& window, const cv::Mat& img);
    private:
        virtual float getFocusMeasure(const cv::Mat& img, const cv::Size& window, int row, int col) = 0;
};

#endif /* FocusMeasureOperator_hpp */
