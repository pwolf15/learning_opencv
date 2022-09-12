#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
  cv::namedWindow("USB capture", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Grayscale", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Canny", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Combo", cv::WINDOW_AUTOSIZE);

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

    cv::Mat combo = cv::Mat::zeros(frame.rows, frame.cols * 3, CV_8UC3);

    cv::cvtColor(frame, img_gray, cv::COLOR_BGR2GRAY);
    cv::Canny(img_gray, img_cny, 10, 100, 3, true);

    cv::Mat m1 = combo(cv::Range(0, frame.rows), cv::Range(0, frame.cols));
    cv::Mat m2 =
        combo(cv::Range(0, frame.rows), cv::Range(frame.cols, frame.cols * 2));
    cv::Mat m3 = combo(cv::Range(0, frame.rows),
                       cv::Range(frame.cols * 2, frame.cols * 3));

    cv::imshow("USB capture", frame);
    cv::imshow("Grayscale", img_gray);
    cv::imshow("Canny", img_cny);

    cv::cvtColor(img_gray, img_gray, cv::COLOR_GRAY2BGR);
    cv::cvtColor(img_cny, img_cny, cv::COLOR_GRAY2BGR);

    frame.copyTo(m1);
    img_gray.copyTo(m2);
    img_cny.copyTo(m3);

    // labels
    cv::putText(m1, "Original", cv::Point(15, 15), cv::FONT_HERSHEY_PLAIN, 1,
                cv::Scalar(255, 255, 255));
    cv::putText(m2, "Grayscale", cv::Point(15, 15), cv::FONT_HERSHEY_PLAIN, 1,
                cv::Scalar(255, 255, 255));
    cv::putText(m3, "Canny", cv::Point(15, 15), cv::FONT_HERSHEY_PLAIN, 1,
                cv::Scalar(255, 255, 255));

    cv::imshow("Combo", combo);

    char c = (char)cv::waitKey(25);
    if (c == 27)
      break;
  }

  cap.release();

  std::cout << "Hello world!" << std::endl;
  return 0;
}
