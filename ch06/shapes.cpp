#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("shapes", cv::WINDOW_AUTOSIZE);

  cv::Mat img = cv::imread("/home/pwolf/Downloads/garden.jpeg");
  if (img.empty())
    return -1;

  cv::imshow("shapes", img);

  cv::waitKey(0);

  return 0;
}