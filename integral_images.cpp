#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <chrono>
#include <iostream>

void MatType( cv::Mat inputMat )
{
    int inttype = inputMat.type();

    std::string r, a;
    uchar depth = inttype & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (inttype >> CV_CN_SHIFT);
    switch ( depth ) {
        case CV_8U:  r = "8U";   a = "Mat.at<uchar>(y,x)"; break;  
        case CV_8S:  r = "8S";   a = "Mat.at<schar>(y,x)"; break;  
        case CV_16U: r = "16U";  a = "Mat.at<ushort>(y,x)"; break; 
        case CV_16S: r = "16S";  a = "Mat.at<short>(y,x)"; break; 
        case CV_32S: r = "32S";  a = "Mat.at<int>(y,x)"; break; 
        case CV_32F: r = "32F";  a = "Mat.at<float>(y,x)"; break; 
        case CV_64F: r = "64F";  a = "Mat.at<double>(y,x)"; break; 
        default:     r = "User"; a = "Mat.at<UKNOWN>(y,x)"; break; 
    }   
    r += "C";
    r += (chans+'0');
    std::cout << "Mat is of type " << r << " and should be accessed with " << a << std::endl;
    
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
      mI.at<float>(i+1, j+1) = pixelValue;
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
      pixelValue += mI.at<float>(i+1, j);
      pixelValue += mI.at<float>(i, j+1);
      pixelValue -= mI.at<float>(i, j);
      pixelValue += (float)m.at<uchar>(i, j);
      mI.at<float>(i+1, j+1) = pixelValue;
    }
  }
}

void rotated_integral_image1(cv::Mat& mI, cv::Mat m, int w, int h)
{
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      int pixelValue = 0;

      int k = i - 1;
      int l = 3;
      while (k >= 0)
      {
        for (int g = j - (l / 2); g <= j + (l / 2); ++g)
        {
          // std::cout << k << ", " << g << std::endl;
          pixelValue += m.at<uchar>(k,g);
        }
        --k;
        l += 2;
      }

      pixelValue += m.at<uchar>(i,j);
      mI.at<float>(i+1, j+1) = pixelValue;
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

int sum_pixels1(cv::Mat& mI, int r0, int c0, int r1, int c1)
{
  // sum = mI[r1][c1] - mI[r0-1][c1] - mI[r1][c0-1] + m1[r0-1][c0-1]

  if (r0 == r1 || c0 == c1)
  {
    return 0;
  }

  float a = mI.at<float>(r1+1,c1+1);
  float b = mI.at<float>(r0,c1+1);
  float c = mI.at<float>(r1+1,c0);
  float d = mI.at<float>(r0,c0);

  return a - b - c + d;
}

int sum_pixels2(cv::Mat& m, int r0, int c0, int r1, int c1)
{
  int sum = 0;
  for (int i = r0; i <= r1; ++i)
  {
    for (int j = c0; j <= c1; ++j)
    {
      sum += m.at<uchar>(i,j);
    }
  }

  return sum;
}

int main()
{
  int w = 200;
  int h = 100;
  cv::Mat m(h, w, CV_8UC1);
  cv::Mat mI(h+1, w+1, CV_32FC1); // integral image uses row / column of padding
  cv::Mat mI2(h+1, w+1, CV_32FC1);

  cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Integral image", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Integral image2", cv::WINDOW_AUTOSIZE);

  randomize_image(m, w, h);

  // method 1: loop over every pixel

  auto start = std::chrono::steady_clock::now();

  generate_integral_image(mI, m, w, h); // integral image has row and column of padding

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

  for (int i = 0; i <= 10; ++i)
  {
    for (int j = 0; j <= 10; ++j)
    {
      std::cout << (int)m.at<uchar>(i,j) << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Integral" << std::endl;
  for (int i = 0; i <= 10; ++i)
  {
    for (int j = 0; j <= 10; ++j)
    {
      std::cout << (int)mI2.at<float>(i,j) << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Sums" << std::endl;
  std::cout << sum_pixels1(mI, 0, 0, 1,1) << std::endl;
  std::cout << sum_pixels2(m, 0, 0, 1,1) << std::endl;
  std::cout << sum_pixels1(mI, 4, 4, 10, 10) << std::endl;
  std::cout << sum_pixels2(m, 4, 4, 10, 10) << std::endl;

  std::cout << sum_pixels1(mI, 1, 2, 31, 31) << std::endl;
  std::cout << sum_pixels2(m, 1, 2, 31, 31) << std::endl;

  cv::Mat mI3;
  cv::integral(m, mI3);

  std::cout << "w: " << mI3.cols << std::endl;
  std::cout << "h: " << mI3.rows << std::endl;

  bool eq = std::equal(mI.begin<uchar>(), mI.end<uchar>(), mI2.begin<uchar>());

  assert(eq);

  // compare against OpenCV generated integral image(mI3)
  // get type of mI3, type is int
  MatType(mI3);

  assert(mI3.rows == mI2.rows);
  assert(mI3.cols == mI2.cols);

  for (int i = 0; i < mI3.rows; ++i)
  {
    for (int j = 0; j < mI3.cols; ++j)
    {
      // CV integral image is int32, our integral image is float
      assert(std::abs(float(mI3.at<int>(i,j) - mI2.at<int>(i,j)) < 0.1));
    }
  }

  // scale images for floating point display
  int maxVal = max_val(mI, w+1, h+1);
  scale_image(mI, w+1, h+1, maxVal);
  maxVal = max_val(mI2, w+1, h+1);
  scale_image(mI2, w+1, h+1, maxVal);

  cv::Mat mI4(h+1, w+1, CV_32FC1);
  mI4 = cv::Mat::zeros(h+1, w+1, CV_32FC1);
  rotated_integral_image1(mI4, m, w, h);
  maxVal = max_val(mI4, w+1, h+1);
  scale_image(mI4, w+1, h+1, maxVal);

  while (true)
  {
    cv::imshow("Image", m);
    cv::imshow("Integral image", mI);
    cv::imshow("Integral image2", mI2);
    cv::imshow("Rotated Integral image1", mI4);

    char c = (char)cv::waitKey(10);
    if (c == KeyCodes::ESCAPE)
    {
      break;
    }
  }
  return 0;
}