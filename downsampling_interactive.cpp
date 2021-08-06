#include <fstream>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int g_slider_position = 0;
int g_run = 1, g_dontset = 0;
int g_sampling_rate = 2;
cv::VideoCapture g_cap;

const int g_sample_max = 100;

void onTrackbarSlide(int pos, void*)
{
  g_sampling_rate =
      2 + 2 * round((float)3 * (float)(pos) / (float)g_sample_max);
  // if (!g_dontset)
  //   g_run = 1;
  // g_dontset = 0;
}

int main(int argc, char** argv)
{
  cv::namedWindow("Example 2-4", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Downsampled", cv::WINDOW_AUTOSIZE);
  g_cap.open(std::string(argv[1]));

  cv::createTrackbar("Sampling", "Example 2-4", &g_slider_position,
                     g_sample_max, onTrackbarSlide);
  int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
  int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  cv::Mat frame, downsampled;
  for (;;)
  {
    // 1. get frame
    // 2.

    g_cap >> frame;
    if (frame.empty())
      break;

    cv::Size sz(1280 / 4, 720 / 4);
    downsampled = frame;
    std::cout << g_sampling_rate << std::endl;
    for (int i = 1; i <= g_sampling_rate / 2; ++i)
    {
      cv::pyrDown(downsampled, downsampled);
    }

    cv::imshow("Downsampled", downsampled);
    cv::imshow("Example 2-4", frame);

    char c = (char)cv::waitKey(10);
    if (c == 27)
      break;
  }
  return 0;
}