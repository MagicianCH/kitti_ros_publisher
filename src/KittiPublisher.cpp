/***********************************************************
 @Author: Chen Hao
 @Created Time : 2019-05-15 14:56:52
 @File Name: KittiPublisher.cpp
 @Description:
***********************************************************/

#include "kitti_ros_publisher/KittiPublisher.h"
#include <fstream>
#include <vector>
#include<iostream>
#include<string>
#include<dirent.h>
#include <algorithm>

void get_files(std::string dirname, std::vector<std::string> &v_f)
{
    DIR *dp;
    struct dirent *dirp;

    if((dp = opendir(dirname.c_str())) == NULL)
    {
        ROS_ERROR("Can't open "); 
    }
    while((dirp = readdir(dp)) != NULL)
    {
        std::string fn = dirp->d_name;
        if(fn != "." && fn != "..") {
            v_f.push_back(fn);
        }   
    }
    closedir(dp);

    std::sort(v_f.begin(), v_f.end());
}


KittiPublisher::KittiPublisher()
{
    ros::NodeHandle private_nh("~"); 
    if(!private_nh.getParam("vld_data_path", vld_data_path_)) {
        vld_data_path_ = "/home/chenhao/Datas/2011_09_30_drive_0020_sync/velodyne_points/data";
    }
    if(!private_nh.getParam("points_pub_hz", points_hz_)) {
        points_hz_ = 10;
    }
    pc2_pub_ = nh_.advertise<pcl::PointCloud<pcl::PointXYZ>>("kitti_points", 1, true);
}

void KittiPublisher::readKittiVLDBinFile(std::string &fn)
{
    std::string infile = vld_data_path_ + "/" + fn;
    std::fstream input(infile, std::ios::in|std::ios::binary); 
    if(!input.good()) {
        ROS_ERROR("Can not read file: %s", infile.c_str());
        return;
    }
    input.seekg(0, std::ios::beg);
    
    pcl::PointCloud<pcl::PointXYZI>::Ptr points(new pcl::PointCloud<pcl::PointXYZI>());

    for(int i = 0; input.good() && !input.eof(); ++i) {
        pcl::PointXYZI point;
        input.read((char *) &point.x, 3*sizeof(float));
        input.read((char *) &point.intensity, sizeof(float));
        points->push_back(point);
    }
    input.close();
    
    sensor_msgs::PointCloud2 pc_msg;
    pc_msg.header.frame_id = "velodyne";
    pc_msg.header.stamp = ros::Time::now();
    points->header = pcl_conversions::toPCL(pc_msg.header);
    pc2_pub_.publish(points);
}

void KittiPublisher::runLoop()
{
    ros::Rate rate(points_hz_);

    std::vector<std::string> files;
    get_files(vld_data_path_, files);
    std::cout << "size: " << files.size() << std::endl;

    std::vector<std::string>::iterator iter = files.begin();
    while(ros::ok() && iter++ != files.end()) {
        std::string tmp = *iter;
        readKittiVLDBinFile(tmp);
        rate.sleep();
    }
}
