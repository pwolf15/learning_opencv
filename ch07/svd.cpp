#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <random>
#include <iostream>

int main(int argc, char** argv)
{
  cv::Mat a = (cv::Mat_<double>(3, 2) << 1.0, 1.0, 0.0, 1.0, -1.0, 1.0);

  std::cout << a << std::endl;

  cv::Mat s, v, u;
  cv::SVD svd(a);
  svd.compute(a, s, u, v);

  std::cout << s << std::endl;
  std::cout << u << std::endl;
  std::cout << v << std::endl;

  return 0;
}