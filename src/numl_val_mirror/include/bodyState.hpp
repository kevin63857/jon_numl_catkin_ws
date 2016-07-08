#ifndef bodyState_hpp
#define bodyState_hpp
#define PI 3.14159265
#define JRIGHT 1
#define JLEFT 0
#define XY 1
#define XZ 2
#define YZ 3

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <math.h>
#include <stdio.h>

/*These are some constants that will be used throughout the program*/

std::string const bodyParts[]={"head","left_elbow","left_foot","left_hand","left_hip","left_knee","left_shoulder","neck","right_elbow","right_foot","right_hand", "right_hip","right_knee","right_shoulder","torso"};

/*
 This is just a point with the option to give angle data as well
 I defined it myself incase i want to go in and add any more functionality
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
	Point operator-(const Point b){
		return Point(x-b.x,y-b.y,z-b.z);
	}
};
class rebuiltJoint{
public:
	rebuiltJoint(Point thisOne, Point parent, int ID_, int parentID_);
	int ID;
	int parentID;
	double x,y,z;
	double radius;
	double tX,tY,tZ;
}
int rebuildOrder[15]={14,11,12,9,4,5,2,13,8,10,6,1,3,7,0};
int parentID[15]={14,14,11,12,14,4,5,14,13,8,14,6,1,14,7};

/*These are some various functions that rotate and translate points in 3 space
	Lol, i really don't use that many of these any more, they propegate too much noise
*/
Point centerAtOrigin(Point p1, Point p2);
double getAngle(double x,double y);
double getAngleBetween(Point a,Point b);
double getAngleInPlane(int planeIdentifier, Point a, Point b);
double getAngleInPlane(int planeIdentifier, Point a, Point b, Point c);
std::vector<double> eulerToQuaternion(std::vector<double> euler);


/*
 And now the main purpose of this file to begin with!
 */
class BodyState{
public:
	std::vector<double> getLeftArmAngles();
	std::vector<double> getRightArmAngles();
	std::vector<double> getRightArmAnglesWithMyo();
	std::vector<double> getNeckAngles();
	std::vector<double> getChestAngles();
	double getStandingHeight();

	std::vector<double> getArmHomeAngles();
	double getPelvisHeightHomeAngles();
	std::vector<double> getNeckHomeAngles();
	std::vector<double> getChestHomeAngles();

	void rebuildTFTree();
	void updateSkeletonData(int jointNum, double x, double y, double z);
private:
	rebuiltJoint newTF[15];
	Point lastStats[15]={Point(0,0,0)};
	Point rotated[15]={Point(0,0,0)}; //A better name would be transformed
	Point rotated2[15]={Point(0,0,0)};
	void rotateInPlane(int planeIdentifier, double theta);
	void rotateInPlane2(int planeIdentifier, double theta);
	void centerOn(Point p);
	double highestHipAverage=.5;
protected:
};

#endif /* bodyState_hpp */
