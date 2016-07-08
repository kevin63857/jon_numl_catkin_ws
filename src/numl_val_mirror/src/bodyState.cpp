#include "../include/bodyState.hpp"
//Here are some various method implementations and documentations



std::vector<double> BodyState::getChestAngles(){//we should look at amplifying movement in the chest
	std::vector<double> toRet;
	toRet.push_back(getAngleInPlane(YZ,centerAtOrigin(lastStats[6],lastStats[4]),Point(0,5,0)));
	if(toRet[0]>PI)
		toRet[0]-=2*PI;

	toRet.push_back(getAngleInPlane(XZ,centerAtOrigin(lastStats[6],lastStats[13]),Point(-5,0,0)));
	//std::cout<<getAngleInPlane(XZ,centerAtOrigin(lastStats[6],lastStats[13]),Point(-5,0,0))<<std::endl;
	//std::cout<<getAngleInPlane(XZ,centerAtOrigin(lastStats[13],lastStats[6]),Point(5,0,0))<<std::endl;

	if(toRet[1]>PI)
		toRet[1]-=2*PI;

	toRet.push_back(getAngleInPlane(XY,centerAtOrigin(lastStats[6],lastStats[4]),Point(0,5,0)));//average this with the rigth side
	toRet[2]+=getAngleInPlane(XY,centerAtOrigin(lastStats[13],lastStats[11]),Point(0,5,0));
	toRet[2]/=2;
	if(toRet[2]>PI)
		toRet[2]-=2*PI;

	return toRet;
}
double BodyState::getStandingHeight(){
	double out=(((lastStats[4].y-lastStats[2].y)+(lastStats[11].y-lastStats[9].y)/2)/highestHipAverage)*1.3;
	//std::cout<<out<<" "<<highestHipAverage<<" "<<((lastStats[4].y-lastStats[2].y)+(lastStats[11].y-lastStats[9].y)/2)<<std::endl;
	return out;
}
std::vector<double> BodyState::getLeftArmAngles(){
	std::vector<double> toRet;
	//Calculate J1 *****************************
	Point a=centerAtOrigin(lastStats[1],lastStats[6]),b=centerAtOrigin(lastStats[4],lastStats[6]);
	a.x=0;
	b.x=0;
	toRet.push_back(getAngleBetween(a,b));
	if(lastStats[1].z<lastStats[4].z)
		toRet[0]*=-1;
	//Calculate J2 *****************************
	toRet.push_back(getAngleBetween(centerAtOrigin(lastStats[1],lastStats[6]),centerAtOrigin(lastStats[13],lastStats[6])));
	if(centerAtOrigin(lastStats[1],lastStats[6]).y<centerAtOrigin(lastStats[13],lastStats[6]).y)
		toRet[1]=(2*PI)-toRet[1];
	toRet[1]-=PI;
	//Calculate J3 *****************************
	toRet.push_back(getAngleBetween(centerAtOrigin(lastStats[3],lastStats[1]),Point(0,1,0)));
	toRet[2]-=(PI/2);
	//Calculate J4 *****************************
	toRet.push_back(getAngleBetween(centerAtOrigin(lastStats[3],lastStats[1]),centerAtOrigin(lastStats[6],lastStats[1])));
	toRet[3]=(PI)-toRet[3];
	for(int i=0;i<3;i++)
		toRet.push_back(0);
	return toRet;
}
std::vector<double> BodyState::getRightArmAnglesWithMyo(){
	std::vector<double> toRet;
	//Calculate J1 *****************************
	Point a=centerAtOrigin(lastStats[8],lastStats[13]),b=centerAtOrigin(lastStats[11],lastStats[13]);
	a.x=0;
	b.x=0;
	toRet.push_back(getAngleBetween(a,b));
	if(lastStats[8].z<lastStats[11].z)
		toRet[0]*=-1;
	//Calculate J2 *****************************
	toRet.push_back(getAngleBetween(centerAtOrigin(lastStats[8],lastStats[13]),centerAtOrigin(lastStats[6],lastStats[13])));
	if(centerAtOrigin(lastStats[8],lastStats[13]).y<centerAtOrigin(lastStats[6],lastStats[13]).y)
		toRet[1]=(2*PI)-toRet[1];
	toRet[1]-=PI;
	//Calculate J3 *****************************
	toRet.push_back(getAngleBetween(centerAtOrigin(lastStats[10],lastStats[8]),Point(0,1,0)));
	toRet[2]-=(PI/2);
	//Calculate J4 *****************************
	toRet.push_back(getAngleBetween(centerAtOrigin(lastStats[10],lastStats[8]),centerAtOrigin(lastStats[13],lastStats[8])));
	toRet[3]=(PI)-toRet[3];
	for(int i=0;i<3;i++)
		toRet.push_back(0);
	return toRet;
}
std::vector<double> BodyState::getRightArmAngles(){
	std::vector<double> toRet;
	//Calculate J1 *****************************
	Point a=centerAtOrigin(lastStats[8],lastStats[13]),b=centerAtOrigin(lastStats[11],lastStats[13]);
	a.x=0;
	b.x=0;
	toRet.push_back(getAngleBetween(a,b));
	if(lastStats[8].z<lastStats[11].z)
		toRet[0]*=-1;
	//Calculate J2 *****************************
	toRet.push_back(getAngleBetween(centerAtOrigin(lastStats[8],lastStats[13]),centerAtOrigin(lastStats[6],lastStats[13])));
	if(centerAtOrigin(lastStats[8],lastStats[13]).y<centerAtOrigin(lastStats[6],lastStats[13]).y)
		toRet[1]=(2*PI)-toRet[1];
	toRet[1]-=PI;
	//Calculate J3 *****************************
	toRet.push_back(getAngleBetween(centerAtOrigin(lastStats[10],lastStats[8]),Point(0,1,0)));
	toRet[2]-=(PI/2);
	//Calculate J4 *****************************
	toRet.push_back(getAngleBetween(centerAtOrigin(lastStats[10],lastStats[8]),centerAtOrigin(lastStats[13],lastStats[8])));
	toRet[3]=(PI)-toRet[3];
	for(int i=0;i<3;i++)
		toRet.push_back(0);
	return toRet;
}
std::vector<double> BodyState::getNeckAngles(){
	std::vector<double> toRet;
	double headTilt=getAngleBetween(centerAtOrigin(lastStats[0],lastStats[7]),centerAtOrigin(lastStats[6],lastStats[7]));
	double abHTilt=headTilt-(90*(PI/180));
	abHTilt=(abHTilt<0?-1*abHTilt:abHTilt);
	toRet.push_back(abHTilt);
	toRet.push_back(0);
	toRet.push_back(-1*abHTilt);
	return toRet;
}
//FUCK ME, this doesn't work
//It only takes two angles to define any rotation in 3 space
void BodyState::rebuildTFTree(){
	for(int i=0;i<15;i++){
		newTF[rebuildOrder[i]]=rebuiltJoint(lastStats[rebuildOrder[i]],lastStats[parentID[i]],rebuildOrder[i],parentID[i]);
	}
}

