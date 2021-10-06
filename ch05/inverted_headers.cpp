#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::namedWindow("inverted_headers", cv::WINDOW_AUTOSIZE);

  cv::Mat img = cv::imread("/home/pwolf/Downloads/IMG_3875.JPG");
  cv::Mat out1, out2, out3, out4, out5, out6, out7, out8, out9;
  if (img.empty())
    return -1;

  // header 1
  cv::Mat mask1 = cv::Mat::zeros(img.rows, img.cols, CV_8U);
  cv::Rect roi1(cv::Rect(5,10,30,20));
  mask1(roi1) = 1;

  cv::Mat mask2 = cv::Mat::zeros(img.rows, img.cols, CV_8U);
  cv::Rect roi2(50,60,30,20);
  mask2(roi2) = 1;

  cv::bitwise_not(img, out1, mask1);
  cv::bitwise_not(img, out2, mask2);

  img(roi1) = 0; 
  img(roi2) = 0; 

  cv::bitwise_or(img, out1, out3);
  cv::bitwise_or(out3, out2, out4);

  cv::imshow("inverted_headers", out4);

  cv::waitKey(0);

  return 0;
}