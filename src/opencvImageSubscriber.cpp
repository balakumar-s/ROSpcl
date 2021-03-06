//Code subscribes to openni device and converts to Mat format to use in openCV
//Author: Balakumar Sundarlingam



#include<ros/ros.h>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/image_encodings.h>

void callback(const sensor_msgs::Image& input)
{
	cv_bridge::CvImagePtr input_cv;
	input_cv=cv_bridge::toCvCopy(input,sensor_msgs::image_encodings::BGR8);
	cv::Mat image_cv;
	image_cv=input_cv->image;
	cv::imshow("output",image_cv);
	cv::waitKey(1);
}
int main(int argc,char** argv)
{
        cv::namedWindow("output");	
	ros::init(argc,argv,"opencvImagesubsriber");
	ros::NodeHandle nh;
	ros::Subscriber sub=nh.subscribe("/kinectSplitter/image", 1, callback);
	ros::spin();
	return(0);
}
