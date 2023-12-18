// Program to examine erosion and dilation of images

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat image, image_processed;
int choice_slider = 0, size_slider = 5;

void process(){
    Mat st_elem = getStructuringElement(MORPH_RECT, Size(size_slider, size_slider));

    if(choice_slider == 0){
        erode(image, image_processed, st_elem);
    } else {
        dilate(image, image_processed, st_elem);
    }
    imshow("Processed Image", image_processed);
}

void on_choice_slider(int, void *){
    process();
}

void on_size_slider(int, void *){
    int size = max(1, size_slider);
    size = size % 2 == 0 ? size + 1 : size;
    setTrackbarPos("Kernel Size", "Processed Image", size);
    process();
}

int main(int argc, char *argv[]){
    
    image = imread(argv[1]);
    
    namedWindow("Original Image");
    namedWindow("Processed Image");

    imshow("Original Image", image);
    Mat st_elem = getStructuringElement(MORPH_RECT, Size(size_slider, size_slider));
    erode(image, image_processed, st_elem);
    imshow("Processed Image", image_processed);

    createTrackbar("Erode/Dilate", "Processed Image", &choice_slider, 1, on_size_slider);
    createTrackbar("Kernel Size", "Processed Image", &size_slider, 21, on_size_slider);

    while(char(waitKey(1) != 'q')){}

    return 0;
}
