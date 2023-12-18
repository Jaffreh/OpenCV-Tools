#include <complex>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace std;
using namespace cv;

Mat img, binaryImg;
Mat rgbChannel[3];
vector<vector<Point>> contours;
int slider = 1;
int slider_max = 255;

void on_trackbar(int pos, void *){
    threshold(rgbChannel[0], binaryImg, pos, 255, THRESH_BINARY);
    imshow("Segmentation App", binaryImg);
}

int main(int argc, char *argv[]){
    img = imread("../assets/image.jpg");
    if(argc > 1) img = imread(argv[1]); 
    
    split(img, rgbChannel); // [R, G, B]
    
    namedWindow("Segmentation App", WINDOW_FREERATIO);
    createTrackbar("Threshold Slider", "Segmentation App", &slider, slider_max, on_trackbar);
    
    while(char(waitKey(1)) != 'q') {}
    return 0;
}
