#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <random>
#include <iostream>

int main(int argc, char** argv)
{
  cv::Mat m(3,1, CV_32F);
  cv::RNG rng(0);
  rng.fill(m, cv::RNG::UNIFORM, 0.0, 1.0);

  for (int i = 0; i < m.rows; ++i)
  {
    std::cout << m.at<float>(i,0) << std::endl;
  }

  return 0;
}