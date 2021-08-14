#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

#include "keys.hpp"

void drawSquare(cv::Mat& m, int r, int c, int w, int h, int keyIdx)
{
  for (int i = r; i < r + h; ++i)
  {
    for (int j = c; j < c + w; ++j)
    {
      m.at<uchar>(i,j) = numbers[keyIdx][(j-c)+w*(i-r)] * 255;
    }
  }
}

int main()
{

  cv::namedWindow("Typewriter", cv::WINDOW_AUTOSIZE);
  cv::Mat m(500, 500, CV_8UC1);

  // for (int i = 0; i < m.rows; ++i)
  // {
  //   for (int j = 0; j < m.cols; ++j)
  //   {
  //     m.at<uchar>(i,j) = rand() % 255;
  //   }
  // }

  int w = 10;
  int h = 20;
  int rowIdx = 0;
  int colIdx = 0;

  while (true)
  {
    cv::imshow("Typewriter", m);

    char c = (char) cv::waitKey(10);
    if (c >= 48 && c <= 57)
    {
      std::cout << "Draw square" << std::endl;
      drawSquare(m, rowIdx, colIdx, w, h, c - 48);
      colIdx += w;
      
      if (colIdx == 500)
      {
        rowIdx += h;
        colIdx = 0;
      }
    }
    if (c == 27)
      break;
  }

  return 0;
}