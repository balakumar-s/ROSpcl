#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc,char* argv[])
{
Mat img;
img=imread("/home/jarvis/Pictures/lena.jpg");
namedWindow("output");
imshow("output",img);
waitKey(0);
}
