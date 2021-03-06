#include"ros/ros.h"
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include "std_msgs/String.h"

//Includes here

ros::Publisher pub;
sensor_msgs::PointCloud2 output;


//typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloud;


void callback(const sensor_msgs::PointCloud2ConstPtr& input)
{
  //Inside the callback should be all the process that you want to do with your point cloud and at the end publish the results.
  printf ("Before filtering Cloud = %d Points\n", input->width * input->height);

  // Do some processing to the point cloud
  pcl::VoxelGrid<sensor_msgs::PointCloud2> sor;
  sor.setInputCloud (input);
  sor.setLeafSize (0.01f, 0.01f, 0.01f);
  sor.filter (output);
  printf ("After filtering Cloud = %d Points.\n", output.width * output.height);

  //Publish the results
  pub.publish(output);
}




int
main (int argc, char** argv)
{
 // INITIALIZE ROS
  ros::init (argc, argv, "SUB_CLOUD_PUB");
  ros::NodeHandle nh;


  ros::Subscriber sub = nh.subscribe("/camera/depth_registered/points", 1, callback);


  pub = nh.advertise<sensor_msgs::PointCloud2> ("pubCloud", 1);

  ros::spin();


  return (0);
}
