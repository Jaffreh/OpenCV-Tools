// Program to detect edges in an image usint the threshholded Scharr operator

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace cv;
using namespace std;

Mat edges, edges_thresholded;
int slider = 50;
void on_slider(int, void *) {
    if(!edges.empty()) {
        Mat edges_thresholded;
        threshold(edges, edges_thresholded, slider, 255, THRESH_TOZERO);
        imshow("Thresholded Scharr edges", edges_thresholded);
    }
}
int main(int argc, char *argv[]) {
    
    Mat image = imread(argv[1]), image_blurred;
    GaussianBlur(image, image_blurred, Size(3, 3), 0, 0);
    
    Mat image_gray;
    cvtColor(image_blurred, image_gray, COLOR_RGB2GRAY);
    
    Mat grad_x, grad_y;
    Scharr(image_gray, grad_x, CV_32F, 1, 0);
    Scharr(image_gray, grad_y, CV_32F, 0, 1);
    pow(grad_x, 2, grad_x);
    pow(grad_y, 2, grad_y);
    
    Mat grad = grad_x + grad_y;
    sqrt(grad, grad);
    
    namedWindow("Original image", 1000);
    namedWindow("Thresholded Scharr edges", 1000);

    grad.convertTo(edges, CV_8U);
    
    threshold(edges, edges_thresholded, slider, 255, THRESH_TOZERO);
    
    imshow("Original image", image);
    imshow("Thresholded Scharr edges", edges_thresholded);
    
    createTrackbar("Threshold", "Thresholded Scharr edges", &slider, 255, on_slider);

    while(char(waitKey(1)) != 'q') {}
    
    return 0;
}
