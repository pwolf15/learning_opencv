#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
  cv::Mat img1, img2;

  cv::namedWindow("Example 2-6-in", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Example 2-6-out", cv::WINDOW_AUTOSIZE);

  img1 = cv::imread(argv[1],-1);

  cv::imshow("Example 2-6-in", img1);

  cv::pyrDown(img1,img2);
  
  cv::imshow("Example 2-6-out", img2);

  cv::waitKey(0);
  
  return 0;
}