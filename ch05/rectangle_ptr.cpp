#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("rectangle_ptr", cv::WINDOW_AUTOSIZE);

  cv::Mat m(100, 100, CV_8UC3, cv::Scalar(0,0,0));
  
  uchar* m_ptr = m.ptr();
  int numChannels = 3;
  for (int i = 20; i <= 40; ++i)
  {
    for (int j = 5; j <= 20; ++j)
    {
      int idx = i * (numChannels*100) + (numChannels*j);
      m_ptr[idx] = 0;
      m_ptr[idx+1] = 255;
      m_ptr[idx+2] = 0;
    }
  }

  cv::imshow("rectangle_ptr", m);

  cv::waitKey(0);

  return 0;
}