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

  // RNG arrays

  // uniform
  cv::Mat m1(20,1,CV_32F);
  rng.fill(m1, cv::RNG::UNIFORM, 0.0, 1.0);
  std::cout << "20 floating-point from 0.0 to 1.0 (uniform)" << std::endl;
  for (int i = 0; i < m1.rows; ++i)
  {
    std::cout << m1.at<float>(i,0) << "\n";
  }

  // Gaussian
  cv::Mat m2(20,1,CV_32F);
  rng.fill(m2, cv::RNG::NORMAL, 0.0, 1.0);
  std::cout << "20 floating point from 0.0 to 1.0 (gaussian)" << std::endl;
  for (int i = 0; i < m2.rows; ++i)
  {
    std::cout << m2.at<float>(i,0) << "\n";
  } 

  return 0;
}