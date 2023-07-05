#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat m1(2, 2, CV_8UC3, Scalar(0, 0, 225));
    cout << "m1 = " << endl
         << " " << m1 << endl
         << endl;

    return 0;
}
