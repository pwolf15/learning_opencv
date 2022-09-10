#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
  cv::namedWindow("USB capture", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Blurred", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Sobel", cv::WINDOW_AUTOSIZE);

  cv::VideoCapture cap;

  cap.open(0);

  if (!cap.isOpened())
  {
    std::cerr << "Couldn't open capture." << std::endl;
    return -1;
  }

  while (1) 
  {
	  cv::Mat frame;
	  cap >> frame;

	  if (frame.empty())
		  break;

	  cv::Mat blurred, sobel;

	  cv::GaussianBlur(frame, blurred, cv::Size(5,5), 0);
	  cv::Sobel(frame, sobel, CV_8U, 0, 1);
	  cv::imshow("USB capture", frame);
	  cv::imshow("Blurred", blurred);
	  cv::imshow("Sobel", sobel);

	  char c = (char) cv::waitKey(25);
	  if (c == 27)
		  break;

  }

  cap.release();

  std::cout << "Hello world!" << std::endl;
  return 0;
}
