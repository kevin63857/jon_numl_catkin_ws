/*mirror.cpp
	This file really should just be publishers and subscribers.
	No real calculations should be done here, that should all be left up to the body state object
	Fine, this file can also have the renderer for the oculus
  */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../include/bodyState.hpp"
#include "../include/mirrorGUI.hpp"
#include "ros/ros.h"
#include "ihmc_msgs/ArmTrajectoryRosMessage.h"
#include "ihmc_msgs/NeckTrajectoryRosMessage.h"
#include "ihmc_msgs/PelvisHeightTrajectoryRosMessage.h"
#include "ihmc_msgs/ChestTrajectoryRosMessage.h"
#include "ihmc_msgs/SO3TrajectoryPointRosMessage.h"
#include "ihmc_msgs/GoHomeRosMessage.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/Int8.h"
#include "sensor_msgs/JointState.h"
#include "sensor_msgs/CompressedImage.h"
#include "skeleton_tracker/user_IDs.h"
#include "myo_raw/IMUData.h"
#include "myo_raw/Gesture.h"
#include "tf2_msgs/TFMessage.h"
#include <sstream>

ihmc_msgs::ArmTrajectoryRosMessage moveArm(int side,std::vector<double> angles,bool record);
ihmc_msgs::NeckTrajectoryRosMessage moveHead(std::vector<double> angles,bool record);
ihmc_msgs::ChestTrajectoryRosMessage moveChest(std::vector<double> angles,bool record);
ihmc_msgs::PelvisHeightTrajectoryRosMessage movePelvisHeight(double angle,bool record);
ihmc_msgs::ArmTrajectoryRosMessage moveArm(int side,std::vector<double> angles){return moveArm(side,angles,true);}
ihmc_msgs::NeckTrajectoryRosMessage moveHead(std::vector<double> angles){return moveHead(angles,true);}
ihmc_msgs::ChestTrajectoryRosMessage moveChest(std::vector<double> angles){return moveChest(angles,true);}
ihmc_msgs::PelvisHeightTrajectoryRosMessage movePelvisHeight(double angle){return movePelvisHeight(angle,true);}
void leftEyeCallBack(sensor_msgs::CompressedImage msg);
void rightEyeCallBack(sensor_msgs::CompressedImage msg);
void jointStateCallBack(sensor_msgs::JointState msg);
void peopleCallBack(skeleton_tracker::user_IDs msg);
void myoIMUCallBack(myo_raw::IMUData msg);
void myoGestureCallBack(myo_raw::Gesture msg);
void myoOnboardGestureCallBack(std_msgs::Int8 msg);
void TFCallBack(tf2_msgs::TFMessage msg);
void updateGUI();
void pollEventsGUI();

int uId=1;
BodyState stateTracker;
sensor_msgs::JointState lastOut;
sensor_msgs::CompressedImage lastLeftEye;
sensor_msgs::CompressedImage lastRightEye;
bool more=false;
bool justChanged=false;
int tracking =-1;
double moveSpeedOverRide=-1;
sf::RenderWindow GUIwindow(sf::VideoMode(1000, 950), "Atleast it's not ui_builder");
GUI gui;


