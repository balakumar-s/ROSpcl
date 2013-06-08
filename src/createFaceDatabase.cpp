#include<ros/ros.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
#include<sstream>
#include<sys/stat.h>
//#include<stdio.h>
//#include<stdlib.h>
#include<string>
#include<sensor_msgs/image_encodings.h>
using namespace std;
using namespace cv;
string face_cascade_name="/opt/ros/groovy/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
int count_image=1;
string person_name;

void faceDetectStore(Mat frame,string name)
{
	Mat frame_mono;
        std::vector<Rect> faces;
	cvtColor(frame,frame_mono,CV_BGR2GRAY);
	equalizeHist(frame_mono,frame_mono);
	face_cascade.detectMultiScale(frame_mono,faces,1.1,2,0|CV_HAAR_SCALE_IMAGE,Size(20,20));
	for (int i=0;i<faces.size();i++)
	{	
	string windowName="face";
	std::stringstream ss;
	ss << i;
	std::string s(ss.str());
	windowName+=s;
	cv::namedWindow(windowName);
	Point center(faces[i].x+faces[i].width*.5,faces[i].y+faces[i].height*.5);
	Point pt1(faces[i].x,faces[i].y);		
	Point pt2(faces[i].x+faces[i].width,faces[i].y+faces[i].height);
	rectangle(frame,pt1,pt2,Scalar(255,0,0),2,8,0);
	Mat face = frame_mono( faces[i] );
	imshow(windowName,face);
	if(i==0)
	{
	Mat image_resized(100,100, DataType<float>::type);
	resize(face,image_resized,image_resized.size(),0,0,CV_INTER_LINEAR);
	string location;
	location="/home/jarvis/ROS_jarvis/eigen_faces/"+name;	
	mkdir(location.c_str(),0755);
	std::stringstream cnt;
	cnt << count_image;
	std::string COUNT(cnt.str());
	location+="/"+name+COUNT+".jpeg";
	imwrite(location,image_resized);
	}
	}	
	imshow("output",frame);
}
void callback(const sensor_msgs::Image& input)
{
	cv_bridge::CvImagePtr input_cv;
	input_cv=cv_bridge::toCvCopy(input,sensor_msgs::image_encodings::BGR8);
	Mat image_cv;
	image_cv=input_cv->image;
	faceDetectStore(image_cv,person_name);	
	waitKey(0);
	count_image++;
}


int initiateDatabase(int argc,char** argv)
{
	ros::init(argc,argv,"opencvFaceDatabase");
	ros::NodeHandle nh;
	ros::Subscriber sub=nh.subscribe("/kinectSplitter/image", 1, callback);
	ros::spin();
	return(0);
}

int main(int argc,char** argv)
{
	printf("\nWelcome to Eigen Face Database\nEnter your name:\n");		
	cin>>person_name;
	cv::namedWindow("output");
	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	initiateDatabase(argc,argv);
}
	