rebuiltJoint::rebuiltJoint(Point thisOne, Point parent, int ID_, int parentID_){
	ID=ID_;
	parentID=parentID_;
	x=thisOne.x-parent.x;
	y=thisOne.y-parent.y;
	z=thisOne.z-parent.z;
	Tx=getAngleInPlane(XZ,parent,thisOne,parent);
	Ty=getAngleInPlane(YZ,parent,thisOne,parent);
	Tz=getAngleInPlane(XY,parent,thisOne,parent);

}

void BodyState::updateSkeletonData(int jointNum, double x_, double y_, double z_){
	lastStats[jointNum].x=x_;
	lastStats[jointNum].y=y_;
	lastStats[jointNum].z=z_;
	if(jointNum==11)
		highestHipAverage=(((lastStats[4].y-lastStats[2].y)+(lastStats[11].y-lastStats[9].y)/2)>highestHipAverage?((lastStats[4].y-lastStats[2].y)+(lastStats[11].y-lastStats[9].y)/2):highestHipAverage);
}

void BodyState::centerOn(Point p){
	for(int i=0;i<15;i++){
		rotated[i].x=lastStats[i].x-p.x;
		rotated[i].y=lastStats[i].y-p.y;
		rotated[i].z=lastStats[i].z-p.z;
	}
}

