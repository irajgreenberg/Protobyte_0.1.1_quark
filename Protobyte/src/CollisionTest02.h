
#ifndef __COLLISIONTEST02_H__
#define __COLLISIONTEST02_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

using namespace ijg;

class CollisionTest02 : public ProtoBaseApp {

public:
void init();
void run();
void display();

bool collide(Face3& t, const Vec3& orb);

private:

	static const int ORB_COUNT = 500;
	Vec3 orbs[ORB_COUNT], spds[ORB_COUNT];

	ProtoSphere sphere;
	std::vector<Face3> faces;
};

#endif //__COLLISIONTEST02_H__
