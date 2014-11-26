
#ifndef __MYAPP03_H__
#define __MYAPP03_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

using namespace ijg;

class myApp03 : public ProtoBaseApp {

public:
void init();
void run();
void display();

void mousePressed();
void mouseReleased();
void mouseMoved();
void mouseDragged();

private:
	Toroid toroid;
};

#endif //__MYAPP03_H__
