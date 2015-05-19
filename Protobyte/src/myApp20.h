
#ifndef __MYAPP20_H__
#define __MYAPP20_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

using namespace ijg;

class myApp20 : public ProtoBaseApp {

public:
void init();
void run();
void display();

private:
	ProtoGroundPlane plane;
};

#endif //__MYAPP20_H__
