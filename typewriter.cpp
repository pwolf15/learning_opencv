#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

#include "keys.hpp"

void drawNumber(cv::Mat& m, int r, int c, int w, int h, int keyIdx)
{
  for (int i = r * h; i < (r * h) + h; ++i)
  {
    for (int j = (c * w); j < (c * w) + w; ++j)
    {
      m.at<uchar>(i, j) = numbers[keyIdx][(j - (c * w)) + w * (i - (r * h))] * 255;
    }
  }
}

void drawCursor(cv::Mat& m, int r, int c, int w, int h, bool toggle)
{
  for (int i = r * h; i < (r * h) + h; ++i)
  {
    for (int j = (c * w); j < (c * w) + w; ++j)
    {
      if (toggle)
      {
        m.at<uchar>(i, j) = cursor[(j - (c * w)) + w * (i - (r * h))] * 255;
      }
      else
      {
        m.at<uchar>(i, j) = 0;
      }
    }
  }
}

void drawBlack(cv::Mat& m, int r, int c, int w, int h)
{
  for (int i = r * h; i < (r * h) + h; ++i)
  {
    for (int j = (c * w); j < (c * w) + w; ++j)
    {
      m.at<uchar>(i, j) = 0;
    }
  }
}

void drawSquareCustom(cv::Mat& m, int r, int c, int w, int h, int keyIdx)
{
  cv::Vec3b color = {(uchar)(rand() % 255), (uchar)(rand() % 255),
                     (uchar)(rand() % 255)};

  for (int i = r; i < r + h; ++i)
  {
    for (int j = c; j < c + w; ++j)
    {
      m.at<cv::Vec3b>(i, j) = numbers[keyIdx][(j - c) + w * (i - r)] * color;
    }
  }
}

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

struct TypewriterState
{
  std::vector<std::vector<int>> grid; // values of each spot in grid  std::vector<std::vector<int>> vals(500 / 20);
  int curRow = 0;
  int curCol = 0;
  int numRows = 0;
  int numCols = 0;
  int charWidth = 0;
  int charHeight = 0;

  bool advanceCol()
  {
    ++curCol;

    if (curCol >= numCols)
    {
      curCol = numCols;
      return false;
    }

    return curRow >= 0 && curRow < numRows;
  }

  bool advanceRow()
  {
    ++curRow;
    if (curRow >= numRows)
    {
      curRow = numRows;
      return false;
    }

    return curCol >= 0 && curCol < numCols;
  }

  bool decrementCol()
  {
    if (curCol == 0)
    {
      // skip
    }
    else
    {
      --curCol;
    }

    return curRow >= 0 && curRow < numRows;
  }

  bool decrementRow()
  {
    if (curRow == 0)
    {
      // skip
    }
    else
    {
      --curRow;
    }

    return curCol >= 0 && curCol < numCols;
  }
};

int main()
{
  cv::namedWindow("Typewriter", cv::WINDOW_AUTOSIZE);
  const int windowWidth = 500;
  const int windowHeight = 500;
  int rowIdx = 0;
  int colIdx = 0;

  cv::Mat m(windowWidth, windowHeight, CV_8UC1);

  TypewriterState twState;
  const int w = twState.charWidth =  10;
  const int h = twState.charHeight = 20;
  int numRows = twState.numRows = windowHeight / h;
  int numCols = twState.numCols = windowWidth / w;

  for (size_t i = 0; i < numRows; ++i)
  {
    std::vector<int> cols;
    twState.grid.push_back(cols);
    for (size_t j = 0; j < numCols; ++j)
    {
      twState.grid[i].push_back(-1); // null value
    }
  }

  int cursorCounter = 0;
  bool toggleCursor = true;
  bool canType = true;
  auto restoreSquare = [&]() {
    if (canType)
    {
      drawCursor(m, twState.curRow, twState.curCol, w, h, false);
      if (twState.grid[twState.curRow][twState.curCol] != -1)
      {
          drawNumber(m , twState.curRow, twState.curCol, w, h, twState.grid[twState.curRow][twState.curCol]);
      }
    }
  };

  while (true)
  {
    cv::imshow("Typewriter", m);

    char c = (char)cv::waitKey(10);
    if (c == KeyCodes::ESCAPE)
    {
      break;
    }
    else if (c == KeyCodes::BACKSPACE)  // backspace
    {
      if (canType)
      {
        drawCursor(m, twState.curRow, twState.curCol, w, h, false);
      }
      
      canType = twState.decrementCol();
      std::cout << twState.curCol << std::endl;

      if (canType)
      {
        drawBlack(m, twState.curRow, twState.curCol, w, h);
        twState.grid[twState.curRow][twState.curCol] = -1;
      }
    }
    // else if (colIdx >= windowWidth || rowIdx >= windowHeight)
    // {
    //   continue;
    // }
    else if (c >= KeyCodes::ZERO && c <= KeyCodes::NINE && canType)  // number
    {
      int numIdx = c - KeyCodes::ZERO;
      drawNumber(m, twState.curRow, twState.curCol, w, h, numIdx);
      twState.grid[twState.curRow][twState.curCol] = numIdx;
      canType = twState.advanceCol();
    }
    else if (c == KeyCodes::CARRIAGE_RETURN)  // carriage return
    {
      if (canType)
      {
        drawCursor(m, twState.curRow, twState.curCol, w, h, false);
      }
      canType = twState.advanceRow();
    }
    else if (c == KeyCodes::LEFT)  // l
    {
      restoreSquare();
      canType = twState.decrementCol();
    }
    else if (c == KeyCodes::UP)  // u
    {
      restoreSquare();
      canType = twState.decrementRow();
    }
    else if (c == KeyCodes::RIGHT)  // r
    {
      restoreSquare();
      canType = twState.advanceCol();
    }
    else if (c == KeyCodes::DOWN)  // d
    {
      restoreSquare();
      canType = twState.advanceRow();
    }
    // else if (c == KeyCodes::K)
    // {
    //   std::cout << "k" << std::endl;
    //   cv::Mat m1(windowWidth, windowHeight, CV_8UC3);
    //   for (int i = 0; i < windowHeight / h; ++i)
    //   {
    //     for (int j = 0; j < windowWidth / w; ++j)
    //     {
    //       drawSquareCustom(m1, i * h, j * w, w, h, vals[i][j]);
    //     }
    //   }
    //   m = m1;
    // }

    if (canType)
    {
      if (twState.grid[twState.curRow][twState.curCol] != -1)
      {
        if (toggleCursor)
        {
          drawCursor(m, twState.curRow, twState.curCol, w, h, toggleCursor);
        }
        else
        {
          drawNumber(m , twState.curRow, twState.curCol, w, h, twState.grid[twState.curRow][twState.curCol]);
        }
      }
      else
      {
        drawCursor(m, twState.curRow, twState.curCol, w, h, toggleCursor);
      }

      if (cursorCounter == 30)
      {
        std::cout << twState.curRow << "," << twState.curCol << std::endl;
        cursorCounter = 0;
        toggleCursor = !toggleCursor;
      }

      cursorCounter++;
    }
  }

  return 0;
}