#include <ros/ros.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <ros/callback_queue.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "shutdown_after_1st_callback");

    ros::NodeHandle nh;

    ros::CallbackQueue cb_queue;
    nh.setCallbackQueue(&cb_queue);

    ros::Subscriber sub;

    boost::function<void(const sensor_msgs::PointCloud2::ConstPtr &)> callback =
            [&sub/*, &nh*/](const sensor_msgs::PointCloud2::ConstPtr &msg) {

                ROS_INFO_STREAM("lambda callback");

                pcl::io::savePCDFile("msg_" + std::to_string(ros::Time::now().toSec()) + ".pcd", *msg);

//                nh.shutdown();
//                ROS_INFO_STREAM("sub.shutdown();");
//                sub.shutdown();
            };

    sub = nh.subscribe<sensor_msgs::PointCloud2::ConstPtr>("/head_camera/depth_downsample/points", 1, callback);

    ros::Rate rate(10);
//    bool do_not_shutdown_pls = true;
    while (nh.ok() /*&& do_not_shutdown_pls*/) {
        rate.sleep();
        if (!cb_queue.isEmpty()) {
            cb_queue.callOne();
//            ROS_INFO_STREAM("nh.shutdown();");
//            nh.shutdown();

//            do_not_shutdown_pls = false;
        }
    }

    return 0;
}