int main(int argc, char **argv)
{
	//So, for some odd reason involving the initialization of static non-copyable data, i can not get GUI to hold it's own RenderWindow
	//So i'm going to bite the bullet and just do it here in this class... :P
	gui.init();

	//Create my BodyState tracker
	stateTracker=BodyState();

	//Set up some ROS stuff
	ros::init(argc, argv, "mirror");
	ros::NodeHandle n;

	//First my subscribers
	ros::Subscriber myoIMU_listener = n.subscribe("/myo/imu",1000, myoIMUCallBack);
	ros::Subscriber myoGesture_listener = n.subscribe("/myo/gesture",1000, myoGestureCallBack);
	ros::Subscriber myoOnboardGesture_listener = n.subscribe("/myo/onboardGesture",1000, myoOnboardGestureCallBack);
	ros::Subscriber left_eye_watcher = n.subscribe("/multisense/left/image_rect/compressed",1000, leftEyeCallBack);
	ros::Subscriber right_eye_watcher = n.subscribe("/multisense/right/image_rect/compressed",1000, rightEyeCallBack);
	ros::Subscriber joint_listener = n.subscribe("/ihmc_ros/valkyrie/output/joint_states", 1000, jointStateCallBack);
	ros::Subscriber transform_listener = n.subscribe("/tf", 1000, TFCallBack);
	ros::Subscriber people_listener = n.subscribe("/people", 1000, peopleCallBack);

	//Now my publishers
	ros::Publisher arm_controller = n.advertise<ihmc_msgs::ArmTrajectoryRosMessage>("/ihmc_ros/valkyrie/control/arm_trajectory", 1000);
	ros::Publisher neck_controller = n.advertise<ihmc_msgs::NeckTrajectoryRosMessage>("/ihmc_ros/valkyrie/control/neck_trajectory", 1000);
	ros::Publisher pelvis_height_controller = n.advertise<ihmc_msgs::PelvisHeightTrajectoryRosMessage>("/ihmc_ros/valkyrie/control/pelvis_height_trajectory", 1000);
	ros::Publisher chest_controller = n.advertise<ihmc_msgs::ChestTrajectoryRosMessage>("/ihmc_ros/valkyrie/control/chest_trajectory", 1000);
	ros::Publisher go_home_pub = n.advertise<ihmc_msgs::GoHomeRosMessage>("/ihmc_ros/valkyrie/control/go_home",1000);

	//Some SFML stufsf::RenderWindow windowf
	sf::RenderWindow window;
	if(gui.isOcculusOn){
		sf::RenderWindow window(sf::VideoMode(2248, 544), "SFML works!");
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);
	}
	//Now the primary loop
	ros::Rate loop_rate(6);
	ihmc_msgs::GoHomeRosMessage goHomeMsg;
	goHomeMsg.trajectory_time=3;
	goHomeMsg.unique_id=14;
	long int end, start;
	while (ros::ok()){
		struct timeval tp;
		gettimeofday(&tp, NULL);
		long int start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		//std::cout<<tracking<<td::endl;
		//Some more SFML stuff
		if(GUIwindow.isOpen()){
			//TODO:add in some human data gathering and print out human position and robot position data
			//Also, add a table for Myo stuff
			pollEventsGUI();
			updateGUI();
		}
		//std::cout<<lastLeftEye.height<<" "<<lastLeftEye.width<<" "<<lastLeftEye.encoding<<" "<<lastLeftEye.step<<" "<<lastLeftEye.data.size()<<" "<<1024*544*3<<std::endl;
		if(gui.isOcculusOn && window.isOpen() && lastLeftEye.data.size()!=0 && lastRightEye.data.size()!=0){
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			sf::Uint8* pixels = new sf::Uint8[2248 * 544 * 4];
			sf::Image image,imageL,imageR;
			sf::Uint8* Ldata=new sf::Uint8[(size_t)lastLeftEye.data.size()];
			sf::Uint8* Rdata=new sf::Uint8[(size_t)lastRightEye.data.size()];
			for(int i=0;i<(size_t)lastLeftEye.data.size();i++){
				Ldata[i]=lastLeftEye.data[i];
			}
			for(int i=0;i<(size_t)lastRightEye.data.size();i++){
				Rdata[i]=lastRightEye.data[i];
			}
			imageL.loadFromMemory(Ldata,(size_t)lastLeftEye.data.size());
			imageR.loadFromMemory(Rdata,(size_t)lastRightEye.data.size());
			delete Ldata;
			delete Rdata;
			if(imageL.getSize().x!=imageR.getSize().x || imageL.getSize().y!=imageR.getSize().y)
				std::cout<<"imageL:("<<imageL.getSize().x<<","<<imageL.getSize().y<<") imageR:("<<imageR.getSize().x<<","<<imageR.getSize().y<<")"<<std::endl;
			sf::Texture texture;
			int max_x=imageL.getSize().x;
			int max_y=imageL.getSize().y;
			for(int y = 0; y <max_y; y++)
			{
				for(int x = 0; x < max_x; x++)
				{
					pixels[(y*(2*max_x+200)+x)*4]	 = imageL.getPixelsPtr()[((max_y-y)*max_x+x)*4]; // R?
					pixels[(y*(2*max_x+200)+x)*4 + 1] = imageL.getPixelsPtr()[((max_y-y)*max_x+x)*4+1]; // G?
					pixels[(y*(2*max_x+200)+x)*4 + 2] = imageL.getPixelsPtr()[((max_y-y)*max_x+x)*4+2]; // B?
					pixels[(y*(2*max_x+200)+x)*4 + 3] = 255; // A?
				}
				for(int x=1024;x<1224;x++){
					pixels[(y*(2*max_x+200)+x)*4]	 = 0; // R?
					pixels[(y*(2*max_x+200)+x)*4 + 1] = 0; // G?
					pixels[(y*(2*max_x+200)+x)*4 + 2] = 0; // B?
					pixels[(y*(2*max_x+200)+x)*4 + 3] = 255; // A?
				}
				for(int x = (max_x+200); x < (2*max_x+200); x++)
				{
					pixels[(y*(2*max_x+200)+x)*4]	 = imageR.getPixelsPtr()[((max_y-y)*max_x+x-(max_x+200))*4]; // R?
					pixels[(y*(2*max_x+200)+x)*4 + 1] = imageR.getPixelsPtr()[((max_y-y)*max_x+x-(max_x+200))*4+1]; // G?
					pixels[(y*(2*max_x+200)+x)*4 + 2] = imageR.getPixelsPtr()[((max_y-y)*max_x+x-(max_x+200))*4+2]; // B?
					pixels[(y*(2*max_x+200)+x)*4 + 3] = 255; // A?
				}
			}
			window.clear();
			image.create(2248, 544, pixels);
			texture.create(2248, 544);
			texture.update(image);
			sf::Sprite sprite;
			sprite.setTexture(texture);
			window.draw(sprite);
			window.display();
			delete pixels;
		}
		if(gui.goHomeCount==12){
			goHomeMsg.body_part=0;
			goHomeMsg.robot_side=0;
			go_home_pub.publish(goHomeMsg);
			std::cout<<"just published goHome LEFT_ARM"<<std::endl;
			for(int i=0;i<6;i++){
				ros::spinOnce();
				loop_rate.sleep();
			}
			goHomeMsg.robot_side=1;
			go_home_pub.publish(goHomeMsg);
			std::cout<<"just published goHome RIGHT_ARM"<<std::endl;
			for(int i=0;i<6;i++){
				ros::spinOnce();
				loop_rate.sleep();
			}
			goHomeMsg.body_part=1;
			go_home_pub.publish(goHomeMsg);
			std::cout<<"just published goHome TORSO"<<std::endl;
			for(int i=0;i<6;i++){
				ros::spinOnce();
				loop_rate.sleep();
			}
			goHomeMsg.body_part=2;
			go_home_pub.publish(goHomeMsg);
			std::cout<<"just published goHome PELVIS"<<std::endl;
			gui.startGoingHome=false;
			gui.goHomeCount--;
			ros::spinOnce();
			loop_rate.sleep();
			continue;
			/*
			moveSpeedOverRide=3;
			arm_controller.publish(moveArm(JRIGHT,stateTracker.getArmHomeAngles()));
			arm_controller.publish(moveArm(JLEFT,stateTracker.getArmHomeAngles()));
			chest_controller.publish(moveChest(stateTracker.getChestHomeAngles()));
			neck_controller.publish(moveHead(stateTracker.getNeckHomeAngles()));
			pelvis_height_controller.publish(movePelvisHeight(stateTracker.getPelvisHeightHomeAngles()));
			moveSpeedOverRide=-1;*/
		}
		if(!more || justChanged || (gui.goHomeCount>0 && gui.goHomeCount<12)){
			//std::cout<<gui.goHomeCount<<" "<<more<<" "<<justChanged<<std::endl;
			if(justChanged && more)
				justChanged=false;
			/*
			ihmc_msgs::GoHomeRosMessage msg;
			msg.trajectory_time=3;
			msg.unique_id=5;
			go_home_pub.publish(msg);
			msg.robot_side=1;
			go_home_pub.publish(msg);*/
			if(gui.goHomeCount>0)
				gui.goHomeCount--;
			ros::spinOnce();
			loop_rate.sleep();
			continue;
		}
		std::vector<double> out;
		out.push_back((tp.tv_sec * 1000 + tp.tv_usec / 1000)-end);//oh wow, this is terrible programming practice... dang man
		if(end!=0)
			gui.record("*: ",out);

		//gui.gesture==0 acts as an unlock feature
		if(gui.isRightArmOn && gui.gesture==1)
			arm_controller.publish(moveArm(JRIGHT,stateTracker.getRightArmAngles()));
		else if(gui.isRightArmOn && gui.gesture!=1 && false){
			moveSpeedOverRide=3;
			arm_controller.publish(moveArm(JRIGHT,stateTracker.getArmHomeAngles()));
			moveSpeedOverRide=-1;
			moveArm(JRIGHT,stateTracker.getRightArmAngles(),false);
		}

		if(gui.isLeftArmOn && gui.gesture==1)
			arm_controller.publish(moveArm(JLEFT,stateTracker.getLeftArmAngles()));
		else if(gui.isLeftArmOn && gui.gesture!=1 && false){
			moveSpeedOverRide=3;
			arm_controller.publish(moveArm(JLEFT,stateTracker.getArmHomeAngles()));
			moveSpeedOverRide=-1;
			//moveArm(JLEFT,stateTracker.getLeftArmAngles(),false);
		}
		if(gui.isChestOn && gui.gesture==1)
			chest_controller.publish(moveChest(stateTracker.getChestAngles()));
		else if(gui.isChestOn && gui.gesture!=1 && false){
			moveSpeedOverRide=3;
			chest_controller.publish(moveChest(stateTracker.getChestHomeAngles()));
			moveSpeedOverRide=-1;
			//moveChest(stateTracker.getChestAngles(),false);
		}
		if(gui.isHeadOn && gui.gesture==1)
			neck_controller.publish(moveHead(stateTracker.getNeckAngles()));
		else if(gui.isHeadOn && gui.gesture!=1 && false){
			moveSpeedOverRide=3;
			neck_controller.publish(moveHead(stateTracker.getNeckHomeAngles()));
			moveSpeedOverRide=-1;
			//moveHead(stateTracker.getNeckAngles(),false);
		}
		if(gui.isPelvisOn && gui.gesture==1)
			pelvis_height_controller.publish(movePelvisHeight(stateTracker.getStandingHeight()));
		else if(gui.isPelvisOn && gui.gesture!=1 && false){
			moveSpeedOverRide=3;
			pelvis_height_controller.publish(movePelvisHeight(stateTracker.getPelvisHeightHomeAngles()));
			moveSpeedOverRide=-1;
			//movePelvisHeight(stateTracker.getStandingHeight(),false);
		}

		ros::spinOnce();
		gettimeofday(&tp, NULL);
		long int start2 = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		loop_rate.sleep();
		gettimeofday(&tp, NULL);
		end = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		std::cout<<end-start2<<std::endl;
	}
	go_home_pub.publish(goHomeMsg);
	goHomeMsg.robot_side=1;
	go_home_pub.publish(goHomeMsg);
	return 0;
}
/*
Graphics methods
*/
void pollEventsGUI(){
	sf::Event event;
	while (GUIwindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			GUIwindow.close();
		if(event.type == sf::Event::MouseButtonPressed)
			gui.mouseClicked(event.mouseButton.x,event.mouseButton.y);
	}
}
void updateGUI(){
	gui.updateButtonStates();
	GUIwindow.clear();
	if(gui.areWeRecording){
		struct timeval tp;
		gettimeofday(&tp, NULL);
		std::ostringstream doubleToString;
		doubleToString<<"Start/Stop Recording "<<-1*(gui.startTime/1000-tp.tv_sec)<<"."<<tp.tv_usec / 1000;
		gui.buttons[9].textContent.setString(doubleToString.str());
		gui.buttons[9].textContent.setColor(sf::Color(0,0,0,255));
	}
	else{
		gui.buttons[9].textContent.setString("Start Recording");
		gui.buttons[9].textContent.setColor(sf::Color(255,255,255,255));
	}
	for(int i=0;i<gui.lines.size();i++){
		GUIwindow.draw(gui.lines[i]);
	}
	for(int i=0;i<gui.words.size();i++){
		GUIwindow.draw(gui.words[i]);
	}
	for(int i=0;i<gui.buttons.size();i++){
		GUIwindow.draw(gui.buttons[i].shapeContent);
		GUIwindow.draw(gui.buttons[i].textContent);
	}
	sf::Text textContent;
	textContent.setFont(gui.font);
	textContent.setCharacterSize(15);
	textContent.setColor(sf::Color(0,0,0,255));
	for(int i=0;i<33;i++){
		std::ostringstream doubleToString;
		if(gui.robotPositions[i]<.0005 && gui.robotPositions[i]>-.0005)
			doubleToString<<"BASICALLY ZERO";
		else if(gui.robotPositions[i]!=-1)
			doubleToString<<gui.robotPositions[i];
		else
			doubleToString<<"NULL";
		textContent.setString(doubleToString.str());
	    textContent.setPosition(850,65+25*i);
		GUIwindow.draw(textContent);
	}
	for(int i=0;i<33;i++){
		std::ostringstream doubleToString;
		if(gui.humanPositions[i]!=-1)
			doubleToString<<gui.humanPositions[i];
		else
			doubleToString<<"NULL";
		textContent.setString(doubleToString.str());
	    textContent.setPosition(725,65+25*i);
		GUIwindow.draw(textContent);
	}
	for(int i=0;i<3;i++){
		std::ostringstream doubleToString;
		if(gui.myo_orientation[i]!=-1)
			doubleToString<<gui.myo_orientation[i];
		else
			doubleToString<<"NULL";
		textContent.setString(doubleToString.str());
			textContent.setPosition(35+123*i,700);
		GUIwindow.draw(textContent);
	}
	std::ostringstream doubleToString;
	doubleToString<<"HUMAN STANDING HEIGHT: "<<gui.standingHeight;
	textContent.setString(doubleToString.str());
	textContent.setPosition(500,900);
	textContent.setCharacterSize(20);
	GUIwindow.draw(textContent);
	std::ostringstream gestureBuilder;
	gestureBuilder<<"Myo_Gesture: "<<gestureNames[gui.gesture];
	textContent.setString(gestureBuilder.str());
	textContent.setPosition(30,740);
	textContent.setCharacterSize(20);
	GUIwindow.draw(textContent);
	//std::cout<<"Finished Drawing"<<std::endl;
	GUIwindow.display();
}

