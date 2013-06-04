#include "ros/ros.h"
#include "std_msgs/String.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
//global variables

ros::Publisher filteredPub;
sensor_msgs::PointCloud2 filteredOutput;
//ros::Publisher nearObjects;


void callback(const sensor_msgs::PointCloud2 input)
{

//printf ("Before filtering Cloud = %d Points\n", input->width * input->height);
  printf ("PCL Filters running\n");
  

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr input_pcl (new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr output_pcl(new pcl::PointCloud<pcl::PointXYZRGB>);

  pcl::fromROSMsg(input,*input_pcl);
  
 
  //Voxel grid filter used to reduce computation requirements 
  pcl::VoxelGrid<pcl::PointXYZRGB> vG;
  vG.setInputCloud(input_pcl);
  vG.setLeafSize (0.01f, 0.01f, 0.01f);
  vG.filter(*output_pcl);
  
  //as setInputCloud uses constant pointer data type as input,a new constant ptr is initialized
  //const sensor_msgs::PointCloud2ConstPtr& input2=filteredOutput.makeShared();
  //typedef boost::shared_ptr< ::sensor_msgs::PointCloud2 const> sensor_msgs::PointCloud2::ConstPtr input2(filteredOutput)

  //const sensor_msgs::PointCloud2<sensor_msgs::PointCloud2>::Ptr input2( new sensor_msgs::PointCloud2<sensor_msgs::PointCloud2>(filteredOutput) );
  
  //Statistical Outlier Removal(remove noise)
  //pcl::StatisticalOutlierRemoval<sensor_msgs::PointCloud2> sor;
  //sor.setInputCloud(input2);
  //sor.setMeanK(50);
  //sor.setStddevMulThresh(1.0);
  //sor.filter(filteredOutput);
  pcl::toROSMsg(*output_pcl,filteredOutput);
  filteredPub.publish(filteredOutput);
  
  //const sensor_msgs::PointCloud2ConstPtr& input3=filteredOutput;
 
  //passthrough filter to detect nearby objects
 // pcl::PassThrough<sensor_msgs::PointCloud2> pass;
  //pass.setInputCloud(input3);
  //pass.setFilterFieldName("z");
 // pass.setFilterLimits(0,1);
 // pass.filter(*filteredOutput);
  //nearObjects.publish(*filteredOutput);
}




int
main (int argc, char** argv)
{
  ros::init (argc, argv, "kinectPcl_Filters");
  ros::NodeHandle nh;
  //ros::NodeHandle n;

  printf("\ninitialized\n");

  ros::Subscriber sub = nh.subscribe("/camera/depth_registered/points", 1, callback);


  printf("\nSubscriber Running\n");
  filteredPub = nh.advertise<sensor_msgs::PointCloud2> ("filteredOutput", 1);
  printf("\Publisher Running\n");
  //nearObjects = n.advertise<sensor_msgs::PointCloud2>("nearObjects",1);
  ros::spin();
  printf("\nSPIN\n");

  return (0);
}

