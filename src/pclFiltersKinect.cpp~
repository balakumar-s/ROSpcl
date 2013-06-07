#include "ros/ros.h"
#include "std_msgs/String.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
//global variables

  ros::Publisher filteredPub,nearObjects;
  sensor_msgs::PointCloud2 filteredOutput,depthOutput;
  sensor_msgs::Image imageRGB;
void callback(const sensor_msgs::PointCloud2 input)
{

  //printf ("Before filtering Cloud = %d Points\n", input->width * input->height);
    printf ("PCL Filters running\n");
  

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr input_pcl (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr output_pcl(new pcl::PointCloud<pcl::PointXYZRGB>);
    //pcl::PointCloud<pcl::PointXYZ>::Ptr depth_pcl(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ> depth_pcl; 
    pcl::fromROSMsg(input,*input_pcl);
  
 
  //Voxel grid filter used to reduce computation requirements 

    pcl::VoxelGrid<pcl::PointXYZRGB> vG;
    vG.setInputCloud(input_pcl);
    vG.setLeafSize (0.01f, 0.01f, 0.01f);
    vG.filter(*output_pcl);
    
  //Statistical Outlier Removal(remove noise)

    pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;
    sor.setInputCloud(output_pcl);
    sor.setMeanK(50);
    sor.setStddevMulThresh(1.0);
    sor.filter(*output_pcl);

  //Conversion to sensor_msgs::pointcloud2

    pcl::toROSMsg(*output_pcl,filteredOutput);
    filteredPub.publish(filteredOutput);

  //passthrough filter to detect nearby objects
    pcl::PassThrough<pcl::PointXYZRGB> pass;
    pass.setInputCloud(output_pcl);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0,1);
    pass.filter(*output_pcl);
  //near object in a seperate topic 
    pcl::toROSMsg(*output_pcl,filteredOutput);
    nearObjects.publish(filteredOutput);
  }




int
main (int argc, char** argv)
{
  ros::init (argc, argv, "kinectPcl_Filters");
  ros::NodeHandle nh;


  printf("\ninitialized\n");

  ros::Subscriber sub = nh.subscribe("/camera/depth_registered/points", 1, callback);

  printf("\nSubscriber Running\n");

  filteredPub = nh.advertise<sensor_msgs::PointCloud2> ("pclFilters/filteredOutput", 1);
  nearObjects = nh.advertise<sensor_msgs::PointCloud2>("pclFilters/nearObj",1);

  printf("\Publisher Running\n");
  ros::spin();
  printf("\nSPIN\n");

  return (0);
}

