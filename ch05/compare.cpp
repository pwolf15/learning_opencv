#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("red", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("green", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("blue", cv::WINDOW_AUTOSIZE);

  cv::Mat img = cv::imread("/home/pwolf/Downloads/IMG_3875.JPG");
  cv::Mat rgb_channel[3];
  cv::split(img, rgb_channel);
  if (img.empty())
    return -1;

  cv::Mat clone1, clone2;
  cv::Mat green = rgb_channel[1];
  clone1 = green.clone();
  clone2 = green.clone();
  
  cv::imshow("red", rgb_channel[0]);
  cv::imshow("green", clone1);
  cv::imshow("blue", rgb_channel[2]);

  double min, max;
  int minIdx, maxIdx;
  cv::minMaxIdx(green, &min, &max, &minIdx, &maxIdx);

  std::cout << "Min: " << minIdx << ", minvalue: " << min << std::endl;
  std::cout << "Max: " << maxIdx << ", maxValue: " << max << std::endl;

  cv::waitKey(0);

  return 0;
}