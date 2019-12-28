#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

#define CANNOT_LOAD_CASCADE -1
#define CANNOT_OPEN_CAMERA -2

void detectAndDraw(Mat &img);
int initialize(string cascadeName, string nestedCascadeName);
int start();

const static Scalar colors[] = {
    Scalar(255, 0, 0),
    Scalar(255, 128, 0),
    Scalar(255, 255, 0),
    Scalar(0, 255, 0),
    Scalar(0, 128, 255),
    Scalar(0, 255, 255),
    Scalar(0, 0, 255),
    Scalar(255, 0, 255)};

VideoCapture capture;
CascadeClassifier cascade, nestedCascade;
double scale;
bool tryflip;

int main(int argc, const char **argv)
{
    string cascadeName;
    string nestedCascadeName;

    cv::CommandLineParser parser(argc, argv,
                                 "{cascade|haarcascade_frontalface_alt.xml|}"
                                 "{nested-cascade|haarcascade_eye.xml|}"
                                 "{scale|1|}{try-flip||}");
    cascadeName = parser.get<string>("cascade");
    nestedCascadeName = parser.get<string>("nested-cascade");
    scale = parser.get<double>("scale");
    if (scale < 1)
        scale = 1;
    tryflip = parser.has("try-flip");

    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

    if (initialize(cascadeName, nestedCascadeName) == 0)
    {
        start();
    }

    return 0;
}

int initialize(string cascadeName, string nestedCascadeName)
{

    // This might fail, it's ok
    nestedCascade.load(nestedCascadeName);
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
            detectAndDraw(clonedFrame);
            char c = (char)waitKey(10);
            if (c == 27 || c == 'q' || c == 'Q')
                break;
        }
    }

    return 0;
}

void detectAndDraw(Mat &clonedFrame)
{
    vector<Rect> faces, faces2;
    Mat gray, smallImg;
    cvtColor(clonedFrame, gray, COLOR_BGR2GRAY);
    flip(clonedFrame, clonedFrame, 1);
    double fx = 1 / scale;
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);
    flip(smallImg, smallImg, 1);
    cascade.detectMultiScale(smallImg, faces,
                             1.1, 2, 0 | CASCADE_SCALE_IMAGE,
                             Size(30, 30));

    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = colors[i % 8];
        rectangle(clonedFrame, cvPoint(cvRound(r.x * scale), cvRound(r.y * scale)),
                  cvPoint(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)),
                  color, 1, LINE_4, 0);
    }
    imshow("result", clonedFrame);
}