std::vector<double> BodyState::getArmHomeAngles(){
	std::vector<double> angles;
	angles.push_back(-.137);
	angles.push_back(1.137);
	angles.push_back(.765);
	angles.push_back(1.5);
	for(int i=0;i<3;i++)
		angles.push_back(0);
	return angles;
}
double BodyState::getPelvisHeightHomeAngles(){
	return 1;
}
std::vector<double> BodyState::getNeckHomeAngles(){
	std::vector<double> angles;
	for(int i=0;i<3;i++)
		angles.push_back(0);
	return angles;
}
std::vector<double> BodyState::getChestHomeAngles(){
	return getNeckHomeAngles();//this might not be the best and could lead to bugs down the road, but i'm lazy
}

void BodyState::rotateInPlane(int planeIdentifier, double theta){
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

void BodyState::rotateInPlane2(int planeIdentifier, double theta){
	double cosT=cos(theta),sinT=sin(theta);
	switch(planeIdentifier){
		case XY:
			for(int i=0;i<15;i++){
				rotated2[i].x=cosT*rotated[i].x+(-1*sinT)*rotated[i].y;
				rotated2[i].y=sinT*rotated[i].x+(cosT)*rotated[i].y;
				rotated2[i].z=rotated[i].z;
			}
			break;
		case XZ:
			for(int i=0;i<15;i++){
				rotated2[i].x=cosT*rotated[i].x+(-1*sinT)*rotated[i].z;
				rotated2[i].y=rotated[i].y;
				rotated2[i].z=sinT*rotated[i].x+(cosT)*rotated[i].z;
			}
			break;
		case YZ:
			for(int i=0;i<15;i++){
				rotated2[i].x=rotated[i].x;
				rotated2[i].y=cosT*rotated[i].y+(-1*sinT)*rotated[i].z;
				rotated2[i].z=sinT*rotated[i].y+(cosT)*rotated[i].z;
			}
			break;
	}
}

//6 left shoulder 8 elbow 10 hand 11 hip 13 shoulder
//******************************************************************************//
std::vector<double> eulerToQuaternion(std::vector<double> euler){
	std::vector<double> toRet;
	std::vector<double> m;
	for(int i=0;i<3;i++)
		m.push_back(cos(euler[i]/2));
	for(int i=0;i<3;i++)
		m.push_back(sin(euler[i]/2));
	toRet.push_back(m[3]*m[4]*m[2]+m[0]*m[1]*m[5]);//x
	toRet.push_back(m[3]*m[1]*m[2]+m[0]*m[4]*m[5]);//y
	toRet.push_back(m[0]*m[4]*m[2]-m[3]*m[1]*m[5]);//z
	toRet.push_back(m[0]*m[1]*m[2]-m[3]*m[4]*m[5]);//w
	return toRet;
}


Point centerAtOrigin(Point p1, Point p2){//returns p1 relative to p2 at the origin
	return Point(p1.x-p2.x,p1.y-p2.y,p1.z-p2.z);
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
	retAngle*=(PI/180);
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
double getAngleInPlane(int planeIdentifier, Point a, Point b, Point c){
	return getAngleInPlane(planeIdentifier, b-a, c-b);
}
