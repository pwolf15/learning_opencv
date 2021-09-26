#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("circle", cv::WINDOW_AUTOSIZE);

  cv::Mat m(100, 100, CV_8UC3, cv::Scalar(0,0,0));
  cv::circle(m, cv::Point(50,50), 10, cv::Scalar(255, 255, 255));

  cv::imshow("circle", m);

  cv::waitKey(0);

  return 0;
}