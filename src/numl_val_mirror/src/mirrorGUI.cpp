#include "../include/mirrorGUI.hpp"
//sf::RenderWindow GUI::window=sf::RenderWindow(sf::VideoMode(400, 700), "Atleast it's not ui_builder");
void GUI::init(){
	for(int i=0;i<33;i++){
		robotPositions[i]=-1;
		humanPositions[i]=-1;
	}
	if(!font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeMono.ttf"))
		std::cout<<"got here ERROR"<<std::endl;
	//Button::font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
	//window=sf::RenderWindow(sf::VideoMode(400, 700), "Atleast it's not ui_builder");
	buttons.push_back(Button(30,160,30,35,"Start All",font));
	buttons.push_back(Button(240,160,30,35,"Stop All",font));
	buttons.push_back(Button(30,370,85,35,"Start/Stop Myo Controller",font));
	buttons.push_back(Button(30,370,140,35,"Start/Stop Occulus Display",font));
	buttons.push_back(Button(30,370,195,35,"Start/Stop Head Mirroring",font));
	buttons.push_back(Button(30,370,250,35,"Start/Stop Left Arm Mirroring",font));
	buttons.push_back(Button(30,370,305,35,"Start/Stop Right Arm Mirroring",font));
	buttons.push_back(Button(30,370,360,35,"Start/Stop Chest Mirroring",font));
	buttons.push_back(Button(30,370,415,35,"Start/Stop Pelvis Mirroring",font));
	buttons.push_back(Button(30,370,540,35,"Start/Stop Recording",font));
	buttons.push_back(Button(30,370,595,35,"Play Last Recording to 10.185.0.30",font));
	buttons.push_back(Button(30,370,780,35,"GO HOME",font));
	buttons[0].setColor(sf::Color::Green);
	buttons[2].setColor(sf::Color(175,255,175,255));
	buttons[3].setColor(sf::Color(175,175,175,255));
	buttons[10].textContent.setCharacterSize(17);
	//this sets a white background
	lines.push_back(sf::RectangleShape(sf::Vector2f(1000,950)));
	lines.push_back(sf::RectangleShape(sf::Vector2f(4,875)));
	lines[1].setPosition(650,20);
	lines.push_back(sf::RectangleShape(sf::Vector2f(1,875)));
	lines[2].setPosition(825,20);
	lines.push_back(sf::RectangleShape(sf::Vector2f(500,4)));
	lines[3].setPosition(480,60);
	for(int i=0;i<32;i++){
		lines.push_back(sf::RectangleShape(sf::Vector2f(500,1)));
		lines[lines.size()-1].setPosition(480,85+25*i);
	}
	moveSpeed=2.5;
	lines.push_back(sf::RectangleShape(sf::Vector2f(330,4)));
	lines[lines.size()-1].setPosition(50,520);
	lines.push_back(sf::RectangleShape(sf::Vector2f(4,20)));
	lines[lines.size()-1].setPosition(215,512);
	sliderLine=lines.size()-1;
	//the box for myo_orientation
	lines.push_back(sf::RectangleShape(sf::Vector2f(370,4)));
	lines[lines.size()-1].setPosition(30,690);
	lines.push_back(sf::RectangleShape(sf::Vector2f(370,4)));
	lines[lines.size()-1].setPosition(30,720);
	for(int i=0;i<4;i++){
		lines.push_back(sf::RectangleShape(sf::Vector2f(4,34)));
		lines[lines.size()-1].setPosition(30+122*i,690);
	}

	for(int i=1;i<lines.size();i++)
		lines[i].setFillColor(sf::Color(0,0,0,255));

	addWord("Movement Speed:",65,480,24);
	addWord("2.5000",300,480,24);
	addWord("Joint",490,40);
	addWord("Human",725,40);
	addWord("Valkyrie",850,40);
	//33 Joints
    for(int i=0;i<33;i++)
	   addWord(jointNames[i],485,65+25*i);
	addWord("Myo Angle (x,y,z)",30,650,24);
}



void GUI::addWord(std::string word, int x, int y){
	addWord(word,x,y,15);
}
void GUI::addWord(std::string word, int x, int y,int size){
	sf::Text text;
	text.setFont(font);
	text.setString(word);
	text.setPosition(x,y);
	text.setCharacterSize(size);
	text.setColor(sf::Color(0,0,0,255));
	words.push_back(text);
}
//it might not be a great idea to hard code the order of the button array into their actions but.....
//																						  whatever
void GUI::doButtonStuff(int buttonNum){
	switch(buttonNum){
	case -1:
		if(gesture==4)
			weShouldGoHomeNow();
	break;
	case 0:
		isHeadOn=true;isLeftArmOn=true;isRightArmOn=true;isChestOn=true;isPelvisOn=true;
		std::cout<<"ALL ON"<<buttonNum<<std::endl;
	break;
	case 1:
		isOcculusOn=false;isHeadOn=false;isLeftArmOn=false;isRightArmOn=false;isChestOn=false;isPelvisOn=false;
	break;
	case 3:
		isOcculusOn=false;
	break;
	case 4:
		isHeadOn=!isHeadOn;
	break;
	case 5:
		isLeftArmOn=!isLeftArmOn;
	break;
	case 6:
		isRightArmOn=!isRightArmOn;
	break;
	case 7:
		isChestOn=!isChestOn;
	break;
	case 8:
		isPelvisOn=!isPelvisOn;
	break;
	case 9:
		areWeRecording=!areWeRecording;
		if(areWeRecording){
			struct timeval tp;
			gettimeofday(&tp, NULL);
			startTime=tp.tv_sec * 1000 + tp.tv_usec / 1000;
			std::ostringstream concat;
			concat<<"/home/hoenir/valkrieCommandRecords/records"<<startTime;
			latestName=concat.str();
			std::ofstream fileCreator(latestName.c_str());
			fileCreator.close();
  		recordFile.open(latestName.c_str());
			weShouldGoHomeNow();
		}
		else{
			recordFile.close();
		}
	break;
	case 10:
		{
			std::ostringstream concat2;
			concat2<<"python ~/numl_catkin_ws/src/numl_val_mirror/src/publishSaveFile.py"<<latestName;
	 		system(concat2.str().c_str());
		}
	break;
	case 11:
		weShouldGoHomeNow();
	break;
	}
	updateButtonStates();
}

void GUI::updateButtonStates(){
	int gray=(gesture!=1?175:0);
	if(isOcculusOn)
		buttons[3].setColor(sf::Color(0,255,0,255));
	else
		buttons[3].setColor(sf::Color(175,175,175,255));

	if(isHeadOn)
		buttons[4].setColor(sf::Color(gray,255,gray,255));
	else
		buttons[4].setColor(sf::Color(255,gray,gray,255));

	if(isLeftArmOn)
		buttons[5].setColor(sf::Color(gray,255,gray,255));
	else
		buttons[5].setColor(sf::Color(255,gray,gray,255));

	if(isRightArmOn)
		buttons[6].setColor(sf::Color(gray,255,gray,255));
	else
		buttons[6].setColor(sf::Color(255,gray,gray,255));

	if(isChestOn)
		buttons[7].setColor(sf::Color(gray,255,gray,255));
	else
		buttons[7].setColor(sf::Color(255,gray,gray,255));

	if(isPelvisOn)
		buttons[8].setColor(sf::Color(gray,255,gray,255));
	else
		buttons[8].setColor(sf::Color(255,gray,gray,255));

	if(areWeRecording)
		buttons[9].setColor(sf::Color(0,255,0,255));
	else
		buttons[9].setColor(sf::Color(255,0,0,255));

	if(startTime==-1 || areWeRecording)
		buttons[10].setColor(sf::Color(175,175,175,255));
	else
		buttons[10].setColor(sf::Color(0,225,0,255));
//std::cout<<goHomeCount<<std::endl;
	if((goHomeCount>0))
		buttons[11].setColor(sf::Color(0,225,0,255));
	else
		buttons[11].setColor(sf::Color(225,0,0,255));

}


void GUI::mouseClicked(int x, int y){
	for(int i=0;i<buttons.size();i++){
		if(buttons[i].isButtonClicked(x,y)){
			//std::cout<<"HA HA!! I HAVE FOUND YOU, IT WAS BUTTON "<<i<<std::endl;
			doButtonStuff(i);
		}
	}
	//the slider bar
	if(y>=512 && y<=532 && x>=50 && x<=380){
		lines[sliderLine].setPosition(x,512);
		moveSpeed=(x-50.0)/330;
		moveSpeed*=5;
		std::ostringstream moveString;
		moveString<<moveSpeed;
		words[1].setString(moveString.str());
	}
}

bool Button::isButtonClicked(int x, int y){
	return (x>=xLeft && x<=xLeft+xLen) && (y>=yTop && y<=yTop+yLen);

}


void GUI::weShouldGoHomeNow(){
	std::cout<<"we should go home"<<std::endl;
	startGoingHome=true;
	goHomeCount=12;//12 cycles of the main loop
}

void GUI::record(std::string prefix, std::vector<double> data){
	if(!areWeRecording)
		return;
	recordFile<<prefix<<" ";
	for(int i=0;i<data.size();i++)
		recordFile<<data[i]<<" ";
	recordFile<<std::endl;

}
