
#include "BlockNet.h"

void BlockNet::init() {
	globalAmbient = Col3f(.2, .2, .2);
	shadowsOn(); 
	
	std::vector<Vec3f> pathVecs;

	for(int i = 0; i < BLOCK_COUNT; ++i){
		pos[i] = Vec3(random(-400, 400), random(-400, 400), random(-600, 600));
		rot[i] = Vec3(random(-360, 360), random(-360, 360), random(-360, 360));
		float sz = random(20, 125);
		dim[i] = Dim3f(sz);

		
		blocks[i] = ProtoBlock(pos[i], rot[i], dim[i], Col4(.5, .4, .5, 1), "corroded_red.jpg");
		blocks[i].setBumpMap("corroded_red.jpg");
		//block.setTextureScale(Vec2f(.5));
		blocks[i].setAmbientMaterial(Col4f(1, 1, 1, 1.0));
		blocks[i].setSpecularMaterial(Col4f(1, .851, 1, 1.0));
		blocks[i].setShininess(120);

		pathVecs.push_back(blocks[i].getPosition());
	}

	
	path = Spline3(pathVecs, 8, false, .5);
	//ProtoTube::ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed, const std::string& textureImageURL, const Vec2f& textureScale
	tube = ProtoTube(path, 5, 18, false, "pitted.jpg", Vec2f(.5, .003));
	tube.textureOn();
	tube.setBumpMap("pitted.jpg");
	//block.setTextureScale(Vec2f(.5));
	//tube.setAmbientMaterial(Col4f(1, 1, 1, 1.0));
	tube.setSpecularMaterial(Col4f(1, .851, 1, 1.0));
	tube.setShininess(20);
}

void BlockNet::run() {
}

void BlockNet::display() {
	background(0.0); 
	arcBallBegin(); 
	translate(0, 0, -500);
	for (int i = 0; i < BLOCK_COUNT; ++i){
		push();
		translate(blocks[i].getPosition());
		rotate(blocks[i].getRotation().x, 1, 0, 0);
		rotate(blocks[i].getRotation().y, 0, 1, 0);
		rotate(blocks[i].getRotation().z, 0, 0, 1);
		scale(blocks[i].getSize().w, blocks[i].getSize().h, blocks[i].getSize().d);
		blocks[i].display();
		pop();
	}
	path.display();
	tube.display();
	arcBallEnd();

}