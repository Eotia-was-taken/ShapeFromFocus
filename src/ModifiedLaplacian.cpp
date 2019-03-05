//
//  ModifiedLaplacian.cpp
//  ShapeFromFocus
//
//  Created by Maxim Dolgich on 29.11.18.
//
#include "ModifiedLaplacian.hpp"
using namespace cv;

ModifiedLaplacian::ModifiedLaplacian(const Mat& img)
{
    Mat tmp = Mat(img.rows, img.cols, CV_32F);
    img.convertTo(tmp, CV_32F, 1/255.);
    modifiedLaplacian =  Mat(img.rows, img.cols, CV_32F);
    computeModifiedLaplacian(tmp, modifiedLaplacian);
}
ModifiedLaplacian::~ModifiedLaplacian() {
    modifiedLaplacian.release();
}

float ModifiedLaplacian::getFocusMeasure(const Mat& img, const Size& window, int row, int col)
{
    float result = 0.;
    for(int i = row - window.height/2; i < row + window.height/2; i++)
    {
        for(int j = col - window.width/2; j < col + window.width/2; j++)
        {

            int x,y;
            FocusMeasureOperator::computeIndices(x, y, i, j, window, modifiedLaplacian);
            result += modifiedLaplacian.at<float>(x,y);

        }
    }

    return result;
}
void ModifiedLaplacian::computeModifiedLaplacian(const Mat& img, Mat& outputImg)
{
    Matx13f Lx;
    Matx31f Ly;
    Mat deltaX = Mat::zeros(img.rows, img.cols, CV_32F);
    Mat deltaY = Mat::zeros(img.rows, img.cols, CV_32F);
    Lx(0,0) = -1;
    Lx(0,1) = 2;
    Lx(0,2) = -1;
    transpose(Lx, Ly);
    filter2D(img, deltaX, -1, Lx);
    filter2D(img, deltaY, -1, Ly);
    outputImg = abs(deltaX) + abs(deltaY);
}
