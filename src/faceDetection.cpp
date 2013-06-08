//detects faces and eyes using Haar cascade
//Author: Balakumar Sundarlingam



#include<ros/ros.h>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/image_encodings.h>
#include<iostream>
#include<stdio.h>

using namespace std;
using namespace cv;
//global variables
string face_cascade_name="/opt/ros/groovy/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
string eyes_cascade_name="/opt/ros/groovy/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;


void faceDetect(Mat frame)
{
	Mat frame_mono;
        std::vector<Rect> faces;
	cvtColor(frame,frame_mono,CV_BGR2GRAY);
	equalizeHist(frame_mono,frame_mono);
	face_cascade.detectMultiScale(frame_mono,faces,1.1,2,0|CV_HAAR_SCALE_IMAGE,Size(20,20));
	for (int i=0;i<faces.size();i++)
	{		
		Point center(faces[i].x+faces[i].width*.5,faces[i].y+faces[i].height*.5);
		Point pt1(faces[i].x,faces[i].y);		
		Point pt2(faces[i].x+faces[i].width,faces[i].y+faces[i].height);
		rectangle(frame,pt1,pt2,Scalar(255,0,0),2,8,0);
		Mat faceROI = frame_mono( faces[i] );
		std::vector<Rect> eyes;

		eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(20, 20) );

    		for( int j = 0; j < eyes.size(); j++ )
     		{
       			Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
      			int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
      			circle( frame, center, radius, Scalar( 255, 255, 0 ), 4, 8, 0 );
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
	faceDetect(image_cv);	
	waitKey(3);
}

int main(int argc,char** argv)
{
        cv::namedWindow("output");	
	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

	ros::init(argc,argv,"opencvFaceDetection");
	ros::NodeHandle nh;
	ros::Subscriber sub=nh.subscribe("/kinectSplitter/image", 1, callback);
	ros::spin();
	return(0);
}