/*
 Subscriber callback method implementations *yay*
 */

 //['leftHipYaw', 'leftHipRoll', 'leftHipPitch', 'leftKneePitch', 'leftAnklePitch', 'leftAnkleRoll', 'rightHipYaw', 'rightHipRoll', 'rightHipPitch', 'rightKneePitch', 'rightAnklePitch', 'rightAnkleRoll', 'torsoYaw', 'torsoPitch', 'torsoRoll', 'leftShoulderPitch', 'leftShoulderRoll', 'leftShoulderYaw', 'leftElbowPitch', 'leftForearmYaw', 'leftWristRoll', 'leftWristPitch', 'lowerNeckPitch', 'neckYaw', 'upperNeckPitch', 'hokuyo_joint', 'rightShoulderPitch', 'rightShoulderRoll', 'rightShoulderYaw', 'rightElbowPitch', 'rightForearmYaw', 'rightWristRoll', 'rightWristPitch']

 void myoIMUCallBack(myo_raw::IMUData msg){
	 gui.myo_orientation[0]=msg.orientation.x;
	 gui.myo_orientation[1]=msg.orientation.y;
	 gui.myo_orientation[2]=msg.orientation.z;
 }
 void myoGestureCallBack(myo_raw::Gesture msg){
	 //std::cout<<"MYO GESTURE:"<<msg.pose_number<<std::endl;
	 //gui.gesture=msg.pose_number;
 }

 void myoOnboardGestureCallBack(std_msgs::Int8 msg){
	 gui.gesture=msg.data;
	 gui.doButtonStuff(-1);
 }

