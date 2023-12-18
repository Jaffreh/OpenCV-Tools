#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    cv::namedWindow("Video");
    cv::VideoCapture cap(0); // 0 corresponds to the default camera

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera." << std::endl;
        return -1;
    }

    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);

    cv::VideoWriter out("../video.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps/2, cv::Size(width, height));

    std::cout << cap.get(cv::CAP_PROP_FPS) << std::endl;

    if (!out.isOpened()) {
        std::cerr << "Error: Could not open the output video file." << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        out.write(frame);
        cv::imshow("Video", frame);
        if(cv::waitKey(1) != -1) break;
    }

    cap.release();
    out.release();
    cv::destroyAllWindows();

    return 0;
}
