#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
  cv::namedWindow("frame_counter", cv::WINDOW_AUTOSIZE);
  cv::VideoCapture cap;
  cap.open(std::string(argv[1]));

  cv::Mat frame;
  int frameCounter = 1;

  auto start = std::chrono::high_resolution_clock::now();
  for (;;)
  {
    cap >> frame;
    if (frame.empty())
      break;
    
    auto current = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(current - start);
    auto fps = (double)frameCounter * (double)(1e6)/(double)(microseconds.count());
    cv::putText(frame, "FPS: " + std::to_string(fps), cv::Point(50,50), 1, 1, cv::Scalar(0,255,0));
    cv::imshow("frame_counter", frame);
    frameCounter++;
    if ((char)cv::waitKey(33) >= 0)
      break;
  }

  return 0;
}