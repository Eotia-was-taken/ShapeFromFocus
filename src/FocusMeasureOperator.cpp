//
//  FocusMeasureOperator.cpp
//  ShapeFromFocus
//
//  Created by Maxim Dolgich on 29.11.18.
//

#include "FocusMeasureOperator.hpp"

using namespace cv;

void FocusMeasureOperator::getFocusMap(const Mat& img, const Size& window, Mat& outputImg)
{

    for(int i = 0; i < img.rows; i++)
    {
        for(int j = 0; j < img.cols; j++)
        {
            outputImg.at<float>(i,j) = getFocusMeasure(img, window, i, j);
        }
    }
}


// Computes the indices for the sliding block window, performing reflective border padding.
void FocusMeasureOperator::computeIndices(int &x, int &y, int i, int j, const Size& window, const Mat& img)
{
    if(i < 0)
    {
        x = i + window.height;
    }
    else if(i > img.rows-1)
    {
        x = i - window.height;
    }
    else
    {
        x = i;
    }
    if(j < 0)
    {
        y = j + window.height;
    }
    else if(j > img.cols-1)
    {
        y = j - window.height;
    }
    else
    {
        y = j;
    }
}
