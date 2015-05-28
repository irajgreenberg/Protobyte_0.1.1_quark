
#include "BlockNet.h"

void BlockNet::init() {
	globalAmbient = Col3f(1, .1, .1);
	shadowsOn(); 
	block = ProtoBlock(Vec3(), Vec3(), Dim3f(330, 330, 330), Col4(.345, .123, 1, 1), "white_tile.jpg");
	block.setBumpMap("white_tile.jpg");
	block.setTextureScale(Vec2f(.5));
	//Plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	block.setSpecularMaterial(Col4f(.1, .1, .1, 1.0));
	block.setShininess(100);
}

void BlockNet::run() {
}

void BlockNet::display() {
	background(1.0, .5, 0); 
	push();
	translate(0, 0, -16);
	scale(150, 150, 150); 
	arcBallBegin();
	block.display();
	arcBallEnd();
	pop();
}