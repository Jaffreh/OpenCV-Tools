// Program to illustrate hierarchical contour extraction
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
Mat img;
vector<vector<Point> > contours;
vector<Vec4i> heirarchy;
int levels = 0;
void on_trackbar(int, void *) {
    if(contours.empty()) return;
    Mat img_show = img.clone();
    // Draw contours of the level indicated by slider
    drawContours(img_show, contours, -1, Scalar(0, 0, 255), 3, 8, heirarchy, levels);
    imshow("Contours", img_show);
}
int main(int argc, char *argv[]) {
    img = imread(argv[1]);
    Mat img_b;
    cvtColor(img, img_b, COLOR_RGB2GRAY);
    Mat edges;
    Canny(img_b, edges, 50, 100);
    // Extract contours and heirarchy
    findContours(edges, contours, heirarchy, RETR_TREE, CHAIN_APPROX_NONE);
    namedWindow("Contours", 500);
    createTrackbar("levels", "Contours", &levels, 15, on_trackbar);
    // Initialize by drawing the top level contours (as 'levels' is initialized to 0)
    on_trackbar(0, 0);
    while(char(waitKey(1)) != 'q') {}
    return 0;
}
