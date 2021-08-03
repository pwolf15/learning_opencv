#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>

using namespace std;

int g_slider_position = 0;
int g_run = 1, g_dontset = 0;
cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void *)
{
  g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
  if (!g_dontset)
    g_run = 1;
  g_dontset = 0;
}

int main(int argc, char** argv)
{
  cv::Mat image = cv::imread(argv[1],-1);

  cv::namedWindow("Example 2-5-in", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Example 2-5-out", cv::WINDOW_AUTOSIZE);

  cv::imshow("Example 2-5-in", image);

  cv::Mat out;

  cv::GaussianBlur(image, out, cv::Size(5,5), 3, 3);
  cv::GaussianBlur(out, out, cv::Size(5,5), 3, 3);
  
  cv::imshow("Example 2-5-out", out);

  cv::waitKey(0);
  
  return 0;
}