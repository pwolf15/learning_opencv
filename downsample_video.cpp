#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  cv::namedWindow("Example 2-11", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Downsampled", cv::WINDOW_AUTOSIZE);

  cv::VideoCapture cap;

  if (argc == 1)
  {
    cap.open(0);
  }
  else
  {
    cap.open(std::string(argv[1]));
  }

  std::cout << "HERE1" << std::endl;
  double fps = cap.get(cv::CAP_PROP_FPS);
  cv::Size size(
    (int)cap.get(cv::CAP_PROP_FRAME_WIDTH),
    (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)
  );

  cv::VideoWriter writer;

  writer.open(argv[2], cv::VideoWriter::fourcc('M','J','P','G'), fps, size);

  cv::Mat downsampled_frame, bgr_frame, out;
  for (;;)
  {
    cap >> bgr_frame;

    if (bgr_frame.empty())
      break;

    cv::imshow("Example 2-11", bgr_frame);

    cv::GaussianBlur(bgr_frame, out, cv::Size(5,5), 3, 3);
    cv::GaussianBlur(out, downsampled_frame, cv::Size(5,5), 3, 3);

    cv::imshow("Downsampled", downsampled_frame);
    writer << downsampled_frame;
    
    if ((char)cv::waitKey(33) >= 0)
      break;
  }

  cap.release();

  return 0;
}