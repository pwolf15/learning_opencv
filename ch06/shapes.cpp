#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("shapes", cv::WINDOW_AUTOSIZE);

  cv::Mat img = cv::imread("/home/pwolf/Downloads/garden.jpeg");
  if (img.empty())
    return -1;

  // circle
  cv::circle(img, cv::Point(30,30), 10, cv::Scalar(255,100,100), 5);

  // ellipse
  cv::ellipse(img, cv::Point(50,50), cv::Size(100, 100), 360, 0, 360, cv::Scalar(0, 0, 0),2);

  // fillConvexPoly
  cv::Point points[4] = { cv::Point(10,10), cv::Point(50,10), cv::Point(50, 10), cv::Point(50,50) };
  cv::fillConvexPoly(img, points, 4, cv::Scalar(255, 255, 255));

  // fillPoly

  // line

  // rectangle

  // polyLines

  cv::imshow("shapes", img);

  cv::waitKey(0);

  return 0;
}