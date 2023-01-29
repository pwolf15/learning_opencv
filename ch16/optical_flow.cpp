#include <opencv2/opencv.hpp>
#include <iostream>

static const int MAX_CORNERS = 1000;

void help(char** argv) {
    std::cout << "Call: " << argv[0] << " [image1] [image2]" << std::endl;
    std::cout << "Demonstrates Pyramid Lucas-Kanade optical flow." << std::endl;
}


int main(int argc, char** argv)
{
    if (argc != 3) { help(argv); exit(-1); }

    cv::Mat imgA = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat imgB = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
    int win_size = 10;
    cv::Mat imgC = cv::imread(argv[2], cv::IMREAD_UNCHANGED);
    std::vector<cv::Point2f> cornersA, cornersB;

    cv::goodFeaturesToTrack(
        imgA,
        cornersA,
        MAX_CORNERS,
        0.01,
        5,
        cv::noArray(),
        3,
        false,
        0.04
    );
    cv::cornerSubPix(
        imgA,
        cornersA,
        cv::Size(win_size, win_size),
        cv::Size(-1,-1),
        cv::TermCriteria(
            cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
            20,
            0.03
        )
    );

    // Lucas Kanade algorithm
    std::vector<uchar> features_found;
    cv::calcOpticalFlowPyrLK(
        imgA,
        imgB,
        cornersA,
        cornersB,
        features_found,
        cv::noArray(),
        cv::Size(win_size*2+1,win_size*2+1),
        5,
        cv::TermCriteria(
            cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
            20,
            0.3
        )
    );

    for (int i = 0; i < (int)cornersA.size(); ++i) 
    {
        if (!features_found[i])
            continue;

        cv::line(imgC, cornersA[i], cornersB[i], cv::Scalar(0,255,0), 2, cv::LINE_AA);
    }

    cv::imshow("ImageA", imgA);
    cv::imshow("ImageB", imgB);
    cv::imshow("LK Optical flow example", imgC);

    cv::waitKey(0);

    return 0;
}