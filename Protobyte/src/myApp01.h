
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

private:
	ProtoGroundPlane plane;
	ProtoTube tube;
	Cylinder cylinder;
	ProtoEllipse ellipse;

	
};

#endif //__MYAPP01_H__
