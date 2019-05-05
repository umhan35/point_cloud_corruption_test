#include <ros/ros.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>

void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& msg) {
    ROS_INFO_STREAM("callback");

    pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*msg, *pcl_cloud);
    pcl::io::savePCDFile("msg_" + std::to_string(ros::Time::now().toSec()) + ".pcd", *pcl_cloud);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "using_subscriber");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/head_camera/depth_downsample/points", 1, cloud_cb);

    ros::Rate r(6);
    while(ros::ok()) {
        ROS_INFO_STREAM("spinOnce...");
        ros::spinOnce();
        ROS_INFO_STREAM("sleep...");
        r.sleep();
    }

    return 0;
}