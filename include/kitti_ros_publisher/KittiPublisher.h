#ifndef  KITTI_PUBLISHER_H
#define  KITTI_PUBLISHER_H

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/transforms.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/point_operators.h>
#include <pcl/common/io.h>


class KittiPublisher
{
public:
    KittiPublisher();
    ~KittiPublisher() = default;

    void runLoop();
    void readKittiVLDBinFile(std::string &fn);

private:
    ros::NodeHandle nh_;
    ros::Publisher pc2_pub_;

    std::string vld_data_path_;
    int points_hz_;
};




#endif
