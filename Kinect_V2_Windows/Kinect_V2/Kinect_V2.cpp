#include "stdafx.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "ros.h"
#include <windows.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseArray.h>
#include <kinect_v2/BodyJoints.h>

// Kinect for Windows SDK Header
#include <Kinect.h>

using namespace std;
const   string  get_name(int n);	//This function is to get the name of joint by jointcount
void	reset_body(kinect_v2::BodyJoints &body);	//This function is to reset the joints value of untracked persons
void	reset_joint(geometry_msgs::Pose &joint);    //This function is to reset the single untracked joint
kinect_v2::BodyJoints& get_body(int n, kinect_v2::BodyJoints &person_0, kinect_v2::BodyJoints &person_1, kinect_v2::BodyJoints &person_2,
	kinect_v2::BodyJoints &person_3, kinect_v2::BodyJoints &person_4, kinect_v2::BodyJoints &person_5);	//This function is to return the body data given its user_id

int main(int argc, _TCHAR* argv[])
{
	// Get ready to read Kinect data
	IKinectSensor   * mySensor = nullptr;
	GetDefaultKinectSensor(&mySensor);
	mySensor->Open();

	int myBodyCount = 0;
	IBodyFrameSource    * myBodySource = nullptr;
	IBodyFrameReader    * myBodyReader = nullptr;
	mySensor->get_BodyFrameSource(&myBodySource);
	myBodySource->OpenReader(&myBodyReader);
	myBodySource->get_BodyCount(&myBodyCount);

	IBodyFrame  * myBodyFrame = nullptr;

	// Get ready to start ROS
	ros::NodeHandle nh;
	char master_uri[] = "192.168.0.104";
	char *ros_master = master_uri;

	cout << "Connecting to server at\n" << ros_master << endl;
	nh.initNode(ros_master);

	cout << "Advertising six persons' joints message\n" << endl;
	kinect_v2::BodyJoints body_0, body_1, body_2, body_3, body_4, body_5;
	ros::Publisher body_0_pub("user_0", &body_0);
	ros::Publisher body_1_pub("user_1", &body_1);
	ros::Publisher body_2_pub("user_2", &body_2);
	ros::Publisher body_3_pub("user_3", &body_3);
	ros::Publisher body_4_pub("user_4", &body_4);
	ros::Publisher body_5_pub("user_5", &body_5);
	nh.advertise(body_0_pub);
	nh.advertise(body_1_pub);
	nh.advertise(body_2_pub);
	nh.advertise(body_3_pub);
	nh.advertise(body_4_pub);
	nh.advertise(body_5_pub);

	int track_id = 0;

	cout << "Go robot go!\n" << endl;

	// Loop start
	while (1)
	{
		// get joints data from Kinect
		while (myBodyReader->AcquireLatestFrame(&myBodyFrame) != S_OK);

		int myBodyCount = 0;
		IBody   ** bodyArr = nullptr;
		myBodySource->get_BodyCount(&myBodyCount);
		bodyArr = new IBody *[myBodyCount];
		for (int i = 0; i < myBodyCount; i++)   //Initialize bodyArr
			bodyArr[i] = nullptr;

		myBodyFrame->GetAndRefreshBodyData(myBodyCount, bodyArr);
		for (int i = 0; i < myBodyCount; i++)   //Traverse all 6 person
		{
			get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).user_id = i;
			BOOLEAN     result = false;
			if (bodyArr[i]->get_IsTracked(&result) == S_OK && result)   //Judge whether the person get tracked
			{
				get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).tracked = "YES";
				cout << "Body " << i << " tracked!" << endl;
				track_id = i;
				int count = 0;
				int tracked_count = 0;
				Joint   jointArr[JointType_Count];
				JointOrientation	orientationArr[JointType_Count];
				bodyArr[i]->GetJoints(JointType_Count, jointArr);    //Get position info of joints
				bodyArr[i]->GetJointOrientations(JointType_Count, orientationArr);    //Get orientation info of joints
				for (int j = 0; j < JointType_Count; j++)
				{
					string  joint_name = get_name(jointArr[j].JointType);   //Get the name of joint
					if (joint_name != "NULL")   //output joint info
					{
						if (jointArr[j].TrackingState == TrackingState_Tracked) //Judge the joints whether get tracked
						{
							++tracked_count;
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].position.x = jointArr[j].Position.X;
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].position.y = jointArr[j].Position.Y;
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].position.z = jointArr[j].Position.Z;
							
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].orientation.w = orientationArr[j].Orientation.w;
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].orientation.x = orientationArr[j].Orientation.x;
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].orientation.y = orientationArr[j].Orientation.y;
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].orientation.z = orientationArr[j].Orientation.z;
						}
						else
							reset_joint(get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count]);
						if (joint_name == "head")	// joint "head" doesn't have orientation feature， so just set it to default orientation
						{
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].orientation.w = 1;
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].orientation.x = 0;
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].orientation.y = 0;
							get_body(i, body_0, body_1, body_2, body_3, body_4, body_5).joints[count].orientation.z = 0;
						}
						++count;
					}
				}
				cout << tracked_count << " joints tracked for the " << i << "th person." << endl;
			}
			else
				reset_body(get_body(i, body_0, body_1, body_2, body_3, body_4, body_5));
		}
		myBodyFrame->Release();
		delete[] bodyArr;
		/*
		switch (track_id)
		{
		case	0:body_0_pub.publish(&body_0); break;
		case	1:body_1_pub.publish(&body_1); break;
		case	2:body_2_pub.publish(&body_2); break;
		case	3:body_3_pub.publish(&body_3); break;
		case	4:body_4_pub.publish(&body_4); break;
		case	5:body_5_pub.publish(&body_5); break;
		}
		*/
		
		body_0_pub.publish(&body_0);
		body_1_pub.publish(&body_1);
		body_2_pub.publish(&body_2);
		body_3_pub.publish(&body_3);
		body_4_pub.publish(&body_4);
		body_5_pub.publish(&body_5);
		
		Sleep(50);

		nh.spinOnce();
	}
	myBodyReader->Release();
	myBodySource->Release();
	mySensor->Close();
	mySensor->Release();

	printf("All done!\n");
	return 0;
}

