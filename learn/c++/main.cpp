#include <iostream>
#include <vector>
#include <opencv4/opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;

int main(int argc,char** argv){

    vector<int> prams;
    std::cout<<"111"<< std::endl;
    cv::Mat src = cv::imread("/home/tian/Downloads/456.jpg");
    prams.push_back(IMWRITE_PNG_COMPRESSION);
    prams.push_back(9);
    imwrite("../pic/yang1.png",src,prams);
    // cv::resize(src,src,cv::Size(3840,2160));
    namedWindow("yang_png1",WINDOW_NORMAL);
    cv::imshow("src", src);
    fprintf(stdout,"yang.png1 已生成\n");

    cv::waitKey(0);
    return 0;
}