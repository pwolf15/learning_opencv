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

  // random
  cv::RNG rng(time(NULL));

  for (int i = 0; i < 10; ++i)
  {
    std::cout << "Random: " << rng(10) << std::endl;  
  }
  
  std::cout << p1 << "\n" << p2 << "\n" << p3 << "\n";

  cv::Matx33f m{1,2,3,4,5,6,7,8,9};
  cv::Vec3f v{1,2,3};

  auto r = m * v;

  std::cout << r << std::endl;

  cv::Matx<float, 3, 3> m1 = {1,2,3,4,5,6,7,8,9};
  cv::Vec<float, 3> v1 = {1, 2, 3};
  auto r1 = m1*v1;

  cv::Matx<float, 3,1> m2 = v1;

  auto r2 = m1*m2;
  std::cout << r1 << std::endl;
  std::cout << r2 << std::endl;
  std::cout << v1.rows << std::endl;
  std::cout << m2.rows << std::endl;
  
  return 0;
}