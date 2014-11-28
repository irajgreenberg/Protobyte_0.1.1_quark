
#ifndef __MYAPP01_H__
#define __MYAPP01_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

using namespace ijg;

class myApp01 : public ProtoBaseApp {

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
	Cylinder cylinder;
	ProtoEllipse ellipse;

	ProtoPath3 myPath;

	
};

#endif //__MYAPP01_H__
