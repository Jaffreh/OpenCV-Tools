#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace std;
using namespace cv;

Mat img, binaryImg;
Mat rgbChannel[3];

int main(int argc, char *argv[]){
    img = imread(argv[1]);
    
    // Image segmentation (on red channel)
    split(img, rgbChannel);
    threshold(rgbChannel[2], binaryImg, 150, 255, THRESH_BINARY);

    namedWindow("Segmentation App");
    imshow("Segmentation App", binaryImg);
    
    while(char(waitKey(1)) != 'q') {}
    return 0;
}
