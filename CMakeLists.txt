cmake_minimum_required(VERSION 3.5)
project(drm_howto VERSION 1.0.0 LANGUAGES C CXX)
set(OpenCV_LIBS opencv_core opencv_video opencv_videoio opencv_imgproc opencv_imgcodecs opencv_highgui)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD 99)
if (NOT DP_ROOTFS STREQUAL "")
  include_directories(${DP_ROOTFS}/include)
  link_directories(${DP_ROOTFS}/lib)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0 -fno-inline")
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_C_FLAGS "-Wall -Werror -ggdb -O0 -fno-inline")



add_executable(test_drm drm-howto/modeset-vsync.c)
target_link_libraries(test_drm drm)

add_library(dpimshow
  drm-howto/imshow.hpp
  drm-howto/imshow.cpp
  drm-howto/modeset-vsync-imshow.c
  )
target_link_libraries(dpimshow drm)

add_executable(test_imshow
  drm-howto/test_imshow.cpp
  )

target_link_libraries(test_imshow dpimshow glog  ${OpenCV_LIBS})


add_executable(test_imfill
  drm-howto/test_imfill.cpp
  )
target_link_libraries(test_imfill glog  ${OpenCV_LIBS})
