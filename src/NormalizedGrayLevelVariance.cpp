//
//  NormalizedGrayLevelVariance.cpp
//  ShapeFromFocus
//
//  Created by Maxim Dolgich on 08.01.19.
//
#include <opencv2/highgui.hpp>
#include "NormalizedGrayLevelVariance.hpp"
using namespace cv;

NormalizedGrayLevelVariance::NormalizedGrayLevelVariance(const Mat& img)
{
    img.convertTo(floatImg, CV_32F, 1/255.);
    grayLevelMeanValue = mean(floatImg)[0];
    floatImg = floatImg - grayLevelMeanValue;
    pow(floatImg, 2, floatImg);
}
NormalizedGrayLevelVariance::~NormalizedGrayLevelVariance() {
    floatImg.release();
}
float NormalizedGrayLevelVariance::getFocusMeasure(const Mat& img, const Size& window, int row, int col)
{
    float result = 0.;
    for(int i = row - window.height/2; i < row + window.height/2; i++)
    {
        for(int j = col - window.width/2; j < col + window.width/2; j++)
        {
            int x,y;
            FocusMeasureOperator::computeIndices(x, y, i, j, window, img);
            result += floatImg.at<float>(x,y);
        }
    }

    return result/grayLevelMeanValue;
}

