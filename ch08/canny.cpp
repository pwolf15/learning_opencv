#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
  cv::namedWindow("USB capture", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Grayscale", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Canny", cv::WINDOW_AUTOSIZE);

  cv::VideoCapture cap;

  cap.open(0);

  if (!cap.isOpened())
  {
    std::cerr << "Couldn't open capture." << std::endl;
    return -1;
  }

  while (1) 
  {
	  cv::Mat frame, img_gray, img_cny;
	  cap >> frame;

	  if (frame.empty())
		  break;

	  cv::cvtColor(frame, img_gray, cv::COLOR_BGR2GRAY);
	  cv::Canny(img_gray, img_cny, 10, 100, 3, true);

	  cv::imshow("USB capture", frame);
	  cv::imshow("Grayscale", img_gray);
	  cv::imshow("Canny", img_cny);

	  char c = (char) cv::waitKey(25);
          if (c == 27)
                  break;

  }

  cap.release();

  std::cout << "Hello world!" << std::endl;
  return 0;
}
