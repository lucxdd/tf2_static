#include "ros/ros.h"
#include"tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/Transform.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2/LinearMath/Quaternion.h"


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"static_pub");
    ros::NodeHandle nh;
    
    tf2_ros::StaticTransformBroadcaster pub;
    geometry_msgs::TransformStamped tfs;

    tfs.header.stamp = ros::Time::now();
    tfs.header.frame_id = "base_link"; // 相对坐标系中被参考的那个
    tfs.child_frame_id = "laser";   
    tfs.transform.translation.x = 1; 
    tfs.transform.translation.y = 1; 
    tfs.transform.translation.z = 1;

    tf2::Quaternion qtn;  //创建寺院书对象，向他设置欧拉角可以转换成寺院书
    qtn.setRPY(0,0,0);    // pi
    
    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();

    pub.sendTransform(tfs);

    ros::spin();

    return 0;
}