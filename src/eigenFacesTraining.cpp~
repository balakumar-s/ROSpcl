#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>

using namespace std;
using namespace cv;
int main(int argc,char** argv)
{
	vector<cv::Mat> images;
	vector<int> labels;
	vector<string> names;
	string line;
	ifstream fileToOpen;
	fileToOpen.open("/home/jarvis/ROS_jarvis/eigen_faces/imageSheet.txt");
	while(fileToOpen.good())
	{
		string location;
		string name;
		//Mat image;
		int lbl;
		fileToOpen>> lbl>> name>> location;
		images.push_back(imread(location));
		labels.push_back(lbl);
		names.push_back(name);
	}
	for(int t=0;t<names.size();++t)
	{
            cout<<names.at(t);
        }
                 
	fileToOpen.close();
	return 0;
                 
}
                 
