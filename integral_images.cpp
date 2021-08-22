#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

enum KeyCodes
{
  BACKSPACE = 8,
  CARRIAGE_RETURN = 13,
  ESCAPE = 27,
  ZERO = 48,
  NINE = KeyCodes::ZERO + 9,
  LEFT = 81,
  UP = 82,
  RIGHT = 83,
  DOWN = 84,
  K = 107,
};

int main()
{
  cv::Mat m(100, 200, CV_8UC1);
  cv::Mat mI(100, 200, CV_32FC1);
  cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Integral image", cv::WINDOW_AUTOSIZE);

  for (int i = 0; i < 100; ++i)
  {
    for (int j = 0; j < 200; ++j)
    {
      m.at<uchar>(i,j) = rand() % 255;
    }
  }

  for (int i = 0; i < 100; ++i)
  {
    for (int j = 0; j < 200; ++j)
    {
      int pixelValue = 0;
      for (int k = 0; k < i; ++k)
      {
        for (int l = 0; l < j; ++l)
        {
          pixelValue += (float)m.at<uchar>(k,l);
        }
      }

      std::cout << pixelValue << std::endl;
      mI.at<float>(i,j) = pixelValue;
    }
  }

  while(true)
  {
    cv::imshow("Image", m);
    cv::imshow("Integral image", mI);

    char c = (char)cv::waitKey(10);
    if (c == KeyCodes::ESCAPE)
    {
      break;
    }
  }
  return 0;
}