void jointStateCallBack(sensor_msgs::JointState msg){
	lastOut=msg;
	for(int i=0;i<33;i++)
		gui.robotPositions[i]=msg.position[mapping[i]];
}

void leftEyeCallBack(sensor_msgs::CompressedImage msg){
	lastLeftEye=msg;
}
void rightEyeCallBack(sensor_msgs::CompressedImage msg){
	lastRightEye=msg;
}

void peopleCallBack(skeleton_tracker::user_IDs msg){
	if(msg.users.size()==0){
		tracking=-1;
		more=false;
	}
	else{
		tracking=msg.users[0];
	}
}
void TFCallBack(tf2_msgs::TFMessage msg){
	for(int i=0;i<msg.transforms.size();i++){
		if(!(tracking<1)){
			for(int i2=0;i2<15;i2++){
				std::ostringstream checking;
				checking<<"/tracker/user_"<<tracking<<"/"<<bodyParts[i2];
				if(msg.transforms[i].child_frame_id==checking.str()){
					stateTracker.updateSkeletonData(i2, msg.transforms[i].transform.translation.x, msg.transforms[i].transform.translation.y, msg.transforms[i].transform.translation.z);
					//std::cout<<"Recieved good data "<<i2<<std::endl;
				}
			}
		}
		more=(tracking==-1?false:true);
		if(!more)
			justChanged=true;
	}
}

