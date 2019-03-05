//
//  DepthEstimationGaussianInterpolation.cpp
//  ShapeFromFocus
//
//  Created by Maxim Dolgich on 24.01.19.
//

#include "DepthEstimationGaussianInterpolation.hpp"

using namespace std;
using namespace cv;

DepthEstimationGaussianInterpolation::DepthEstimationGaussianInterpolation(const vector<Mat>& _focusMeasures, const Mat _focalLengths, int _k)
{
    focusMeasures = _focusMeasures;
    focalLengths = _focalLengths;
    k = _k;
}
DepthEstimationGaussianInterpolation::~DepthEstimationGaussianInterpolation()
{
    focusMeasures.clear();
    focalLengths.release();
}

float DepthEstimationGaussianInterpolation::pixelwiseDepth(int row, int col)
{
    float maxFocus = 0.f;
    int middle = 2;
    for(int measureNr = 3; measureNr < focusMeasures.size(); measureNr++)
    {
        float leftFocus = focusMeasures[measureNr-2].at<float>(row, col);
        float currentFocus = focusMeasures[measureNr-1].at<float>(row, col);
        float rightFocus = focusMeasures[measureNr].at<float>(row, col);
        if(currentFocus > maxFocus && currentFocus > leftFocus && currentFocus > rightFocus)
        {
            maxFocus = currentFocus;
            middle = measureNr - 1;
        }

    }
    return computeMean(middle, row, col);
}
Mat DepthEstimationGaussianInterpolation::reconstructDepthMap()
{
    Mat result = Mat(focusMeasures[0].rows, focusMeasures[0].cols, CV_32F);
    float startFocalLength = focalLengths.at<float>(0,0);
    for(int i = 0; i < focusMeasures[0].rows; i++)
    {

        for(int j = 0; j < focusMeasures[0].cols; j++)
        {
            result.at<float>(i,j) = pixelwiseDepth(i, j) - startFocalLength;
        }
    }
    return result;
}


float DepthEstimationGaussianInterpolation::computeDelta(const int middle)
{
    float focalLengthMiddle = focalLengths.at<float>(0, middle);
    float focalLengthLeft = focalLengths.at<float>(0, middle - 1 );
    float focalLengthRight = focalLengths.at<float>(0, middle + 1 );
    return (abs(focalLengthLeft - focalLengthMiddle) + abs(focalLengthMiddle - focalLengthRight))/2;
}


float DepthEstimationGaussianInterpolation::computeMean(const int middle, int row, int col)
{
    float delta = computeDelta(middle);
    float d = focalLengths.at<float>(0, middle+1);
    float dLeft = d - delta;
    float dRight = d + delta;
    float leftFocusMeasure = focusMeasures[middle-1].at<float>(row, col);
    float rightFocusMeasure = focusMeasures[middle+1].at<float>(row, col);
    float middleFocusMeasure = focusMeasures[middle].at<float>(row, col);
    float numerator = (log(middleFocusMeasure) - log(rightFocusMeasure)) * (d*d - dLeft*dLeft)
                    - (log(middleFocusMeasure) - log(leftFocusMeasure)) * (d*d - dRight*dRight);
    float denominator = 2 * delta * ( (log(middleFocusMeasure) - log(leftFocusMeasure)) + (log(middleFocusMeasure) - log(rightFocusMeasure)) );
    float result = (numerator*256)/(denominator*256);
    return result;
}
