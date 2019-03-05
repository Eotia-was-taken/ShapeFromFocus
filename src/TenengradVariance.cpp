//
//  TenengradVariance.cpp
//  ShapeFromFocus
//
//  Created by Maxim Dolgich on 08.01.19.
//

#include "TenengradVariance.hpp"
#include <opencv2/highgui.hpp>

using  namespace cv;


TenengradVariance::TenengradVariance(const Mat& img)
{
    double scale = 1/32.0; // normalization wrt Scharr Mask
    double delta = 0;
    Mat tmp = Mat(img.rows, img.cols, CV_32F);
    Mat gradX, gradY, squaredGradientX, squaredGradientY;
    img.convertTo(tmp, CV_32F, 1/255.);
    Scharr(tmp, gradX, -1,1,0, scale, delta, BORDER_REFLECT);
    Scharr(tmp, gradY, -1,0,1, scale, delta, BORDER_REFLECT);
    pow(gradX, 2, squaredGradientX);
    pow(gradY, 2, squaredGradientY);
    sqrt(squaredGradientX + squaredGradientY, gradMagnitude);
    gradMeanValue = mean(gradMagnitude)[0];
    squaredGradientX.release();
    squaredGradientY.release();
}
TenengradVariance::~TenengradVariance()
{
    gradMagnitude.release();
}

float TenengradVariance::getFocusMeasure(const Mat& img, const Size& window, int row, int col)
{
    float result = 0.;
    for(int i = row - window.height/2; i < row + window.height/2; i++)
    {
        for(int j = col - window.width/2; j < col + window.width/2; j++)
        {
            int x,y;
            FocusMeasureOperator::computeIndices(x, y, i, j, window, img);
            result += computeGradVarianceStep(x, y);
        }
    }
    return result;
}

float TenengradVariance::computeGradVarianceStep(int x, int y)
{
    const float result = (gradMagnitude.at<float>(x,y) - gradMeanValue);
    return result * result;
}

