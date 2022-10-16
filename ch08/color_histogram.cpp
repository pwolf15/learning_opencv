#include <iostream>
#include <opencv2/opencv.hpp>

void my_mouse_callback(int event, int x, int y, int flags, void* param);

cv::Mat original;
cv::Mat histImg;
int x_1 = 0;
int y_1 = 0;

void draw_hist()
{
  cv::Mat r = histImg(cv::Range(0, 100), cv::Range(0, 400));
  cv::Mat g = histImg(cv::Range(100, 200), cv::Range(0, 400));
  cv::Mat b = histImg(cv::Range(200, 300), cv::Range(0, 400));

  cv::rectangle(r, cv::Point(0, 0), cv::Point(r.cols, r.rows), cv::Scalar(0, 0, 255), -1);
  cv::rectangle(g, cv::Point(0, 0), cv::Point(r.cols, r.rows), cv::Scalar(0, 255, 0), -1);
  cv::rectangle(b, cv::Point(0, 0), cv::Point(r.cols, r.rows), cv::Scalar(255, 0, 0), -1);
}

int main(int argc, char** argv)
{
  cv::Mat img = cv::imread(argv[1], -1);
  cv::Mat hist(300, 400, CV_8UC3);

  img.copyTo(original);
  hist.copyTo(histImg);
  if (img.empty())
    return -1;

  cv::namedWindow("Color Histogram", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Hist", cv::WINDOW_AUTOSIZE);
  cv::setMouseCallback("Color Histogram", my_mouse_callback, (void*)&img);

  while (true)
  {
    cv::imshow("Color Histogram", img);
    cv::imshow("Hist", histImg);

    char c = (char)cv::waitKey(25);
    if (c == 27)
      break;
  }

  cv::destroyWindow("Color Histogram");
  cv::destroyWindow("Hist");
  return 0;
}

void my_mouse_callback(int event, int x, int y, int flags, void* param)
{
  cv::Mat& image = *(cv::Mat*)param;

  switch (event)
  {
    case cv::EVENT_LBUTTONDOWN: {
      
      x_1 = x;
      y_1 = y;
      // hold onto coordds

      // // get color at point
      // cv::Vec3b color = image.at<cv::Vec3b>(y, x);

      // std::string col = "R: " + std::to_string(color[2]) + " G: " + std::to_string(color[1]) + " B: " + std::to_string(color[0]);
      // int baseline=0;
      // cv::Size sz = cv::getTextSize(col, cv::FONT_HERSHEY_PLAIN, 0.5, 1, &baseline);
      // cv::rectangle(image, cv::Point(x-5, y-10), cv::Point(x+sz.width,y+sz.height), cv::Scalar(0,0,0), -1);
      // cv::putText(image, col, cv::Point(x, y), cv::FONT_HERSHEY_PLAIN, 0.5,
      //           cv::Scalar(255, 255, 255));
    }
    break;

    case cv::EVENT_LBUTTONUP: {

      int x_2 = x;
      int y_2 = y;

      original.copyTo(image);
  
      // draw rectangle over selected region 
      cv::Mat roi = image(cv::Rect(x_1, y_1, x_2-x_1, y_2-y_1));
      double alpha = 0.7;
      cv::Mat color(roi.size(), CV_8UC3, cv::Scalar(0, 0, 0));
      cv::addWeighted(color, alpha, roi, 1.0 - alpha, 0.0, roi);

      draw_hist();
    }

    default:
      break;
  }

} 