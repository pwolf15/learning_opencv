#include <iostream>
#include <opencv2/opencv.hpp>

void my_mouse_callback(int event, int x, int y, int flags, void* param);

cv::Mat original;

int main(int argc, char** argv)
{
  cv::Mat img = cv::imread(argv[1], -1);

  img.copyTo(original);
  if (img.empty())
    return -1;

  cv::namedWindow("Show Pixel", cv::WINDOW_AUTOSIZE);
  cv::setMouseCallback("Show Pixel", my_mouse_callback, (void*)&img);

  while (true)
  {
    cv::imshow("Show Pixel", img);
    char c = (char)cv::waitKey(25);
    if (c == 27)
      break;
  }

  cv::destroyWindow("Show Pixel");
  return 0;
}

void my_mouse_callback(int event, int x, int y, int flags, void* param)
{
  cv::Mat& image = *(cv::Mat*)param;

  switch (event)
  {
    case cv::EVENT_LBUTTONDOWN: {
      
      original.copyTo(image);

      // get color at point
      cv::Vec3b color = image.at<cv::Vec3b>(y, x);

      std::string col = "R: " + std::to_string(color[2]) + " G: " + std::to_string(color[1]) + " B: " + std::to_string(color[0]);
      int baseline=0;
      cv::Size sz = cv::getTextSize(col, cv::FONT_HERSHEY_PLAIN, 0.5, 1, &baseline);
      cv::rectangle(image, cv::Point(x-5, y-10), cv::Point(x+sz.width,y+sz.height), cv::Scalar(0,0,0), -1);
      cv::putText(image, col, cv::Point(x, y), cv::FONT_HERSHEY_PLAIN, 0.5,
                cv::Scalar(255, 255, 255));
    }
    break;

    default:
      break;
  }

} 