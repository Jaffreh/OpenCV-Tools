#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

int main(){

    VideoCapture cap(0);

    if(!cap.isOpened()){
        cout << "Capture device could not be opened successfully." << endl;
        return -1;
    }
    
    namedWindow("Video");

    while(char(waitKey(1)) != 'q' && cap.isOpened()){
        Mat frame;
        cap >> frame;
        if(frame.empty()){
            cout << "Video over." << endl;
            break;
        }
        imshow("Video", frame);
    }

    return 0;
}
