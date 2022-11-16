#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"static_sub");
    ros::NodeHandle nh;
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listrner(buffer);  //订阅到消息存入buffer

    geometry_msgs::PointStamped ps;
    ps.header.frame_id = "laser";
    ps.header.stamp = ros::Time::now();
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;
    ros::Duration(2).sleep();
    ros::Rate rate(10);
    while (ros::ok())
    {
        // 将ps转换成小车坐标系
        geometry_msgs::PointStamped ps_out;
        ps_out = buffer.transform(ps,"base_link");  //需要转换的坐标点，和目标的坐标系  返回之：输出的坐标点

        ROS_INFO("转换后的作标志： （%.2f,%.2f,%.2f）,参考的坐标系: %s",
                    ps_out.point.x,
                    ps_out.point.y,
                    ps_out.point.z,
                    ps_out.header.frame_id.c_str());
        
        rate.sleep();
        ros::spinOnce();
    }
    

    return 0;
}