/*
 These methods need to be somewhere, I'm just not sure where, so they go here:
 */

//This method will take in all the joint measurements from the skeleton, truncate them so that valkyrie likes them and package them into a message to be published
ihmc_msgs::ArmTrajectoryRosMessage moveArm(int side,std::vector<double> angles,bool record){//it works, trust me
	//these arrays ARE zero indexed
	double high[7]={1.8,1.4,1.9,2.1,0,0,0};//don't have last 3 yet
	double low[7]={-2.5,-1.2,-1.9,0,0,0,0};//don't have last 3 yet (yes, the 4th value was calulated to zero)
	ihmc_msgs::ArmTrajectoryRosMessage msg;
	ihmc_msgs::OneDoFJointTrajectoryRosMessage n3;
	ihmc_msgs::TrajectoryPoint1DRosMessage n2;
	n2.time=(moveSpeedOverRide==-1?gui.moveSpeed:moveSpeedOverRide);
	n2.position=0;
	n2.velocity=.5;
	n3.trajectory_points.push_back(n2);
	for(int i=0;i<7;i++){
		angles[i]=(angles[i]>high[i]?high[i]:angles[i]);
		angles[i]=(angles[i]<low[i]?low[i]:angles[i]);
		if(i==1||i==3)
			angles[i]=(side==JLEFT?angles[i]*-1 : angles[i]);
		n3.trajectory_points[0].position=angles[i];
		msg.joint_trajectory_messages.push_back(n3);
	}
	msg.robot_side=side;
	msg.unique_id=uId++;
	/*
	std::cout<<(side==JLEFT?"LEFT: ":"RIGHT: ");
	for(int i=0;i<7;i++){
		std::cout<<" Joint "<<i+1<<": "<<angles[i];//*(180/PI);
	}
	std::cout<<std::endl;*/
	for(int i=0;i<4;i++)
		gui.humanPositions[i+3+side*7]=angles[i];

	if(record){
		angles.insert(angles.begin(),side);
		gui.record("1: ",angles);
	}
	return msg;
}

