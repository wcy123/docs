#include "./imshow.hpp"
#include <glog/logging.h>
extern "C" int modeset_init();
extern "C" int modeset_exit(int fd);
extern "C" void* modeset_get_fb();
extern "C" int modeset_get_fb_width();
extern "C" int modeset_get_fb_height();
extern "C" int modeset_get_fb_stride();
extern "C" void modeset_update(int fd);
static int fd = 0;
void imshow_open() {
  fd = modeset_init();
}
void imshow_close() {
  modeset_exit(fd);
}

void imshow(const cv::Mat & image) {
  //
  auto data = modeset_get_fb();
  auto fb_size = cv::Size(modeset_get_fb_width(), modeset_get_fb_height());
  auto fb = cv::Mat(fb_size, CV_8UC3, data, modeset_get_fb_stride());
  auto image_size = cv::Size(std::min(fb_size.width, image.size().width),
                             std::min(fb_size.height, image.size().height));
  auto rect = cv::Rect(cv::Point(0, 0), image_size);
  image(rect).copyTo(fb(rect));
  if (0)
    LOG(INFO) << "fb_size = " << fb_size << "rect " << rect << " "  //
              << "image.size() " << image.size() << " "             //
              << "fb.size() " << fb.size() << " "                   //
              << std::endl;
  modeset_update(fd);
}
