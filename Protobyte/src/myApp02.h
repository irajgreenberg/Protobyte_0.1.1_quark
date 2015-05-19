
#ifndef __MYAPP02_H__
#define __MYAPP02_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"
#include "libProtobyte/ProtoRootBall.h"

using namespace ijg;

class myApp02 : public ProtoBaseApp {

public:
void init();
void run();
void display();

void mousePressed();
void mouseReleased();
void mouseMoved();
void mouseDragged();

private:
	ProtoGroundPlane plane;
	ProtoTube tube;
	std::vector<ProtoTube> ribs;
	std::vector<ProtoTube> ribBands;
	std::vector<Vec3> tempVecs, allVecs;
	
	// visera
	ProtoTube vascularWrap; 
	
	// organs
	const static int ROOTBALL_COUNT = 1;// 34;
	ProtoRootBall rootBalls[ROOTBALL_COUNT];

};

#endif //__MYAPP02_H__
