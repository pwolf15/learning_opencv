#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

#include "keys.hpp"

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

enum MatOption
{
  GRAYSCALE = 0,
  COLOR = 1
};

struct TypewriterState
{
  std::vector<std::vector<int>>
      grid;  // values of each spot in grid  std::vector<std::vector<int>>
             // vals(500 / 20);
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

void drawNumber(cv::Mat& m,
                int r,
                int c,
                int w,
                int h,
                int keyIdx,
                MatOption option = MatOption::GRAYSCALE)
{
  if (option == MatOption::GRAYSCALE)
  {
    for (int i = r * h; i < (r * h) + h; ++i)
    {
      for (int j = (c * w); j < (c * w) + w; ++j)
      {
        m.at<uchar>(i, j) =
            numbers[keyIdx][(j - (c * w)) + w * (i - (r * h))] * 255;
      }
    }
  }
  else if (option == MatOption::COLOR)
  {
    cv::Vec3b color = {
      (uchar)(rand() % 255),
      (uchar)(rand() % 255),
      (uchar)(rand() % 255),
    };
    for (int i = r * h; i < (r * h) + h; ++i)
    {
      for (int j = (c * w); j < (c * w) + w; ++j)
      {
        m.at<cv::Vec3b>(i, j) = {
            (uchar)((numbers[keyIdx][(j - (c * w)) + w * (i - (r * h))] != 0) * (color[0])),
            (uchar)((numbers[keyIdx][(j - (c * w)) + w * (i - (r * h))] != 0) * (color[1])),
            (uchar)((numbers[keyIdx][(j - (c * w)) + w * (i - (r * h))] != 0) * (color[2]))
        };
      }
    }
  }
}

void drawCursor(cv::Mat& m,
                int r,
                int c,
                int w,
                int h,
                bool toggle,
                MatOption option = MatOption::GRAYSCALE)
{
  if (option == MatOption::GRAYSCALE)
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
  else if (option == MatOption::COLOR)
  {
    for (int i = r * h; i < (r * h) + h; ++i)
    {
      for (int j = (c * w); j < (c * w) + w; ++j)
      {
        if (toggle)
        {
          m.at<cv::Vec3b>(i, j) = {
              cursor[(j - (c * w)) + w * (i - (r * h))] * 255,
              cursor[(j - (c * w)) + w * (i - (r * h))] * 255,
              cursor[(j - (c * w)) + w * (i - (r * h))] * 255};
        }
        else
        {
          m.at<cv::Vec3b>(i, j) = {0, 0, 0};
        }
      }
    }
  }
}

void drawBlack(cv::Mat& m,
               int r,
               int c,
               int w,
               int h,
               MatOption option = MatOption::GRAYSCALE)
{
  if (option == MatOption::GRAYSCALE)
  {
    for (int i = r * h; i < (r * h) + h; ++i)
    {
      for (int j = (c * w); j < (c * w) + w; ++j)
      {
        m.at<uchar>(i, j) = 0;
      }
    }
  }
  else if (option == MatOption::COLOR)
  {
    for (int i = r * h; i < (r * h) + h; ++i)
    {
      for (int j = (c * w); j < (c * w) + w; ++j)
      {
        m.at<cv::Vec3b>(i, j) = {0, 0, 0};
      }
    }
  }
}

int main()
{
  cv::namedWindow("Typewriter", cv::WINDOW_AUTOSIZE);
  const int windowWidth = 500;
  const int windowHeight = 500;
  int rowIdx = 0;
  int colIdx = 0;

  cv::Mat m(windowWidth, windowHeight, CV_8UC1);
  cv::Mat m1(windowWidth, windowHeight, CV_8UC3);

  TypewriterState twState;
  const int w = twState.charWidth = 10;
  const int h = twState.charHeight = 20;
  int numRows = twState.numRows = windowHeight / h;
  int numCols = twState.numCols = windowWidth / w;

  for (size_t i = 0; i < numRows; ++i)
  {
    std::vector<int> cols;
    twState.grid.push_back(cols);
    for (size_t j = 0; j < numCols; ++j)
    {
      twState.grid[i].push_back(-1);  // null value
    }
  }

  int cursorCounter = 0;
  bool toggleCursor = true;
  bool canType = true;
  MatOption option = MatOption::GRAYSCALE;
  auto restoreSquare = [&]()
  {
    if (canType)
    {
      drawCursor(m, twState.curRow, twState.curCol, w, h, false);
      if (twState.grid[twState.curRow][twState.curCol] != -1)
      {
        drawNumber(m, twState.curRow, twState.curCol, w, h,
                   twState.grid[twState.curRow][twState.curCol]);
      }
    }
  };

  while (true)
  {
    if (option == MatOption::GRAYSCALE)
    {
      cv::imshow("Typewriter", m);
    }
    else
    {
      cv::imshow("Typewriter", m1);
    }

    char c = (char)cv::waitKey(10);
    if (c == KeyCodes::ESCAPE)
    {
      break;
    }
    else if (c == KeyCodes::BACKSPACE)  // backspace
    {
      if (canType)
      {
        if (option == MatOption::GRAYSCALE)
        {
          drawCursor(m, twState.curRow, twState.curCol, w, h, false, option);
        }
        else 
        {
           drawCursor(m1, twState.curRow, twState.curCol, w, h, false, option);
        }
      }

      canType = twState.decrementCol();
      std::cout << twState.curCol << std::endl;

      if (canType)
      {
        if (option == MatOption::GRAYSCALE)
        {
          drawBlack(m, twState.curRow, twState.curCol, w, h, option);
        }
        else 
        {
           drawBlack(m1, twState.curRow, twState.curCol, w, h, option);
        }
        twState.grid[twState.curRow][twState.curCol] = -1;
      }
    }
    else if (c >= KeyCodes::ZERO && c <= KeyCodes::NINE && canType)  // number
    {
      int numIdx = c - KeyCodes::ZERO;
      if (option == MatOption::GRAYSCALE)
      {
        drawNumber(m, twState.curRow, twState.curCol, w, h, numIdx, option);
      }
      else 
      {
        drawNumber(m1, twState.curRow, twState.curCol, w, h, numIdx, option);
      }
      twState.grid[twState.curRow][twState.curCol] = numIdx;
      canType = twState.advanceCol();
    }
    else if (c == KeyCodes::CARRIAGE_RETURN)  // carriage return
    {
      if (canType)
      {
        if (option == MatOption::GRAYSCALE)
        {
          drawCursor(m, twState.curRow, twState.curCol, w, h, false, option);
        }
        else 
        {
          drawCursor(m1, twState.curRow, twState.curCol, w, h, false, option);
        }
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
    else if (c == KeyCodes::K)
    {
      std::cout << "k, " << option << std::endl;
      if (option == MatOption::GRAYSCALE)
      {
        option = MatOption::COLOR;
        for (size_t i = 0; i < twState.numRows; ++i)
        {
          for (size_t j = 0; j < twState.numCols; ++j)
          {
            if (twState.grid[i][j] != -1)
            {
              drawNumber(m1, i, j, w, h,
                         twState.grid[i][j], option);
            }
            else
            {
              drawBlack(m1, i, j, w, h, option);
            }
          }
        }
      }
      else if (option == MatOption::COLOR)
      {
        option = MatOption::GRAYSCALE;
        for (size_t i = 0; i < twState.numRows; ++i)
        {
          for (size_t j = 0; j < twState.numCols; ++j)
          {
            if (twState.grid[i][j] != -1)
            {
              drawNumber(m, i, j, w, h,
                         twState.grid[i][j], option);
            }
            else
            {
              drawBlack(m, i, j, w, h, option);
            }
          }
        }
      }
    }

    if (canType)
    {
      if (twState.grid[twState.curRow][twState.curCol] != -1)
      {
        if (toggleCursor)
        {
          if (option == MatOption::GRAYSCALE)
          {
            drawCursor(m, twState.curRow, twState.curCol, w, h, toggleCursor,
                                option);
          }
          else 
          {
            drawCursor(m1, twState.curRow, twState.curCol, w, h, toggleCursor,
                                option);
          }
        }
        else
        {

          if (option == MatOption::GRAYSCALE)
          {
            drawNumber(m, twState.curRow, twState.curCol, w, h,
                                twState.grid[twState.curRow][twState.curCol], option);
          }
          else 
          {
            drawNumber(m1, twState.curRow, twState.curCol, w, h,
                                twState.grid[twState.curRow][twState.curCol], option);
          }
        }
      }
      else
      {
        if (option == MatOption::GRAYSCALE)
        {
          drawCursor(m, twState.curRow, twState.curCol, w, h, toggleCursor,
            option);
        }
        else 
        {
          drawCursor(m1, twState.curRow, twState.curCol, w, h, toggleCursor,
                    option);
        }
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