#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <math.h>
#include "ros/ros.h"
#include "ihmc_msgs/ArmTrajectoryRosMessage.h"
#include "ihmc_msgs/NeckTrajectoryRosMessage.h"
#include "sensor_msgs/JointState.h"
#include "skeleton_tracker/user_IDs.h"
#include "tf2_msgs/TFMessage.h"
//#include <thread>         // std::this_thread::sleep_for
//#include <chrono>         // std::chrono::seconds
/*			struct timeval tp;
			gettimeofday(&tp, NULL);
			long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
			timestamps.push_back(ms);
			*/
#include <sstream>
#define PI 3.14159265
#define RIGHT 1
#define LEFT 0
#define XY 1
#define XZ 2
#define YZ 3

/**
 * This test out simple arm maneuver commands
 * Does not actually work for the first command
 */
class Point{
public:
	Point(double x_=0,double y_=0,double z_=0):x(x_),y(y_),z(z_),theta(0){}
	Point(double x_,double y_,double z_,double theta_):x(x_),y(y_),z(z_),theta(theta_){}
	double x,y,z,theta;
	bool operator==(const int i){
		if(x==i&&y==i&&z==i)
			return true;
		return false;
	}
};
int uId=100030;
bool PUBLISH=true;
double getAngle(double x,double y);
double getAngleBetween(Point a,Point b);
double getAngleInPlane(int planeIdentifier, Point a, Point b);
Point centerAtOrigin(bool lootAtRotated,int x,int y);
ihmc_msgs::ArmTrajectoryRosMessage moveArm(int side,double _1,double _2,double _3,double _4,double _5,double _6, double _7);
ihmc_msgs::NeckTrajectoryRosMessage moveHead(double _1,double _2,double _3);
sensor_msgs::JointState lastOut;
bool more=false;
int tracking =-1;
std::vector<Point> bodyHistory[15];
std::vector<long int> timestamps;
Point lastStats[15]={Point(0,0,0)};
Point rotated[15]={Point(0,0,0)};
std::string bodyParts[]={"head","left_elbow","left_foot","left_hand","left_hip","left_knee","left_shoulder","neck","right_elbow","right_foot","right_hand","right_hip","right_knee","right_shoulder","torso"};
void jointStateCallBack(sensor_msgs::JointState msg){
  lastOut=msg;
  //std::cout<<"msg recieved"<<std::endl;
}
void peopleCallBack(skeleton_tracker::user_IDs msg){
	if(msg.users.size()==0){
		tracking=-1;
		more=false;
	}
	else{
		tracking=msg.users[0];
	}
	//std::cout<<tracking<<std::endl;
}
int MsgCount=-1;
void TFCallBack(tf2_msgs::TFMessage msg){//this only supports 1 user and under ideal conditions
	/*TODO:
	 * Check for multiple people being tracked
	 * use data for lowest number -> peopleCallBack
	 * be able to track and number person
	 * better filter messages so they only come from tracker (done)
	 * */
	 
	//std::cout<<"newMSG"<<std::endl;
	for(int i=0;i<msg.transforms.size();i++){
		//std::cout<<"\ti: "<<i<<" Frame ID: "<<msg.transforms[i].header.frame_id<<" Child Frame ID: "<<msg.transforms[i].child_frame_id<<"\tx:"<<msg.transforms[i].transform.translation.x<<" y:"<<msg.transforms[i].transform.translation.y<<" z:"<<msg.transforms[i].transform.translation.z<<std::endl;
		if(!(tracking<1)){
			for(int i2=0;i2<15;i2++){
				std::ostringstream checking;
				checking<<"/tracker/user_"<<tracking<<"/"<<bodyParts[i2];
				//std::cout<<checking.str()<<std::endl;
				if(msg.transforms[i].child_frame_id==checking.str()){
					lastStats[i2].x=msg.transforms[i].transform.translation.x;
					lastStats[i2].y=msg.transforms[i].transform.translation.y;
					lastStats[i2].z=msg.transforms[i].transform.translation.z;
					//std::cout<<"updated "<<i2<<std::endl;
				}
			}
		}
		if(tracking==-1)
			for(int i2=0;i2<15;i2++){
				lastStats[i2].x=0;
				lastStats[i2].y=0;
				lastStats[i2].z=0;
			}
	}
}
int main(int argc, char **argv)
{	
	ros::init(argc, argv, "mirror");
	ros::NodeHandle n;
	ros::Publisher arm_controller;
	ros::Publisher head_controller;
	if(PUBLISH)
		ros::Subscriber joint_listener = n.subscribe("/ihmc_ros/valkyrie/output/joint_states", 1000, jointStateCallBack);
	ros::Subscriber transform_listener = n.subscribe("/tf", 1000, TFCallBack);
	ros::Subscriber people_listener = n.subscribe("/people", 1000, peopleCallBack);
	//if(PUBLISH)
		arm_controller = n.advertise<ihmc_msgs::ArmTrajectoryRosMessage>("/ihmc_ros/valkyrie/control/arm_trajectory", 1000);
		head_controller = n.advertise<ihmc_msgs::NeckTrajectoryRosMessage>("/ihmc_ros/valkyrie/control/neck_trajectory", 1000);
	ros::Rate loop_rate(6);
	double _delta=1000;
	while (ros::ok()){
		struct timeval tp;
		gettimeofday(&tp, NULL);
		long int start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		more=true;
		for(int i=0;i<15;i++){
			if(lastStats[i]==0)
				more=false;
		}
		if(!more){		
			ros::spinOnce();
			loop_rate.sleep();
			continue;
		}
		//print me some stuff
		for(int i=0;i<15;i++){
			if((i==-8||i==-10||i==-13||i==0)&&false)
				std::cout<<"\t"<<bodyParts[i]<<": \u0394x="<<lastStats[i].x-lastStats[i].x<<" \u0394y="<<lastStats[i].y-lastStats[i].y<<" \u0394z="<<lastStats[i].z-lastStats[i].z<<std::endl;
			if(i==0&&false)
				std::cout<<"\t"<<bodyParts[i]<<": x="<<lastStats[i].x<<": y="<<lastStats[i].y<<": z="<<lastStats[i].z<<std::endl;
			//std::cout<<"\t"<<bodyParts[i]<<": x="<<lastStats[i].x<<": y="<<lastStats[i].y<<": z="<<lastStats[i].z<<std::endl;
		}
		Point avg=Point((lastStats[13].x+lastStats[6].x)/2,(lastStats[13].y+lastStats[6].y)/2,(lastStats[13].z+lastStats[6].z)/2);
		double R=getAngleInPlane(XZ,centerAtOrigin(13,avg),Point(5,0,0));
		std::cout<<"R: "<<R<<std::endl;
		//LOOK AT RIGHT SIDE
		Point a=centerAtOrigin(false,8,13),b=centerAtOrigin(false,11,13);
		a.x=0;
		b.x=0;
		double shoulderRot2=getAngleBetween(a,b);
		double biceptRot2=getAngleBetween(centerAtOrigin(false,10,8),Point(0,1,0));
		//angle between hand-elbow and rightShoulder-elbow
		double elbowAngle2=getAngleBetween(centerAtOrigin(false,10,8),centerAtOrigin(false,13,8));
		//angle between elbow-rightShoulder and leftShoulder-rightShoulder
		double shoulderFlappy2=getAngleBetween(centerAtOrigin(false,8,13),centerAtOrigin(false,6,13));
		//map angles to values that Val likes
		//Shoulder Rotation
			if(lastStats[8].z<lastStats[11].z)
				shoulderRot2*=-1;
		//elbow
			elbowAngle2=(PI)-elbowAngle2;//(does not) map directly
		//Bicept rotation (actually better called upper arm rotation) DONE: renamed
		//TODO: fix when it rotates backwards past 0 degrees (low use case)
			biceptRot2-=(PI/2);//maps directly (lol no, i wish)
		//Shoulder flap
			if(centerAtOrigin(false,8,13).y<centerAtOrigin(false,6,13).y)
				shoulderFlappy2=(2*PI)-shoulderFlappy2;
			shoulderFlappy2-=PI;
		//std::cout<<"SHOULDER_ROTATE: "<<shoulderRot2*(180/PI)<<" ELBOW_ANGLE: "<<elbowAngle2*(180/PI)<<" BICEPT_ROTATE: "<<biceptRot2*(180/PI)<<" SHOULDER_FLAPPY: "<<shoulderFlappy2*(180/PI)<<std::endl;
		if(PUBLISH)//NEED TO ADD CODE TO moveArm to check bounds on all data points! -> DONE
			arm_controller.publish(moveArm(RIGHT,shoulderRot2,shoulderFlappy2,biceptRot2,elbowAngle2,0,0,0));
		ros::spinOnce();
		loop_rate.sleep();
		//NOW THE LEFT
		Point la=centerAtOrigin(false,1,6),lb=centerAtOrigin(false,4,6);
		la.x=0;
		lb.x=0;
		double lshoulderRot2=getAngleBetween(la,lb);
		double lbiceptRot2=getAngleBetween(centerAtOrigin(false,3,1),Point(0,1,0));
		//angle between hand-elbow and rightShoulder-elbow
		double lelbowAngle2=getAngleBetween(centerAtOrigin(false,3,1),centerAtOrigin(false,6,1));
		//angle between elbow-rightShoulder and leftShoulder-rightShoulder
		double lshoulderFlappy2=getAngleBetween(centerAtOrigin(false,1,6),centerAtOrigin(false,13,6));
		//map angles to values that Val likes
		//Shoulder Rotation
			if(lastStats[1].z<lastStats[4].z)
				lshoulderRot2*=-1;
		//elbow
			lelbowAngle2=(PI)-lelbowAngle2;//(does not) map directly
		//Bicept rotation (actually better called upper arm rotation) DONE: renamed
		//TODO: fix when it rotates backwards past 0 degrees (low use case)
			lbiceptRot2-=(PI/2);//maps directly (lol no, i wish)
		//Shoulder flap
			if(centerAtOrigin(false,1,6).y<centerAtOrigin(false,13,6).y)
				lshoulderFlappy2=(2*PI)-lshoulderFlappy2;
			lshoulderFlappy2-=PI;
		//std::cout<<"LEFT SHOULDER_ROTATE: "<<lshoulderRot2*(180/PI)<<" ELBOW_ANGLE: "<<lelbowAngle2*(180/PI)<<" BICEPT_ROTATE: "<<lbiceptRot2*(180/PI)<<" SHOULDER_FLAPPY: "<<lshoulderFlappy2*(180/PI)<<std::endl;
		if(PUBLISH)//NEED TO ADD CODE TO moveArm to check bounds on all data points! -> DONE
			arm_controller.publish(moveArm(LEFT,lshoulderRot2,lshoulderFlappy2,lbiceptRot2,lelbowAngle2,0,0,0));
		//0-7 6-7
		double headTilt=getAngleBetween(centerAtOrigin(false,0,7),centerAtOrigin(false,6,7));
		//double headTiltR=getAngleBetween(centerAtOrigin(false,0,13),centerAtOrigin(false,6,13));
		double abHTilt=headTilt-(90*(PI/180));
		abHTilt=(abHTilt<0?-1*abHTilt:abHTilt);
		//;if(abHTilt>(10*(PI/180)))
			head_controller.publish(moveHead(abHTilt,0,-1*abHTilt));
		ros::spinOnce();
		gettimeofday(&tp, NULL);
		long int end = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		//std::cout<<"HEAD_TILT: "<<headTilt*(180/PI)<<" AB_HEAD_TILT: "<<abHTilt*(180/PI)<<" Duration: "<<end-start<<std::endl;
		loop_rate.sleep();
	}
	//270=0 360=90  ???
  /*//*///6 left shoulder 8 elbow 10 hand 11 hip 13 shoulder
  //how do 1 and 3 map to human joints? -> DONE
  
  
  return 0;
}
Point centerAtOrigin(bool lootAtRotated, int p1, int p2){//p1 relative to p2 at the origin
	if(!lootAtRotated)
		return Point(lastStats[p1].x-lastStats[p2].x,lastStats[p1].y-lastStats[p2].y,lastStats[p1].z-lastStats[p2].z);
	else
		return Point(rotated[p1].x-rotated[p2].x,rotated[p1].y-rotated[p2].y,rotated[p1].z-rotated[p2].z);		
}
Point centerAtOrigin(int p1, Point p2){//p1 relative to p2 at the origin
	return Point(lastStats[p1].x-p2.x,lastStats[p1].y-p2.y,lastStats[p1].z-p2.z);	
}

