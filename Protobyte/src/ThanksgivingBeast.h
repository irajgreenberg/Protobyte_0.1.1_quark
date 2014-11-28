
#ifndef __THANKSGIVINGBEAST_H__
#define __THANKSGIVINGBEAST_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

using namespace ijg;

class ThanksgivingBeast : public ProtoBaseApp {

public:
void init();
void run();
void display();

private:

	ProtoGroundPlane plane;
	std::vector<ProtoTube> ribs;

	std::vector<ProtoTube> ribBands;
	std::vector<Vec3> tempVecs, allVecs;

	// visera
	ProtoTube vascularWrap;
};

#endif //__THANKSGIVINGBEAST_H__
