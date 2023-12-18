// Program to crop images using GUI mouse callbacks.
// To be extended in the future to a better program.

#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

// --- Global variables
bool left_mouse_down = false;
bool left_mouse_up = false;

Mat img;

Point corner_1, corner_2;
Rect box;


static void mouse_callback(int event, int x, int y, int flags, void *){
    // Button is pressed, record first corner
    if(event == EVENT_LBUTTONDOWN){
        left_mouse_down = true;
        corner_1.x = x;
        corner_1.y = y;
        cout << "Corner 1 recorded at " << corner_1 << endl;
    }

    // Button is released, record second corner
    if(event == EVENT_LBUTTONUP){
        // Selection must be bigger than 20px
        if(abs(x - corner_1.x) > 20 && abs(y - corner_1.y) > 20){
            left_mouse_up = true;
            corner_2.x = x;
            corner_2.y = y;
            cout << "Corner 2 recorder at " << corner_2 << endl;
        } else {
            cout << "Please select a bigger region." << endl;
            left_mouse_down = false;
        }
    }

    // Update selection box as user moves mouse
    if(left_mouse_down && !left_mouse_up){
        Point pt; 
        pt.x = x;
        pt.y = y;
        Mat local_img = img.clone();
        rectangle(local_img, corner_1, pt, Scalar(0, 0, 255));
        imshow("Cropping App", local_img);
    }

    // Perform cropping
    if(left_mouse_down && left_mouse_up){
        box.width = abs(corner_1.x - corner_2.x);
        box.height = abs(corner_1.y - corner_2.y);
        box.x = min(corner_1.x, corner_2.x);
        box.y = min(corner_1.y, corner_2.y);

        Mat crop(img, box);
        namedWindow("Crop");
        imshow("Crop", crop);

        left_mouse_down = false;
        left_mouse_up = false;
    }
}

int main(int argc, char *argv[]){
    img = imread(argv[1]);
    
    namedWindow("Cropping App");
    imshow("Cropping App", img);

    setMouseCallback("Cropping App", mouse_callback);

    while(char(waitKey(1)) != 'q'){}

    return 0;
}