void rotateInPlane(int planeIdentifier, double theta){
	double cosT=cos(theta),sinT=sin(theta);
	switch(planeIdentifier){
	case XY:
		for(int i=0;i<15;i++){
			rotated[i].x=cosT*lastStats[i].x+(-1*sinT)*lastStats[i].y;
			rotated[i].y=sinT*lastStats[i].x+(cosT)*lastStats[i].y;
			rotated[i].z=lastStats[i].z;
		}
		break;
	case XZ:
		for(int i=0;i<15;i++){
			rotated[i].x=cosT*lastStats[i].x+(-1*sinT)*lastStats[i].z;
			rotated[i].y=lastStats[i].y;
			rotated[i].z=sinT*lastStats[i].x+(cosT)*lastStats[i].z;
		}
		break;
	case YZ:
		for(int i=0;i<15;i++){
			rotated[i].x=lastStats[i].x;
			rotated[i].y=cosT*lastStats[i].y+(-1*sinT)*lastStats[i].z;
			rotated[i].z=sinT*lastStats[i].y+(cosT)*lastStats[i].z;
		}
		break;
	}
}
double getAngleBetween(Point a,Point b){
	//calulate dot product of a(dot)b
	//calculate |a|*|b|
	//cos-1(a(dot)b/(|a|*|b|))
	//std::cout<<a.x<<" "<<b.x<<" "<<a.y<<" "<<b.y<<" "<<a.z<<" "<<b.z<<std::endl;
	double AdotB=a.x*b.x+a.y*b.y+a.z*b.z;
	double magA=sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
	double magB=sqrt(b.x*b.x+b.y*b.y+b.z*b.z);
	double angle= acos(AdotB/(magA*magB));
	/*if(a.y<b.y)
		angle=(2*PI)-angle;*/
	return angle;
}
double getAngle(double x, double y){
	//std::cout<<x<<" "<<y<<std::endl;
	double ax=x,ay=y;
	if(x<0)
		ax=-1*x;
	if(y<0)
		ay=-1*y;
	double retAngle=0;
	if(x>0){
		if(y>0)
			retAngle=(atan(ay/ax)*180/PI);//Quad 1
		else
			retAngle=360-(atan(ay/ax)*180/PI);//Quad 4
	}
	else{
		if(y>0)
			retAngle=180-(atan(ay/ax)*180/PI);//Quad 2
		else
			retAngle=180+(atan(ay/ax)*180/PI);//Quad 3
	}
	if(retAngle<0) //wait a sec, this should be impossible...
		retAngle*=-1;
	return retAngle;
}
double getAngleInPlane(int planeIdentifier, Point a, Point b){
	double angle1=0,angle2=0;
	switch(planeIdentifier){
	case XY:
		angle1=getAngle(a.x,a.y);
		angle2=getAngle(b.x,b.y);
		break;
	case XZ:
		angle1=getAngle(a.x,a.z);
		angle2=getAngle(b.x,b.z);
		break;
	case YZ:
		angle1=getAngle(a.y,a.z);
		angle2=getAngle(b.y,b.z);
		break;
	}
	double retAngle=angle1-angle2;
	retAngle=(retAngle<0?retAngle*-1:retAngle);
	return retAngle;
}
ihmc_msgs::ArmTrajectoryRosMessage moveArm(int side, double _1,double _2,double _3,double _4,double _5,double _6, double _7){
	//these arrays are NOT zero indexed
	double high[8]={0,1.8,1.4,1.9,2.1,0,0,0};//don't have last 3 yet
	double low[8]={0,-2.5,-1.2,-1.9,0,0,0,0};//don't have last 3 yet (yes, the 4th value was calulated to zero)
	_1=(_1>high[1]?high[1]:_1);
	_2=(_2>high[2]?high[2]:_2);
	_3=(_3>high[3]?high[3]:_3);
	_4=(_4>high[4]?high[4]:_4);
	_5=(_5>high[5]?high[5]:_5);
	_6=(_6>high[6]?high[6]:_6);
	_7=(_7>high[7]?high[7]:_7);
	_1=(_1<low[1]?low[1]:_1);
	_2=(_2<low[2]?low[2]:_2);
	_3=(_3<low[3]?low[3]:_3);
	_4=(_4<low[4]?low[4]:_4);
	_5=(_5<low[5]?low[5]:_5);
	_6=(_6<low[6]?low[6]:_6);
	_7=(_7<low[7]?low[7]:_7);
	_2=(side==LEFT?_2*-1:_2);
	_4=(side==LEFT?_4*-1:_4);
	
	ihmc_msgs::ArmTrajectoryRosMessage msg;
	ihmc_msgs::OneDoFJointTrajectoryRosMessage n3;
	ihmc_msgs::TrajectoryPoint1DRosMessage n2;
	n2.time=0;
	n2.position=0;
	n2.velocity=.1;
	n3.trajectory_points.push_back(n2);
	n3.trajectory_points[0].position=_1;
	msg.joint_trajectory_messages.push_back(n3);
	n3.trajectory_points[0].position=_2;
	msg.joint_trajectory_messages.push_back(n3);
	n3.trajectory_points[0].position=_3;
	msg.joint_trajectory_messages.push_back(n3);
	n3.trajectory_points[0].position=_4;
	msg.joint_trajectory_messages.push_back(n3);
	n3.trajectory_points[0].position=_5;
	msg.joint_trajectory_messages.push_back(n3);
	n3.trajectory_points[0].position=_6;
	msg.joint_trajectory_messages.push_back(n3);
	n3.trajectory_points[0].position=_7;
	msg.joint_trajectory_messages.push_back(n3);
	msg.robot_side=side;
	msg.unique_id=uId++;
	return msg;
}

ihmc_msgs::NeckTrajectoryRosMessage moveHead(double _1,double _2,double _3){
	//these arrays are NOT zero indexed
	double high[4]={0,1.1,1,0};
	double low[4]={0,0,-1,-.8};
	_1=(_1>high[1]?high[1]:_1);
	_2=(_2>high[2]?high[2]:_2);
	_3=(_3>high[3]?high[3]:_3);
	_1=(_1<low[1]?low[1]:_1);
	_2=(_2<low[2]?low[2]:_2);
	_3=(_3<low[3]?low[3]:_3);
	ihmc_msgs::NeckTrajectoryRosMessage msg;
	ihmc_msgs::OneDoFJointTrajectoryRosMessage n3;
	ihmc_msgs::TrajectoryPoint1DRosMessage n2;
	n2.time=0;
	n2.position=0;
	n2.velocity=.5;
	n3.trajectory_points.push_back(n2);
	n3.trajectory_points[0].position=_1;
	msg.joint_trajectory_messages.push_back(n3);
	n3.trajectory_points[0].position=_2;
	msg.joint_trajectory_messages.push_back(n3);
	n3.trajectory_points[0].position=_3;
	msg.joint_trajectory_messages.push_back(n3);
	return msg;
}
