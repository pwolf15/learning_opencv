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
  std::vector<cv::Point> pts = {cv::Point(2,1), cv::Point(200,1), cv::Point(2,200), cv::Point(200,200) };
  cv::fillPoly(img, pts,cv::Scalar(0,0,255));

  // line
  cv::line(img, cv::Point(150, 1), cv::Point(150, 200), cv::Scalar(255, 255, 0));

  // rectanglec
  cv::rectangle(img, cv::Rect(20, 20, 200, 200), cv::Scalar(255, 255, 255), 20);

  // polyLines
  // cv::Point 
  int npts = 4;
  cv::polylines(img, pts, true, cv::Scalar(0,0,0),2,150,0);

  cv::imshow("shapes", img);

  cv::waitKey(0);

  return 0;
}