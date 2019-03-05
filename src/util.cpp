//
//  util.cpp
//  ShapeFromFocus
//
//  Created by Maxim Dolgich on 26.02.19.
//

#include "util.hpp"

using namespace cv;
using namespace pcl;
using namespace std;

void triangulate(const string& fName,const Mat& textureImage, Mat& depthMap)
{
    PointCloud<PointXYZRGB>::Ptr cloud (new PointCloud<PointXYZRGB>);
    Mat img;
    resize(textureImage,img, Size(800,600));
    PointCloud<PointXYZRGB>::Ptr cloud_organized(new PointCloud<PointXYZRGB>);
    cloud_organized->width = img.cols;
    cloud_organized->height = img.rows;
    cloud_organized->points.resize (cloud_organized->width * cloud_organized->height);
    int npoints= 0;
    for(int i = 0; i < depthMap.rows; i++)
    {
        for(int j = 0; j < depthMap.cols; j++)
        {
            // COORDINATES
            cloud_organized->points[npoints].x = static_cast<float> (j);
            cloud_organized->points[npoints].y = static_cast<float> (i);
            cloud_organized->points[npoints].z = static_cast<float> (depthMap.at<float>(i,j)*5.f);

            // COLOUR
            Point3_<uchar> colour = img.at<Point3_<uchar> >(i,j);
            cloud_organized->points[npoints].r = colour.z;
            cloud_organized->points[npoints].g = colour.y;
            cloud_organized->points[npoints].b = colour.x;
            npoints++;
        }

    }
    int nan_idx = cloud_organized->width*cloud_organized->height - 2*cloud_organized->width + 1;
    cloud_organized->points[nan_idx].x = numeric_limits<float>::quiet_NaN ();
    cloud_organized->points[nan_idx].y = numeric_limits<float>::quiet_NaN ();
    cloud_organized->points[nan_idx].z = numeric_limits<float>::quiet_NaN ();
    PolygonMesh triangles;
    OrganizedFastMesh<PointXYZRGB> ofm;
    // Set parameters
    ofm.setInputCloud(cloud_organized);
    ofm.setTrianglePixelSize(1);
    ofm.setTriangulationType(OrganizedFastMesh<PointXYZRGB>::TRIANGLE_ADAPTIVE_CUT);

    // Reconstruct
    ofm.reconstruct(triangles);
    pcl::io::savePLYFile(fName, triangles);

}
