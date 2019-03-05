

#ifndef util_hpp
#define util_hpp


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


#include <pcl/point_types.h>
#include <pcl/surface/organized_fast_mesh.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>

// Performs a trivial triangulation of the provided depth map and assigns a colour value
// to the vertices based on the provided image "textureImage". The 3D model is saved as
// a PLY file as a file with name fName.
void triangulate(const std::string& fName, const cv::Mat& textureImage, cv::Mat& depthMap);;

#endif /* util_hpp */
