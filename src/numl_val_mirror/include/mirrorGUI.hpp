#ifndef mirrorGUI_hpp
#define mirrorGUI_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "sensor_msgs/JointState.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
enum bodyPart {NECK,LEFT_ARM,RIGHT_ARM,CHEST,HEIGHT};
//std::string const jointNames[]={"testing"};

/*
Yes, i know that everything is public and that might not be the best practice, but do i really want to deal with freaking getters and setters??
																																			NO
*/
class Button{
public:
	bool isButtonClicked(int x, int y);
	std::string text;
	sf::Color backgroundColor=sf::Color(255,0,0,255);
	sf::Text textContent;
	sf::RectangleShape shapeContent;
	void drawButton();
	void setColor(sf::Color color){
		backgroundColor=color;
        shapeContent.setFillColor(backgroundColor);
	};
	Button(int xLeft_, int xLen_, int yTop_, int yLen_, std::string text_, sf::Font &font):xLeft(xLeft_),xLen(xLen_),yTop(yTop_),yLen(yLen_),text(text_){
		textContent.setFont(font);
		textContent.setString(text);
        textContent.setPosition(xLeft,yTop);
		textContent.setCharacterSize(20);
		textContent.setColor(sf::Color::White);
        shapeContent.setSize(sf::Vector2<float>(xLen,yLen));
        shapeContent.setFillColor(backgroundColor);
        shapeContent.setPosition(xLeft,yTop);
	};
	int xLeft, xLen, yTop, yLen;
protected:
};
const std::string jointNames[33]={"lowerNeckPitch","neckYaw","upperNeckPitch","leftShoulderPitch","leftShoulderRoll","leftShoulderYaw","leftElbowPitch","leftForearmYaw","leftWristRoll","leftWristPitch","rightShoulderPitch","rightShoulderRoll","rightShoulderYaw","rightElbowPitch","rightForearmYaw","rightWristRoll","rightWristPitch","torsoYaw","torsoPitch","torsoRoll","leftHipYaw","leftHipRoll","leftHipPitch","leftKneePitch","leftAnklePitch","leftAnkleRoll","rightHipYaw","rightHipRoll","rightHipPitch","rightKneePitch","rightAnklePitch","rightAnkleRoll","hokuyo_joint"};
const std::string gestureNames[7]={"rest","fist","wave in","wave out","fingers spread","??????5","???????6"};//nothing, unlock movement, nothing, nothing, goHome
const int mapping[33]={22,23,24,15,16,17,18,19,20,21,26,27,28,29,30,31,32,12,13,14,0,1,2,3,4,5,6,7,8,9,10,11,25};
class GUI{
public:
	//static const sf::RenderWindow window(sf::VideoMode(400, 700), "Atleast it's not ui_builder");
	sf::Font font;
	void init();
	void updateRobotJointStates(sensor_msgs::JointState msg);
	void updateHumanJointStates(int bodyPart, std::vector<double> angles);
	void mouseClicked(int x, int y);
	void doButtonStuff(int buttonNum);
	void updateButtonStates();
	void weShouldGoHomeNow();
	void addWord(std::string words, int x, int y);
	void addWord(std::string words, int x, int y, int size);
	void record(std::string prefix, std::vector<double> data);
	int sliderLine;
	std::ofstream recordFile;
	long int startTime=-1;
	int gesture=0;
	double moveSpeed;
	double standingHeight;
	std::string latestName;
	double robotPositions[33]={-1};
	double humanPositions[33]={-1};
	double myo_orientation[3]={-1,-1,-1};
	std::vector<Button> buttons;
	std::vector<sf::RectangleShape> lines;
	std::vector<sf::Text> words;
	bool isOcculusOn=false,isHeadOn=false,isLeftArmOn=false,isRightArmOn=false,isChestOn=false,isPelvisOn=false,areWeRecording=false;
	bool startGoingHome=false;
	int goHomeCount=0;
};

#endif
