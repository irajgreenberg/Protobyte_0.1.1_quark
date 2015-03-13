
#ifndef __COLLISIONTEST03_H__
#define __COLLISIONTEST03_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

using namespace ijg;

class CollisionTest03 : public ProtoBaseApp {

public:
void init();
void run();
void display();

bool collide(Face3& t, const Vec3& orb);

private:

	bool isForming = true;
	int counter = 0;
	static const int ORB_COUNT = 1000;
	Vec3 orbs[ORB_COUNT], spds[ORB_COUNT];
	ProtoSpline3 spline;
	ProtoTube tube;
	ProtoTube vein;

	void test();

	ProtoSphere sphere, outerSphere;
	ProtoToroid toroid;
	std::vector<Face3> faces;
	std::vector<Face3> outerSphereFaces;
};

#endif //__COLLISIONTEST03_H__
