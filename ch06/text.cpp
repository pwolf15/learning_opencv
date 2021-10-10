#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("text", cv::WINDOW_AUTOSIZE);

  cv::Mat img = cv::imread("/home/pwolf/Downloads/garden.jpeg");
  if (img.empty())
    return -1;

  cv::Mat gray;
  cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
  cv::putText(gray, 
    "This is a garden", 
    cv::Point(10,10),
    3,
    0.25,
    cv::Scalar(255,125,255)
  );

  cv::imshow("text", gray);

  cv::waitKey(0);

  return 0;
}