#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <random>
#include <iostream>

int main(int argc, char** argv)
{
  cv::RNG rng = cv::theRNG();


  // 100 three-byte objects
  // center: 64, 192, 128
  // variance: 2, 2, 2
  cv::Mat m(100,1,CV_8UC3);
  rng.fill(m, cv::RNG::NORMAL, cv::Vec3f(64, 192, 128), cv::Vec3f(sqrt(2), sqrt(2), sqrt(2)));

  for (int i = 0; i < 5; ++i)
  {
    cv::Vec3b color = m.at<cv::Vec3b>(i,0);
    std::cout << "r: " << (int)color[0] << " ";
    std::cout << "g: " << (int)color[1] << " ";
    std::cout << "b: " << (int)color[2] << "\n";
  }

  cv::PCA(m, cv::Mat(0,0,0), cv::PCA::DATA_AS_COL, 2);
  
  return 0;
}