#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "face.h"

using namespace std;
using namespace cv;

VideoCapture capture;
CascadeClassifier cascade;

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

    return OK;
}

bool detectAndDraw(Mat &clonedFrame, double scale, bool (*callback)(int, int))
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
        return true;
    }

    Rect r = faces[0];
    CvPoint topLeft = cvPoint(cvRound(r.x * scale), cvRound(r.y * scale));
    CvPoint widthHeight = cvPoint(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale));
    Point faceCenter = Point((widthHeight.x + topLeft.x) / 2, (widthHeight.y + topLeft.y) / 2);
    Size imageSize = clonedFrame.size();
    Point imageCenter = Point(imageSize.width / 2, imageSize.height / 2);
    int faceIsRight = faceCenter.x - imageCenter.x;
    int faceIsHigher = faceCenter.y - imageCenter.y;
    return callback(faceIsRight, faceIsHigher);
}

int startFaceDetection(string cascadeName, bool (*callback)(int, int))
{
    if (initialize(cascadeName) != 0)
    {
        return CANNOT_LOAD_CASCADE;
    }

    Mat frame;
    if (capture.isOpened())
    {
        for (;;)
        {
            capture >> frame;
            if (frame.empty())
                break;
            Mat clonedFrame = frame.clone();
            if (!detectAndDraw(clonedFrame, 1.2, callback))
            {
                break;
            }
        }
    }

    return OK;
}