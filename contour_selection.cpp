// Program to find the smallest contour that surrounds the clicked point
// Author: Samarth Manoj Brahmbhatt, University of Pennsylvania
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
Mat img_all_contours;
vector<vector<Point> > closed_contours;
vector<Vec4i> heirarchy;
// Function to approximate contours by closed contours
vector<vector<Point> > make_contours_closed(vector<vector<Point> > contours) {
    vector<vector<Point> > closed_contours;
    closed_contours.resize(contours.size());
    for(int i = 0; i < contours.size(); i++)
        approxPolyDP(contours[i], closed_contours[i], 0.1, true);
    return closed_contours;
}
// Function to return the index of smallest contour in 'closed_contours' surrounding the clicked point
int smallest_contour(Point p, vector<vector<Point> > contours, vector<Vec4i> heirarchy) {
    int idx = 0, prev_idx = -1;
    while(idx >= 0) {
        vector<Point> c = contours[idx];
        // Point-polgon test
        double d = pointPolygonTest(c, p, false);
        // If point is inside the contour, check its children for an even smaller contour...
        if(d > 0) {
            prev_idx = idx;
            idx = heirarchy[idx][2];
        }
        // ...else, check the next contour on the same level
        else idx = heirarchy[idx][0];
    }
    return prev_idx;
}
void on_mouse(int event, int x, int y, int, void *) {
    if(event != EVENT_LBUTTONDOWN) return;
    // Clicked point
    Point p(x, y);
    // Find index of smallest enclosing contour
    int contour_show_idx = smallest_contour(p, closed_contours, heirarchy);
    // If no such contour, user clicked outside all contours, hence clear image
    if(contour_show_idx < 0) {
        imshow("Contours", img_all_contours);
        return;
    }
    // Draw the smallest contour using a thick red line
    vector<vector<Point> > contour_show;
    contour_show.push_back(closed_contours[contour_show_idx]);
    if(!contour_show.empty()) {
        Mat img_show = img_all_contours.clone();
        drawContours(img_show, contour_show, -1, Scalar(0, 0, 255), 3);
        imshow("Contours", img_show);
    }
}
int main(int argc, char *argv[]) {
    Mat img = imread(argv[1]);
    img_all_contours = img.clone();
    Mat img_b;
    cvtColor(img, img_b, COLOR_RGB2GRAY);
    Mat edges;
    Canny(img_b, edges, 50, 100);
    vector<vector<Point> > contours;
    findContours(edges, contours, heirarchy, RETR_TREE, CHAIN_APPROX_NONE);
    closed_contours = make_contours_closed(contours);
    drawContours(img_all_contours, closed_contours, -1, Scalar(0, 255, 0));
    imshow("Contours", img_all_contours);
    setMouseCallback("Contours", on_mouse);
    while(char(waitKey(1)) != 'q') {}
    return 0;
}
