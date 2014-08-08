
#ifndef __MYAPP02_H__
#define __MYAPP02_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

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

};

#endif //__MYAPP02_H__
