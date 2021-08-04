#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
  cv::Mat img_rgb, img_gry;

  img_rgb = cv::imread(argv[1],-1);
  cv::cvtColor(img_rgb, img_gry, cv::COLOR_BGR2GRAY);

  int x = 16, y = 32;
  cv::Vec3b intensity = img_rgb.at<cv::Vec3b>(y, x);

  uchar blue = intensity[0];
  uchar green = intensity[1];
  uchar red = intensity[2];

  std::cout << "At (x,y) = (" << x << ", " << y <<
    "): (blue,green,red) = (" <<
    (unsigned int) blue <<
    ", " << (unsigned int)green << ", " <<
    (unsigned int)red << ")" << std::endl;

  std::cout << "Gray pixel there is: " <<
    (unsigned int)img_gry.at<uchar>(y,x) << std::endl;

  x /= 4; y /= 4;
  std::cout << "Pyramid2 pixel there is: " <<
    (unsigned int)img_gry.at<uchar>(y,x) << std::endl;

  img_gry.at<uchar>(x,y) = 128;

  cv::waitKey(0);
  
  return 0;
}