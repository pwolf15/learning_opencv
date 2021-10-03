#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int drawLevel(cv::Mat& m, int idx)
{
  int offset = idx * 10;
  for (int i = offset; i < 210 - offset; ++i)
  {
    for (int j = offset; j < 210 - offset; ++j)
    {
      m.at<uchar>(i,j) = idx * 20;
    }
  }
}

int main(int argc, char** argv)
{
  cv::namedWindow("pyramid", cv::WINDOW_AUTOSIZE);

  cv::Mat m(210, 210, CV_8UC1, cv::Scalar(0));

  for (int i = 1; i <= 10; ++i)
  {
    drawLevel(m, i);
  }

  cv::imshow("pyramid", m);

  cv::waitKey(0);

  return 0;
}