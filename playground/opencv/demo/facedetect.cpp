#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

#define CANNOT_LOAD_CASCADE -1
#define CANNOT_OPEN_CAMERA -2

void detectAndDraw(Mat &img, double scale);
int initialize(string cascadeName);
int start();

VideoCapture capture;
CascadeClassifier cascade;

int main(int argc, const char **argv)
{
    string cascadeName;

    cv::CommandLineParser parser(argc, argv, "{cascade|haarcascade_frontalface_alt.xml|}");
    cascadeName = parser.get<string>("cascade");

    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

    if (initialize(cascadeName) == 0)
    {
        start();
    }

    return 0;
}

int initialize(string cascadeName)
{

    if (!cascade.load(cascadeName))
    {
        cerr << "Error: Could not load classifier cascade." << endl;
        return CANNOT_LOAD_CASCADE;
    }

    int camera = 0;
    if (!capture.open(camera))
    {
        cerr << "Capture from camera #" << camera << " didn't work" << endl;
        return CANNOT_OPEN_CAMERA;
    }

    return 0;
}

int start()
{
    Mat frame;
    if (capture.isOpened())
    {
        for (;;)
        {
            capture >> frame;
            if (frame.empty())
                break;
            Mat clonedFrame = frame.clone();
            detectAndDraw(clonedFrame, 1.2);
            char c = (char)waitKey(10);
            if (c == 27 || c == 'q' || c == 'Q')
                break;
        }
    }

    return 0;
}

void detectAndDraw(Mat &clonedFrame, double scale)
{
    vector<Rect> faces;
    Mat gray, smallImg;
    cvtColor(clonedFrame, gray, COLOR_BGR2GRAY);
    flip(clonedFrame, clonedFrame, 1);
    double fx = 1 / scale;
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);
    flip(smallImg, smallImg, 1);
    cascade.detectMultiScale(smallImg, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    Scalar color = Scalar(206, 220, 237);
    Scalar colorLine = Scalar(100, 100, 237);

    if (faces.empty())
    {
        return;
    }
    Rect r = faces[0];
    CvPoint topLeft = cvPoint(cvRound(r.x * scale), cvRound(r.y * scale));
    CvPoint widthHeight = cvPoint(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale));
    Point faceCenter = Point((widthHeight.x + topLeft.x) / 2, (widthHeight.y + topLeft.y) / 2);
    Size imageSize = clonedFrame.size();
    Point imageCenter = Point(imageSize.width / 2, imageSize.height / 2);
    rectangle(clonedFrame, topLeft, widthHeight, color, 1, LINE_4, 0);
    line(clonedFrame, faceCenter, imageCenter, colorLine, 2, LINE_4, 0);
    imshow("result", clonedFrame);
}