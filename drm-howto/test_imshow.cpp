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
  auto video_file_ = std::string(argv[1]);
  auto is_camera =
      video_file_.size() == 1 && video_file_[0] >= '0' && video_file_[0] <= '9';
  auto video_stream = std::unique_ptr<cv::VideoCapture>(
      is_camera ? new cv::VideoCapture(std::stoi(video_file_))
                : new cv::VideoCapture(video_file_));
  auto &cap = *video_stream.get();
  if (!cap.isOpened()) {
    LOG(ERROR) << "cannot open file " << video_file_;
    return -1;
  }
  imshow_open();
  while (true) {
    cv::Mat image;
    cap >> image;
    auto video_ended = image.empty();
    if (video_ended) {
      break;
    }
    imshow(image);
    std::this_thread::sleep_for(std::chrono::milliseconds(33));
  }
  imshow_close();
  return 0;
}
