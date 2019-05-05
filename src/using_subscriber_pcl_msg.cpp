#include <ros/ros.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>

void cloud_cb(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& msg) {
    ROS_INFO_STREAM("callback");

    pcl::io::savePCDFile("pcl_cloud_" + std::to_string(ros::Time::now().toSec()) + ".pcd", *msg);
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