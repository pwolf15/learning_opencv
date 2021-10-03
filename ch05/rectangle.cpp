#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("rectangle", cv::WINDOW_AUTOSIZE);

  cv::Mat m(100, 100, CV_8UC3, cv::Scalar(0,0,0));
  
  for (int i = 20; i <= 40; ++i)
  {
    for (int j = 5; j <= 20; ++j)
    {
      // m.at<cv::Vec3d> = cv::Vec(0,255,0);
      m.at<cv::Vec3b>(i,j) = cv::Vec3b(0,255,0);
    }
  }

  cv::imshow("rectangle", m);

  cv::waitKey(0);

  return 0;
}