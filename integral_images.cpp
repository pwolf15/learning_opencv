#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <chrono>
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
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      m.at<uchar>(i, j) = rand() % 256;
    }
  }
}

void generate_integral_image(cv::Mat& mI, cv::Mat m, int w, int h)
{
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      int pixelValue = 0;
      for (int k = 0; k <= i; ++k)
      {
        for (int l = 0; l <= j; ++l)
        {
          pixelValue += (float)m.at<uchar>(k, l);
        }
      }
      mI.at<float>(i, j) = pixelValue;
    }
  }
}

void generate_integral_image2(cv::Mat& mI, cv::Mat m, int w, int h)
{
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      int pixelValue = 0;
      if (i == 0)
      {
        if (j != 0)
        {
          // add left pixel
          pixelValue += mI.at<float>(i, j - 1);
        }
      }
      else if (j == 0)
      {
        if (i != 0)
        {
          // add top pixel
          pixelValue += mI.at<float>(i - 1, j);
        }
      }
      else
      {
        pixelValue += mI.at<float>(i, j - 1);
        pixelValue += mI.at<float>(i - 1, j);
        pixelValue -= mI.at<float>(i - 1, j - 1);
      }

      pixelValue += (float)m.at<uchar>(i, j);
      mI.at<float>(i, j) = pixelValue;
    }
  }
}

int max_val(cv::Mat m, int w, int h)
{
  float maxVal = 0;
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      maxVal = std::max(maxVal, m.at<float>(i, j));
    }
  }

  return maxVal;
}

void scale_image(cv::Mat& m, int w, int h, int maxVal)
{
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      m.at<float>(i, j) = m.at<float>(i, j) / maxVal;
    }
  }
}

int sum_pixels(cv::Mat& mI, int r0, int c0, int r1, int c1)
{
  // sum = mI[r1][c1] - mI[r0][c1] - mI[r1][c0] + m1[r0][c0]
  return 0;
}

int main()
{
  int w = 200;
  int h = 100;
  cv::Mat m(h, w, CV_8UC1);
  cv::Mat mI(h, w, CV_32FC1);
  cv::Mat mI2(h, w, CV_32FC1);
  cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Integral image", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Integral image2", cv::WINDOW_AUTOSIZE);

  randomize_image(m, w, h);

  // method 1: loop over every pixel

  auto start = std::chrono::steady_clock::now();

  generate_integral_image(mI, m, w, h);

  auto finish = std::chrono::steady_clock::now();
  double elapsed_seconds =
      std::chrono::duration_cast<std::chrono::duration<double>>(finish - start)
          .count();

  std::cout << "Method 1: " << elapsed_seconds << std::endl;

  // method 2: efficient a (left) + b (top) - c (top left for double count)
  
  start = std::chrono::steady_clock::now();

  generate_integral_image2(mI2, m, w, h);

  finish = std::chrono::steady_clock::now();
  elapsed_seconds =
      std::chrono::duration_cast<std::chrono::duration<double>>(finish - start)
          .count();

  std::cout << "Method 2: " << elapsed_seconds << std::endl;

  // check equal
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      assert(mI.at<float>(i, j) == mI2.at<float>(i, j));
    }
  }

  int maxVal = max_val(mI, w, h);
  scale_image(mI, w, h, maxVal);
  maxVal = max_val(mI2, w, h);
  scale_image(mI2, w, h, maxVal);

  while (true)
  {
    cv::imshow("Image", m);
    cv::imshow("Integral image", mI);
    cv::imshow("Integral image2", mI2);

    char c = (char)cv::waitKey(10);
    if (c == KeyCodes::ESCAPE)
    {
      break;
    }
  }
  return 0;
}