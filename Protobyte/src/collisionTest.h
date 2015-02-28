// on hyperplane
//http://gamedeveloperjourney.blogspot.com/2009/04/point-plane-collision-detection.html
// baycentric:
//http://blogs.msdn.com/b/rezanour/archive/2011/08/07/barycentric-coordinates-and-point-in-triangle-tests.aspx

#ifndef __COLLISIONTEST_H__
#define __COLLISIONTEST_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

using namespace ijg;

struct Tri{
	Vec3 v0, v1, v2;
	Tri(){}
	Tri(Vec3 v0, Vec3 v1, Vec3 v2):
		v0(v0), v1(v1), v2(v2) {}
	
	Vec3 N(){
		Vec3 e0, e1, n;
		e0 = v1 - v0;
		e1 = v2 - v0;
		n = e1.cross(e0);
		n.normalize();
		return n;
	}

	Vec3 C(){
		return (v0 + v1 + v2) / 3.0f;
	}

	void draw(ProtoBaseApp* base = nullptr){

		base->beginShape();
		base->vertex(v0);
		base->vertex(v1);
		base->vertex(v2);
		base->endShape(CLOSE);
	}

	void drawNorm(ProtoBaseApp* base = nullptr, float len = 50){

		base->beginShape();
		base->vertex(C().x, C().y, C().z);
		base->vertex(C().x + N().x * len, C().y + N().y * len, C().z + N().z * len);
		base->endShape(CLOSE);
	}


};

class collisionTest : public ProtoBaseApp {

public:
void init();
void run();
void display();
bool collide(const Vec3&);

private:

	static const int ORB_COUNT = 500;
	Vec3 orbs[ORB_COUNT], spds[ORB_COUNT];
	Tri t;

	static const int TRI_COUNT = 500; 
	Tri ts[TRI_COUNT];
};

#endif //__COLLISIONTEST_H__
