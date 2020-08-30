#include <iostream>

using namespace std;

#define OK 0
#define CANNOT_LOAD_CASCADE -1
#define CANNOT_OPEN_CAMERA -2

int startFaceDetection(string cascadeName, bool (*callback)(int, int));