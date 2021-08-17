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

void drawBlack(cv::Mat& m, int r, int c, int w, int h)
{
  for (int i = r; i < r + h; ++i)
  {
    for (int j = c; j < c + w; ++j)
    {
      m.at<uchar>(i,j) = 0;
    }
  }
}

enum KeyCodes
{
  ZERO = 48,
  NINE = KeyCodes::ZERO + 9,
  LEFT = 81,
  UP = 82,
  RIGHT = 83,
  DOWN = 84
};

int main()
{

  cv::namedWindow("Typewriter", cv::WINDOW_AUTOSIZE);
  const int windowWidth = 500;
  const int windowHeight = 500;
  const int w = 10;
  const int h = 20;
  int rowIdx = 0;
  int colIdx = 0;

  cv::Mat m(windowWidth, windowHeight, CV_8UC1);

  // for (int i = 0; i < m.rows; ++i)
  // {
  //   for (int j = 0; j < m.cols; ++j)
  //   {
  //     m.at<uchar>(i,j) = rand() % 255;
  //   }
  // }



  while (true)
  {
    cv::imshow("Typewriter", m);

    char c = (char) cv::waitKey(10);
    if (c == 27)
    {
      break;
    }
    else if (colIdx >= windowWidth || rowIdx >= windowHeight)
    {
      continue;
    }
    else if (c >= KeyCodes::ZERO && c <= KeyCodes::NINE) // number
    {
      std::cout << "Draw square" << std::endl;
      drawSquare(m, rowIdx, colIdx, w, h, c - KeyCodes::ZERO);
      colIdx += w;
      
      if (colIdx == windowWidth)
      {
        rowIdx += h;
        colIdx = 0;
      }
    }
    else if (c == 13) // carriage return
    {
      rowIdx += h;
      colIdx = 0;
    }
    else if (c == 8) // backspace
    {
      drawBlack(m, rowIdx, colIdx, w, h);
      if (colIdx == 0)
      {
        if (rowIdx != 0)
        {
          rowIdx -= h;
        }
      }
      else 
      {
        colIdx -= w;
      }
    }
    else if (c == KeyCodes::LEFT) // l
    {
      if (colIdx == 0)
      {
        if (rowIdx != 0)
        {
          rowIdx -= h;
        }
      }
      else
      {
        colIdx -= w;
      }
    }
    else if (c == KeyCodes::UP) // u
    {
      if (rowIdx != 0)
      {
        rowIdx -= h;
      }
    }
    else if (c == KeyCodes::RIGHT) // r
    {
      if (colIdx == windowWidth)
      {
        colIdx = 0;
        rowIdx += h; 
      }
      else 
      {
        colIdx += w;
      }
      
    }
    else if (c == KeyCodes::DOWN) // d
    {
      if (rowIdx != windowHeight)
      {
        rowIdx += h;
      }
    }

  }

  return 0;
}