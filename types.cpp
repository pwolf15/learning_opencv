#include <iostream>

#include <opencv2/core.hpp>

int main()
{
  float f = 3.14159;
  std::cout << "Abs: " << abs(f) << "\n"
            << "Round: " << round(f) << "\n"
            << "Ceil: " << ceil(f) << "\n"
            << "Floor: " << floor(f) << "\n";

  cv::Point2f p1{1.25, 2.25};
  cv::Point p2 = p1;
  cv::Point2f p3 = p2;
  p3 *= 2.25;

  std::cout << p1 << "\n" << p2 << "\n" << p3 << "\n";

  return 0;
}