/***********************************************************
 @Author: Chen Hao
 @Created Time : 2019-05-15 15:53:27
 @File Name: node.cpp
 @Description:
***********************************************************/
#include "kitti_ros_publisher/KittiPublisher.h"

int main(int argc, char**argv)
{
    ros::init(argc, argv, "kitti_ros_publisher");

    KittiPublisher kp;
    kp.runLoop();

    return 0;
}
