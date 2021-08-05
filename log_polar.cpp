#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  cv::namedWindow("Example 2-11", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Log_Polar", cv::WINDOW_AUTOSIZE);

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

  cv::Mat logpolar_frame, bgr_frame;
  for (;;)
  {
    cap >> bgr_frame;

    if (bgr_frame.empty())
      break;

    cv::imshow("Example 2-11", bgr_frame);

    cv::logPolar(
      bgr_frame,
      logpolar_frame,
      cv::Point2f(
        bgr_frame.cols/2,
        bgr_frame.rows/2
      ),
      40,
      cv::WARP_FILL_OUTLIERS
    );

    cv::imshow("Log_Polar", logpolar_frame);
    writer << logpolar_frame;
    
    if ((char)cv::waitKey(33) >= 0)
      break;
  }

  cap.release();

  return 0;
}