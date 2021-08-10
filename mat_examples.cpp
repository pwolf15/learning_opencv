#include <opencv2/core.hpp>
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
  return 0;
}