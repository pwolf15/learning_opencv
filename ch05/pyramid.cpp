#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("pyramid", cv::WINDOW_AUTOSIZE);

  int width = 210, height = 210, numLevels = 10;
  cv::Mat m(height, width, CV_8UC1, cv::Scalar(0));

  for (int i = 1; i <= numLevels; ++i)
  {
    cv::Mat mask = cv::Mat::zeros(width, height, CV_8U); 
    mask(cv::Rect(i * 10, i * 10, width - (i * 10 * 2), height - (i * 10 * 2))) = 1;
    m.setTo(cv::Scalar(i * 20), mask);
  }

  cv::imshow("pyramid", m);

  cv::waitKey(0);

  return 0;
}