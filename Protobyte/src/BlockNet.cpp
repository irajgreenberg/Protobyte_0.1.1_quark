
#include "BlockNet.h"

void BlockNet::init() {
	globalAmbient = Col3f(.2, .2, .2);
	shadowsOn(); 
	
	for (int i = 0; i < BLOCK_COUNT; ++i){
		pos[i] = Vec3(random(-400, 400), random(-400, 400), random(-600, 600));
		rot[i] = Vec3(random(-360, 360), random(-360, 360), random(-360, 360));
		float sz = random(20, 125);
		scl[i] = Vec3(sz);

		
		blocks[i] = ProtoBlock(Vec3(), Vec3(), Dim3f(sz), Col4(.5, .4, .5, 1), "corroded_red.jpg");
		blocks[i].setBumpMap("corroded_red.jpg");
		//block.setTextureScale(Vec2f(.5));
		blocks[i].setAmbientMaterial(Col4f(1, 1, 1, 1.0));
		blocks[i].setSpecularMaterial(Col4f(1, .851, 1, 1.0));
		blocks[i].setShininess(20);
	}
}

void BlockNet::run() {
}

void BlockNet::display() {
	background(1.0, .5, 0); 
	arcBallBegin(); 
	translate(0, 0, -500);
	for (int i = 0; i < BLOCK_COUNT; ++i){
		push();
		translate(pos[i]);
		rotate(rot[i].x, 1, 0, 0);
		rotate(rot[i].y, 0, 1, 0);
		rotate(rot[i].z, 0, 0, 1);
		scale(scl[i].x, scl[i].y, scl[i].z);
		blocks[i].display(WIREFRAME);
		pop();
	}
	arcBallEnd();

}