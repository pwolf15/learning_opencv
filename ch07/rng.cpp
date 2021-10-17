#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <random>
#include <iostream>

int main(int argc, char** argv)
{
  cv::RNG rng = cv::theRNG();

  // three fp numbers from 0.0 to 1.0 (uniform)
  std::cout << "Numbers from 0.0 to 1.0 (uniform)" << std::endl;
  for (size_t i = 0; i < 3; ++i)
  {
    std::cout << (float)rng << std::endl;
  }

  // three dp centered at 0.0 (gaussian)
  std::cout << "Numbers from -1.0 to 1.0 (gaussian)" << std::endl;
  for (size_t i = 0; i < 3; ++i)
  {
    std::cout << rng.gaussian(1) << std::endl;
  }

  // three unsigned bytes from 0 to 255 (uniform)
  std::cout << "Numbers from 0 to 255 (uniform)" << std::endl;
  for (size_t i = 0; i < 3; ++i)
  {
    std::cout << (int)((uint8_t)rng.uniform(0,255)) << std::endl;
  }

  // RNG arrays

  // uniform
  cv::Mat m1(20,1,CV_32F);
  rng.fill(m1, cv::RNG::UNIFORM, 0.0, 1.0);
  std::cout << "20 floating-point from 0.0 to 1.0 (uniform)" << std::endl;
  for (int i = 0; i < m1.rows; ++i)
  {
    std::cout << m1.at<float>(i,0) << "\n";
  }

  // Gaussian
  cv::Mat m2(20,1,CV_32F);
  rng.fill(m2, cv::RNG::NORMAL, 0.0, 1.0);
  std::cout << "20 floating point from 0.0 to 1.0 (gaussian)" << std::endl;
  for (int i = 0; i < m2.rows; ++i)
  {
    std::cout << m2.at<float>(i,0) << "\n";
  } 

  // unsigned uniform
  cv::Mat m3(20,1,CV_8UC1);
  rng.fill(m3, cv::RNG::UNIFORM, 0, 255);
  std::cout << "20 unsigned bytes from 0 to 255 (uniform)" << std::endl;
  for (int i = 0; i < m3.rows; ++i)
  {
    std::cout << (int)m3.at<uchar>(i,0) << "\n";
  }

  // 20 color triplets, each of three bytes uniform
  cv::Mat m4(20,1,CV_8UC3);
  rng.fill(m4, cv::RNG::UNIFORM, 0, 255);
  std::cout << "20 color triplets from 0 to 255 (uniform)" << std::endl;
  for (int i = 0 ; i < m4.rows; ++i)
  {
    cv::Vec3b color = m4.at<cv::Vec3b>(i,0);
    std::cout << "r: " << (int)color[0] << " ";
    std::cout << "g: " << (int)color[1] << " ";
    std::cout << "b: " << (int)color[2] << "\n";
  }

  // 100 three-byte objects
  // cv::Mat m5(100,1,CV_8UC3);
  // rng.fill(m5, cv::RNG::UNIFORM, cv::Vec3f()

  // SVD
  cv::Mat A = (cv::Mat_<double>(3,2) << 1,1,0,1,-1,1);
  cv::Mat A_T;
  cv::transpose(A, A_T);
  std::cout << A << std::endl;

  cv::Mat result = A * A_T;
  cv::Mat eigenValues, eigenVectors;
  cv::eigenNonSymmetric(result,eigenValues,eigenVectors);
  std::cout << result << std::endl;
  std::cout << eigenValues << std::endl;    // 0,2,3
  std::cout << eigenVectors << std::endl;   // normalized eigenvectors

  cv::Mat W,U,Vt;
  cv::SVD::compute(A, W, U, Vt);
  std::cout << W << std::endl;
  std::cout << U << std::endl;
  std::cout << Vt << std::endl;

  return 0;
}