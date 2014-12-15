
#ifndef __MYAPP01_H__
#define __MYAPP01_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"
#include "tesselator.h"

using namespace ijg;

class myApp01 : public ProtoBaseApp {

public:
void init();
void run();
void display();

void mousePressed();
void mouseReleased();
void mouseMoved();
void mouseDragged();

private:
	//ProtoGroundPlane plane;
	ProtoTube tube;
	//Cylinder cylinder;
	//ProtoEllipse ellipse;

	//ProtoPath3 myPath;
	GLUtesselator* tesselator;

	static const int W = 400;
	static const int H = 400;
	static const int D = 400;
	static const int ROWS = 15;
	static const int COLUMNS = 15;
	static const int LAYERS = 10;
	Col4f colors[ROWS*COLUMNS*LAYERS];
	float rots[ROWS*COLUMNS*LAYERS];
	float rotSpds[ROWS*COLUMNS*LAYERS];


	
};

#endif //__MYAPP01_H__
