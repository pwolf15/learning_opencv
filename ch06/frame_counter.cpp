#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main(int argc, char** argv)
{
  cv::namedWindow("frame_counter", cv::WINDOW_AUTOSIZE);
  cv::VideoCapture cap;
  cap.open(std::string(argv[1]));

  cv::Mat frame;
  int frameCounter = 1;
  for (;;)
  {
    cap >> frame;
    if (frame.empty())
      break;
    cv::putText(frame, "Frame counter: " + std::to_string(frameCounter), cv::Point(50,50), 1, 1, cv::Scalar(0,255,0));
    cv::imshow("frame_counter", frame);
    frameCounter++;
    if ((char)cv::waitKey(33) >= 0)
      break;
  }

  return 0;
}