cmake_minimum_required(VERSION 3.12)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")

PROJECT(ShapeFromFocus)

SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")

FILE(GLOB SOURCES src/*.cpp include/*.hpp)

FIND_PACKAGE(PCL 1.9 REQUIRED COMPONENTS common io surface)
FIND_PACKAGE(OpenCV 4.0 REQUIRED)



LINK_DIRECTORIES(${PCL_LIBRARY_DIRS})

ADD_LIBRARY(ShapeFromFocus SHARED
    src/CoarseResolutionDepthEstimation.cpp
    src/DepthEstimationGaussianInterpolation.cpp
    src/DepthReconstruction.cpp
    src/FocusMeasureOperator.cpp
    src/ModifiedLaplacian.cpp
    src/NormalizedGrayLevelVariance.cpp
    src/TenengradVariance.cpp
    src/util.cpp)

TARGET_INCLUDE_DIRECTORIES(
    ${PROJECT_NAME} PUBLIC
    ${PCL_INCLUDE_DIRS}
    src
    include
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    ${OpenCV_LIBS}
    ${PCL_COMMON_LIBRARIES}
    ${PCL_IO_LIBRARIES}
    ${PCL_SURFACE_LIBRARIES}
    )

