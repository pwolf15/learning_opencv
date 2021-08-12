#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
  const int n_mat_size = 5;
  const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
  cv::Mat n_mat0(3, n_mat_sz, CV_32FC1);
  cv::Mat n_mat1(3, n_mat_sz, CV_32FC1);

  cv::RNG rng;
  rng.fill(n_mat0, cv::RNG::UNIFORM, 0.f, 1.f);
  rng.fill(n_mat1, cv::RNG::UNIFORM, 0.f, 1.f);

  const cv::Mat* arrays[] = { &n_mat0, &n_mat1 };
  cv::Mat my_planes[2];
  cv::NAryMatIterator it(arrays,my_planes);

  float s = 0.f;
  int n = 0;
  for (int p = 0; p < it.nplanes; p++, ++it)
  {
    s += cv::sum(it.planes[0])[0];
    s += cv::sum(it.planes[1])[0];
    n++;
  }

  std::cout << "n planes: " << n << std::endl;
  std::cout << "s: " << s << std::endl;

  return 0;
}