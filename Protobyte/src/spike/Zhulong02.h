#ifndef Protobyte_dev_Zhulong02_H
#define Protobyte_dev_Zhulong02_H

#include "appProtobyte/ProtoBaseApp.h"
#include <iostream>
#include "libProtobyte/ProtoToroid.h"
	
	
	
using namespace ijg;

class Zhulong02 : public ProtoBaseApp {

public:

	void init();
	void run();
	Toroid* toroid;
	Tube tubulesWrap;
	const static int TUBULE_RINGS = 6;
	int tubuleRingsIndices[TUBULE_RINGS];
	std::vector<Tube> tubules;

	Tube tube;
	Spline3 sp3;

};

#endif //Protobyte_dev_Zhulong02_H

