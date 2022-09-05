#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <random>
#include <iostream>

int main(int argc, char** argv)
{
  cv::RNG rng = cv::theRNG();


  // 100 three-byte objects
  // center: 64, 192, 128
  // variance: 2, 2, 2
  cv::Mat m(100,1,CV_8UC3);
  rng.fill(m, cv::RNG::NORMAL, cv::Vec3f(64, 192, 128), cv::Vec3f(sqrt(2), sqrt(2), sqrt(2)));

  std::vector<cv::Mat> planes;
  cv::split(m, planes);
  for (int i = 0; i < 5; ++i)
  {
    cv::Vec3b color = m.at<cv::Vec3b>(i,0);
    std::cout << "r: " << (int)color[0] << " ";
    std::cout << "g: " << (int)color[1] << " ";
    std::cout << "b: " << (int)color[2] << "\n";
  }
  
  cv::PCA PCA(planes[0], cv::Mat(), cv::PCA::DATA_AS_ROW, 2);
  planes[0] = PCA.project(planes[0]);
  PCA(planes[1], cv::Mat(), cv::PCA::DATA_AS_ROW, 2);
  planes[1] = PCA.project(planes[1]);
  PCA(planes[2], cv::Mat(), cv::PCA::DATA_AS_ROW, 2);
  planes[2] = PCA.project(planes[2]);

  float f1, f2, f3;
	f1 = 0;
	f2 = 0;
	f3 = 0;
	for (int i = 0;i<100;i++)
	{
		f1 += planes[0].at<float>(i,0);
		f2 += planes[1].at<float>(i,0);
		f3 += planes[2].at<float>(i,0);
	}
	f1 = f1/100;
	f2 = f2/100;
	f3 = f3/100;

  std::cout << planes[0] << std::endl;

  std::cout << "f1, f2, f3: " << f1 << "," << f2 << "," << f3 << std::endl;
  return 0;
}