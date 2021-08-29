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

void randomize_image(cv::Mat& m, int w, int h)
{
  for (int i = 0; i < w; ++i)
  {
    for (int j = 0; j < h; ++j)
    {
      m.at<uchar>(i,j) = rand() % 256;
    }
  }
}

void generate_integral_image(cv::Mat& mI, cv::Mat m, int w, int h)
{
  for (int i = 0; i < w; ++i)
  {
    for (int j = 0; j < h; ++j)
    {
      int pixelValue = 0;
      for (int k = 0; k < i; ++k)
      {
        for (int l = 0; l < j; ++l)
        {
          pixelValue += (float)m.at<uchar>(k,l);
        }
      }
      mI.at<float>(i,j) = pixelValue;
    }
  }
}

int max_val(cv::Mat m, int w, int h)
{
  float maxVal = 0;
  for (int i = 0; i < w; ++i)
  {
    for (int j = 0; j < h; ++j)
    {
      maxVal = std::max(maxVal, m.at<float>(i,j));
    }
  }

  return maxVal;
}

void scale_image(cv::Mat& m, int w, int h, int maxVal)
{
  for (int i = 0; i < w; ++i)
  {
    for (int j = 0; j < h; ++j)
    {
      m.at<float>(i,j) = m.at<float>(i, j) / maxVal;
    }
  }
}

int main()
{
  int w = 100;
  int h = 200;
  cv::Mat m(w, h, CV_8UC1);
  cv::Mat mI(w, h, CV_32FC1);
  cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Integral image", cv::WINDOW_AUTOSIZE);

  randomize_image(m, w, h);

  // method 1: loop over every pixel
  generate_integral_image(mI, m, w, h);
  int maxVal = max_val(mI, w, h);
  scale_image(mI, w, h, maxVal);

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