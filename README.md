# kitti_ros_publisher

## Description

An ROS Node to publish data from kitti datasets as ros messages.

## RoadMap

Now only publish velodyne points as sensor_msgs/PointCloud2. 

## ToDo

+ IMU data
+ Image data
+ tf

## Usage

```bash
cd your/path/to/catkin/workspace
git clone https://github.com/MagicianCH/kitti_ros_publisher.git
catkin build kitti_ros_publisher
```

## Dependencies

+ pcl_ros
+ sensor_msgs
