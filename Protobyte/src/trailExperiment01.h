
#ifndef __TRAILEXPERIMENT01_H__
#define __TRAILEXPERIMENT01_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"
#include "libProtobyte/ProtoGroundPlane.h"

using namespace ijg;

class trailExperiment01 : public ProtoBaseApp {

public:
void init();
void run();
void display();

bool collide(Face3& t, const Vec3& orb);

private:

	int counter = 0;
	static const int ORB_COUNT = 20;
	static const int VEIN_COUNT = 300;
	float damping = .775;

	ProtoSpline3 spline;
	std::vector<ProtoTube> veins;

	ProtoTube vein;

	ProtoGroundPlane plane;
};

#endif //__TRAILEXPERIMENT01_H__
