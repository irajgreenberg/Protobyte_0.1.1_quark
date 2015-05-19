
#include "myApp20.h"

void myApp20::init() {

	globalAmbient = Col3f(.65, .65, .65);

	//light0.setPosition(Vec3f(.1, 300, 0));
	light0.setPosition(Vec3f(0, 150, -50));
	light0.setIntensity(Vec3f(.85, .85, .85));

	light1.setPosition(Vec3f(-10, -400, 0));
	light1.setIntensity(Vec3f(1, 1, 1));
	//camera0.setPosition(Vec3f(0, 0, 500));


	shadowsOn();
	plane = GroundPlane(Vec3(), Vec3(), Dim2f(50, 50), Col4f(1, 1, 1, 1), 1, 1, "yellow2.jpg", Vec2f(1, 1));
	//GroundPlane()
	plane.textureOn();
	plane.setBumpMap("yellow2.jpg");
	plane.loadBumpMapTexture("yellow2.jpg");
	plane.setTextureScale(Vec2f(.05));
	plane.setAmbientMaterial(Col4f(.3, .3, .3, 1.0));
	plane.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	plane.setShininess(6);
}

void myApp20::run() {
}

void myApp20::display() {
	arcBallBegin();
	//rect(Vec2(-100, 100), Vec2(100, -100));
	plane.display();
	arcBallEnd();
}