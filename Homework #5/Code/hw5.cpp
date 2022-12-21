#include <iostream>
#include <opencv/cv.hpp>

using namespace cv;
using namespace std;


void bilinear_interpolation(Mat& org_img, Mat& new_img) {
    double x_rate = (double)new_img.cols / org_img.cols;
    double y_rate = (double)new_img.rows / org_img.rows;


    for (int y = 0; y < new_img.rows; y++) {
        for (int x = 0; x < new_img.cols; x++) {

            int px = (int)(x / x_rate);
            int py = (int)(y / y_rate);
            double fx1 = (double)x / x_rate - px;
            double fx2 = 1 - fx1;
            double fy1 = (double)y / y_rate - py;
            double fy2 = 1 - fy1;

            double w1 = fx2 * fy2;
            double w2 = fx1 * fy2;
            double w3 = fx2 * fy1;
            double w4 = fx1 * fy1;

            Vec3b P1 = org_img.at<Vec3b>(py, px);
            Vec3b P2 = org_img.at<Vec3b>(py, px + 1);
            Vec3b P3 = org_img.at<Vec3b>(py + 1, px);
            Vec3b P4 = org_img.at<Vec3b>(py + 1, px + 1);

            new_img.at<Vec3b>(y, x) = w1 * P1 + w2 * P2 + w3 * P3 + w4 * P4;
        }
    }
}

int main(int argc, char* argv[]) {
    
    
    Mat before = imread("sample.png", CV_LOAD_IMAGE_COLOR);
    
    imshow("before", before);
    waitKey(0);


    int after_y = before.rows*2.0;
    int after_x = before.cols*1.5;

    Mat after(after_y, after_x, CV_8UC3);
    bilinear_interpolation<cv::Vec3b>(before, after);

    
    imshow("after", after);
    waitKey(0);
   
    return 0;
}