ihmc_msgs::NeckTrajectoryRosMessage moveHead(std::vector<double> angles,bool record){
	double high[3]={1.1,1,0};
	double low[3]={0,-1,-.8};
	ihmc_msgs::NeckTrajectoryRosMessage msg;
	ihmc_msgs::OneDoFJointTrajectoryRosMessage n3;
	ihmc_msgs::TrajectoryPoint1DRosMessage n2;
	n2.time=(moveSpeedOverRide==-1?gui.moveSpeed:moveSpeedOverRide);
	n2.position=0;
	n2.velocity=.5;
	n3.trajectory_points.push_back(n2);
	for(int i=0;i<3;i++){
		angles[i]=(angles[i]>high[i]?high[i]:angles[i]);
		angles[i]=(angles[i]<low[i]?low[i]:angles[i]);
		n3.trajectory_points[0].position=angles[i];
		msg.joint_trajectory_messages.push_back(n3);
	}
	msg.unique_id=uId++;
	for(int i=0;i<3;i++)
		gui.humanPositions[i]=angles[i];

	if(record)
		gui.record("2: ",angles);
	return msg;
}
//YO DUMBBY, these are measured in degrees, not radians! (But i'll do the change here)
ihmc_msgs::ChestTrajectoryRosMessage moveChest(std::vector<double> angles,bool record){
	/*std::cout<<"CHEST: ";
	for(int i=0;i<3;i++){
		std::cout<<" Joint "<<i+1<<": "<<angles[i]*(180/PI);
	}
	std::cout<<std::endl;*/
	double high[3]={1.047,1.378,1.2217};
	double low[3]={-1.047,-.7,-1.2217};
	ihmc_msgs::ChestTrajectoryRosMessage msg;
	ihmc_msgs::SO3TrajectoryPointRosMessage n2;
	for(int i=0;i<3;i++){
		angles[i]=(angles[i]>high[i]?high[i]:angles[i]);
		angles[i]=(angles[i]<low[i]?low[i]:angles[i]);
	}
	std::vector<double> quat=eulerToQuaternion(angles);
	n2.time=(moveSpeedOverRide==-1?gui.moveSpeed:moveSpeedOverRide);
	n2.orientation.x=quat[0];
	n2.orientation.y=quat[1];
	n2.orientation.z=quat[2];
	n2.orientation.w=quat[3];
	n2.angular_velocity.x=0;n2.angular_velocity.z=0;n2.angular_velocity.y=0;
	msg.taskspace_trajectory_points.push_back(n2);
	msg.unique_id=uId++;

	for(int i=0;i<3;i++)
		gui.humanPositions[i+17]=angles[i];

	if(record)
		gui.record("4: ",angles);
	return msg;
}


ihmc_msgs::PelvisHeightTrajectoryRosMessage movePelvisHeight(double angle,bool record){
	double high=1.3;
	double low=.65;
  angle=(angle>high?high:angle);
  angle=(angle<low?low:angle);
	ihmc_msgs::PelvisHeightTrajectoryRosMessage msg;
  ihmc_msgs::TrajectoryPoint1DRosMessage n2;
  n2.time=(moveSpeedOverRide==-1?gui.moveSpeed:moveSpeedOverRide);
  n2.position=angle;
  n2.velocity=.5;
  msg.trajectory_points.push_back(n2);
  msg.unique_id=uId++;
  gui.standingHeight=angle;
	std::vector<double> angles;
	angles.push_back(angle);
	if(record)
		gui.record("3: ",angles);
  return msg;
}
