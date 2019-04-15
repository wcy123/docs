#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <glog/logging.h>
#include "./imshow.hpp"
#include <thread>
using namespace std;


int main(int argc, char *argv[])
{
  auto image = cv::imread(argv[1]);
  if (image.empty()) {
    cerr << "cannot load " << argv[1] << endl;
    abort();
  }
  auto c = cv::Mat(cv::Size{1024,768}, CV_8UC3);
  auto rect = cv::Rect{cv::Point{0,0}, cv::Size{100,100}};
  image(rect).copyTo(c(rect));
  cv::imshow("tset", c);
  cv::waitKey(0);
  return 0;
}
