#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main()
{

  cv::namedWindow("Typewriter", cv::WINDOW_AUTOSIZE);
  cv::Mat m(500, 500, CV_8UC1);

  for (int i = 0; i < m.rows; ++i)
  {
    for (int j = 0; j < m.cols; ++j)
    {
      m.at<uchar>(i,j) = rand() % 255;
    }
  }

  cv::imshow("Typewriter", m);
  
  cv::waitKey(0);

  return 0;
}