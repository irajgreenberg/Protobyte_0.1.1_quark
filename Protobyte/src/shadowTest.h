// shadowTest

#ifndef __SHADOW_TEST__
#define  __SHADOW_TEST__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"


using namespace ijg;

class shadowTest : public ProtoBaseApp {

public:
	void init();
	void run();


	void render(int scaleFactor = 1);
	Plane plane;
	Toroid toroid;


private:
	
};

#endif //  __SHADOW_TEST__