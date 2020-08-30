#include "opencv2/core/utility.hpp"
#include <iostream>
#include "face.h"

extern "C" {
#include "facemove.h"
}

using namespace std;

int moveleft = 20;

bool processInput(int x, int y)
{
    cout << "X: " << x << ", Y:" << y << endl;
    moveleft = moveleft - 1;
    return moveleft > 0;
}

int start(char *serial, string cascadeName)
{
    if (prepareSystem(serial) == 0)
    {
        return 0;
    }
    cout << "Starting detection:" << endl;
    cout << "Serial device: " << serial << endl;
    cout << "Cascade file: " << cascadeName << endl;
    int result = startFaceDetection(cascadeName, processInput);
    cout << "Result: " << result << endl;
    cleanupSystem();
    return 0;
}

int main(int argc, const char **argv)
{
    string cascadeName;
    string serial;

    cv::CommandLineParser parser(argc, argv, "{cascade|haarcascade_frontalface_alt.xml|}{serial|/dev/serial0|}");
    cascadeName = parser.get<string>("cascade");
    serial = parser.get<string>("serial");

    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

    start(&serial[0], cascadeName);
}