const   string  get_name(int n)		// only remain key 16 joints in consideration of the limitation on message size
{
	switch (n)
	{
	case	0:return	"base_spine"; break;
	case    2:return    "neck"; break;
	case    3:return    "head"; break;
	case    4:return    "left_shoulder"; break;
	case	5:return	"left_elbow"; break;
	case    7:return    "left_hand"; break;
	case    8:return    "right_shoulder"; break;
	case	9:return	"right_elbow"; break;
	case    11:return   "right_hand"; break;
	case	12:return	"left_hip"; break;
	case	13:return	"left_knee"; break;
	case	14:return	"left_ankle"; break;
	case	16:return	"right_hip"; break;
	case	17:return	"right_knee"; break;
	case	18:return	"right_ankle"; break;
	case	20:return	"shoulder_spine"; break;
	default:return "NULL";
	}
}

kinect_v2::BodyJoints& get_body(int n, kinect_v2::BodyJoints &person_0, kinect_v2::BodyJoints &person_1, kinect_v2::BodyJoints &person_2,
	kinect_v2::BodyJoints &person_3, kinect_v2::BodyJoints &person_4, kinect_v2::BodyJoints &person_5)
{
	switch (n)
	{
	case	0:	return	person_0; break;
	case	1:	return	person_1; break;
	case	2:	return	person_2; break;
	case	3:	return	person_3; break;
	case	4:	return	person_4; break;
	case	5:	return	person_5; break;
	}
}

void reset_body(kinect_v2::BodyJoints &body)
{
	body.tracked = "NO";
	geometry_msgs::Pose *p = body.joints;
	for (int i = 0; i < sizeof(body.joints) / sizeof(geometry_msgs::Pose); ++i)
	{
		// string name = get_name(i);
		// const char *joint_name = name.c_str();
		p->position.x = 0;
		p->position.y = 0;
		p->position.z = 0;
		p->orientation.w = 1;
		p->orientation.x = 0;
		p->orientation.y = 0;
		p->orientation.z = 0;
		++p;
	}
}

void reset_joint(geometry_msgs::Pose &joint)
{
	joint.position.x = 0;
	joint.position.y = 0;
	joint.position.z = 0;
	joint.orientation.w = 1;
	joint.orientation.x = 0;
	joint.orientation.y = 0;
	joint.orientation.z = 0;
}