#include <ros/ros.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>

void cloud_cb(boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ> const>& msg) {
    ROS_INFO_STREAM("callback");

    pcl::io::savePCDFile("pcl_cloud_" + std::to_string(ros::Time::now().toSec()) + ".pcd", *msg);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "using_waitForMsg");

    ros::NodeHandle nh;

    ros::Rate r(6);
    while(ros::ok()) {
        ROS_INFO_STREAM("waitForMessage...");
        boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ> const> msg =
                ros::topic::waitForMessage<pcl::PointCloud<pcl::PointXYZ>>("/head_camera/depth_downsample/points");
        cloud_cb(msg);
        ROS_INFO_STREAM("sleep...");
        r.sleep();
    }
    return 0;
}