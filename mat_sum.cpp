#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
  const int n_mat_size = 5;
  const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
  cv::Mat n_mat(3, n_mat_sz, CV_32FC1);
  
  cv::RNG rng;
  rng.fill(n_mat, cv::RNG::UNIFORM, 0.f, 1.f);

  const cv::Mat* arrays[] = { &n_mat, 0 };
  cv::Mat my_planes[1];
  cv::NAryMatIterator it(arrays,my_planes);

  float s = 0.f;
  int n = 0;
  for (int p = 0; p < it.nplanes; p++, ++it)
  {
    s += cv::sum(it.planes[0])[0];
    n++;
  }

  std::cout << "n planes: " << n << std::endl;
  std::cout << "s: " << s << std::endl;

  return 0;
}