#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("green", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("green_compare", cv::WINDOW_AUTOSIZE);

  cv::Mat img = cv::imread("/home/pwolf/Downloads/garden.jpeg");
  cv::Mat rgb_channel[3];
  cv::split(img, rgb_channel);
  if (img.empty())
    return -1;

  cv::Mat clone1, clone2;
  cv::Mat green = rgb_channel[1];
  clone1 = green.clone();
  clone2 = green.clone();
  
  double min, max;
  int minIdx, maxIdx;
  cv::minMaxIdx(green, &min, &max, &minIdx, &maxIdx);

  std::cout << "Min: " << minIdx << ", minvalue: " << min << std::endl;
  std::cout << "Max: " << maxIdx << ", maxValue: " << max << std::endl;

  unsigned char thresh = (unsigned char)((max - min) / 2.0);
  clone1.setTo(thresh);
  clone2.setTo(0);

  cv::imshow("green", green);

  cv::compare(green, clone1, clone2, cv::CMP_GE);

  cv::subtract(green, thresh/2, green, clone2);

  cv::imshow("green_compare", green);

  cv::waitKey(0);

  return 0;
}