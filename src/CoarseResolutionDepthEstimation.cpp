//
//  CoarseResolutionDepthEstimation.cpp
//  ShapeFromFocus
//
//  Created by Maxim Dolgich on 10.01.19.
//

#include "CoarseResolutionDepthEstimation.hpp"

using namespace std;
using namespace cv;

CoarseResolutionDepthEstimation::CoarseResolutionDepthEstimation(const vector<Mat>& _focusMeasures, const Mat& _focalLengths)
{
    focusMeasures = vector<Mat>(_focusMeasures);
    focalLengths = _focalLengths;
}

CoarseResolutionDepthEstimation::~CoarseResolutionDepthEstimation()
{
    focusMeasures.clear();
}

Mat CoarseResolutionDepthEstimation::reconstructDepthMap()
{
    float focalLengthStart = focalLengths.at<float>(0, 0);
    Mat result = Mat(focusMeasures[0].rows, focusMeasures[0].cols, CV_32F);
    for(int i = 0; i < focusMeasures[0].rows; i++)
    {
        int maxFocusImageNr = 0;
        float maxFocus = 0.;
        for(int j = 0; j < focusMeasures[0].cols; j++)
        {
            for(int measureNr = 0; measureNr < focusMeasures.size(); measureNr++)
            {
                float currentFocus = focusMeasures[measureNr].at<float>(i,j);
                if(currentFocus > maxFocus)
                {
                    maxFocusImageNr = measureNr;
                    maxFocus = currentFocus;
                }
            }
            result.at<float>(i,j) = focalLengths.at<float>(0, maxFocusImageNr-1)- focalLengthStart;
            maxFocusImageNr = 0.;
            maxFocus = 0;
        }
    }
    return result;
}
