#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
  cv::Mat m = cv::Mat::eye(10, 10, CV_32FC1);

  std::cout << "Element (3,3) is " << m.at<float>(3,3) << "\n";

  cv::Mat m2 = cv::Mat::eye(10,10, CV_32FC2);

  std::cout << "Element (3,3) is (" << m2.at<cv::Vec2f>(3,3)[0] << "," << m2.at<cv::Vec2f>(3,3)[1] << ")" << std::endl;

  cv::Mat m3 = cv::Mat::eye(10,10,cv::DataType<cv::Complexf>::generic_type);

  std::cout << "Element (3,3) is (" << m3.at<cv::Complexf>(3,3).re << "," << m3.at<cv::Complexf>(3,3).im << ")" << std::endl;

  int sz[3] = { 4, 4, 4 };
  cv::Mat m4(3, sz, CV_32FC3);
  cv::randu(m4, -1.0f, 1.0f);

  float max = 0.0f, len2 = 0.0f;

  auto it = m4.begin<cv::Vec3f>();
  while (it != m4.end<cv::Vec3f>())
  {
    len2 = (*it)[0]*(*it)[0] + (*it)[1]*(*it)[1] + (*it)[2]*(*it)[2];
    if (len2 > max) max = len2;
    it++;
  }

  std::cout << "Max: " << max << std::endl;

  return 0;
}