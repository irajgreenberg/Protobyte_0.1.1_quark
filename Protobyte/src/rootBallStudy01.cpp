
#include "rootBallStudy01.h"

#include <thread>


float theta5 = 0;

void rootBallStudy01::init() {

	
	TransformFunction t2 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.14f, .22f), 80); // local, so can't be sent as reference
	
	// wall
	plane = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 1, 1), 1, 1, "white_tile.jpg");
	//plane.textureOn();
	plane.setBumpMap("white_tile.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	plane.setTextureScale(Vec2f(.5));
	//plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	plane.setSpecularMaterial(Col4f(.35, .35, .35, 1.0));
	plane.setShininess(128);
	//trace("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS =", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

	// ground
	ground = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 1, 1), 1, 1, "white_tile.jpg");
	//plane.textureOn();
	ground.setBumpMap("white_tile.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	ground.setTextureScale(Vec2f(.5));
	//plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	ground.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	ground.setShininess(3);

	std::string texs[] = { "pebbles.jpg", "gold_foil2.jpg", "vascular.jpg", "greenCrocSkin.jpg", "pink2.jpg", "metal_screwHeads.jpg", "woodPlank.jpg", "metal_blue.jpg", "shipPlate_yellow.jpg", "reptile2_invert.jpg", "corroded_metal.jpg", "giraffe.jpg", "shipPlate.jpg", "metal_grate.jpg" }; 
	

		for (int i = 0; i < ROOTBALL_COUNT; ++i){
			int sub = int(random(14));
			rootBalls[i] = RootBall(Vec3f(), Vec3f(), Dim3f(2.55f), Col4f(.9f), 1, 150, .3, Tup2f(.2, .5), texs[sub], 14);
			TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.06f, .35f), int(random(3, 65))); // local, so can't be sent as reference
			rootBalls[i].setTransformFunction(t1);
			rootBalls[i].setTextureScale(Vec2f(1, .0075));
		}

		// export geometry data to 
		//std::vector<Tup4v> vs;

		//std::vector<Tup4v> temp2 = rootBalls[0].getGeomData();
		//vs.insert(vs.end(), temp2.begin(), temp2.end());
		//export(vs, STL);
		//shadowsOn();
}




void rootBallStudy01::run() {
	setBackground(0);

	// save high resolution rendering
	// currently only works with max 999 tiles
	//
	//std::thread t(&ProtoBaseApp::render);
	//t.join();
	//render();

	// wall
	

	static int frameCounter = 0;
	

	// shadowsOn();
	// shape display()
	push();
	translate(0, 0, -14);
	scale(13.75, 12.75, 1);
	rotate(90, 1, 0, 0);
	plane.display();
	pop();

	// ground 
	//push();
	//translate(0, -7, 5);
	//scale(13.75, 1, 1);
	//ground.display();
	//pop();



	push();
	translate(-1, sin(theta5) * 2, 0);
	scale(4.75);
	rotate(getFrameCount()*.05f, 0, 1, 0);
	rotate(getFrameCount()*.065f, 0, 0, 1);
	rotate(getFrameCount()*.05f, 1, 0, 0);
	for (int i = 0; i < ROOTBALL_COUNT; ++i){
		rootBalls[i].display();
	}
	pop();

	if (frameCounter++ < 1){
		save("roots", 14);
		/*std::thread t(&this->save, "roots", 13);
		t.join();*/
	}
}