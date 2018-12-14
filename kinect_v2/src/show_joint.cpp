#include <ros/ros.h>
#include <string>
#include <cstdio>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/convert.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <kinect_v2/BodyJoints.h>
#include <iostream>

using namespace std;

const string get_key_name(int n);
void publishTransform(const kinect_v2::BodyJoints &user_i, int user_id, int j);

void callback_0(const kinect_v2::BodyJoints &user_0)
{
	for (int i = 0; i < 16; ++i)
		publishTransform(user_0, 0, i);
}

void callback_1(const kinect_v2::BodyJoints &user_1)
{
	for (int i = 0; i < 16; ++i)
		publishTransform(user_1, 1, i);
}

void callback_2(const kinect_v2::BodyJoints &user_2)
{
	for (int i = 0; i < 16; ++i)
		publishTransform(user_2, 2, i);
}

void callback_3(const kinect_v2::BodyJoints &user_3)
{
	for (int i = 0; i < 16; ++i)
		publishTransform(user_3, 3, i);
}

void callback_4(const kinect_v2::BodyJoints &user_4)
{
	for (int i = 0; i < 16; ++i)
		publishTransform(user_4, 4, i);
}

void callback_5(const kinect_v2::BodyJoints &user_5)
{
	for (int i = 0; i < 16; ++i)
		publishTransform(user_5, 5, i);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "skeleton_tracking");
	ros::NodeHandle n;
	ros::Subscriber sub_0 = n.subscribe("user_0", 1, &callback_0);
	ros::Subscriber sub_1 = n.subscribe("user_1", 1, &callback_1);
	ros::Subscriber sub_2 = n.subscribe("user_2", 1, &callback_2);
	ros::Subscriber sub_3 = n.subscribe("user_3", 1, &callback_3);
	ros::Subscriber sub_4 = n.subscribe("user_4", 1, &callback_4);
	ros::Subscriber sub_5 = n.subscribe("user_5", 1, &callback_5);
	ros::spin();

	return 0;
}

const string get_key_name(int n)
{
	switch (n)
	{
		case	0:return	"base_spine"; break;
		case	1:return	"neck"; break;
		case	2:return	"head"; break;
		case	3:return	"left_shoulder"; break;
		case	4:return	"left_elbow"; break;
		case	5:return	"left_hand"; break;
		case	6:return	"right_shoulder"; break;
		case	7:return	"right_elbow"; break;
		case	8:return	"right_hand"; break;
		case	9:return	"left_hip"; break;
		case	10:return	"left_knee"; break;
		case	11:return	"left_ankle"; break;
		case	12:return	"right_hip"; break;
		case	13:return	"right_knee"; break;
		case	14:return	"right_ankle"; break;
		case	15:return	"shoulder_spine"; break;
	}
}

void publishTransform(const kinect_v2::BodyJoints &user_i, int user_id, int joint_id)
{
	static tf2_ros::TransformBroadcaster br;
	geometry_msgs::TransformStamped transformStamped;

	transformStamped.header.stamp = ros::Time::now();
	transformStamped.header.frame_id = "kinect_v2";
	transformStamped.child_frame_id = get_key_name(joint_id) + "_" + to_string(user_id);
	transformStamped.transform.translation.x = user_i.joints[joint_id].position.x;
	transformStamped.transform.translation.y = user_i.joints[joint_id].position.y;
	transformStamped.transform.translation.z = user_i.joints[joint_id].position.z;
	transformStamped.transform.rotation.w = user_i.joints[joint_id].orientation.w;
	transformStamped.transform.rotation.x = user_i.joints[joint_id].orientation.x;
	transformStamped.transform.rotation.y = user_i.joints[joint_id].orientation.y;
	transformStamped.transform.rotation.z = user_i.joints[joint_id].orientation.z;

	br.sendTransform(transformStamped);
}