

#ifndef DepthReconstruction_hpp
#define DepthReconstruction_hpp

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class DepthReconstruction
{
    public:
        virtual cv::Mat reconstructDepthMap() = 0;
};

#endif /* DepthReconstruction_hpp */
