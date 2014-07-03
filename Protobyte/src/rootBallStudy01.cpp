
#include "rootBallStudy01.h"

#include <thread>


float theta5 = 0;
float theta = 0;

void rootBallStudy01::init() {
	shadowsOn();
	
	TransformFunction t2 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.14f, .22f), 80); // local, so can't be sent as reference
	
	// wall
	plane = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(0, 0, 0, 1), 1, 1, "white_tile.jpg");
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

	//http://1.bp.blogspot.com/-x0fmAALwyPM/UmpNqLMJfhI/AAAAAAAAEsE/JugrjQr0yRs/s1600/Seamless+tileable+reptile+snake+alien+frog+skin+texture.jpg
	//std::string texs[] = { "pebbles.jpg", "gold_foil2.jpg", "vascular.jpg", "greenCrocSkin.jpg", "pink2.jpg", "metal_screwHeads.jpg", "woodPlank.jpg", "metal_blue.jpg", "shipPlate_yellow.jpg", "reptile2_invert.jpg", "corroded_metal.jpg", "giraffe.jpg", "shipPlate.jpg", "metal_grate.jpg" }; 

	const int TEXTURE_COUNT = 2;
	std::string texs[] = { "skin01.jpg", "skin02.jpg", "skin03.jpg" };
	

		for (int i = 0; i < ROOTBALL_COUNT; ++i){
			int sub = int(random(TEXTURE_COUNT));
			rootBalls[i] = RootBall(Vec3f(), Vec3f(), Dim3f(2.55f), Col4f(.9f), 1, 150, .3, Tup2f(.2, .5), texs[sub], 14);
			float sz = 0;
			if (i % 7 == 0)
				sz = float(random(1.15, 1.65));
			else
				sz = float(random(.02, .3));
			TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(sz, sz), int(random(3, 65))); // local, so can't be sent as reference
			rootBalls[i].setTransformFunction(t1);
			rootBalls[i].setTextureScale(Vec2f(1, .0075));
		}

		// export geometry data to 
		//std::vector<Tup4v> vs;

		//std::vector<Tup4v> temp2 = rootBalls[0].getGeomData();
		//vs.insert(vs.end(), temp2.begin(), temp2.end());
		//export(vs, STL);
		//shadowsOn();



		//const int cps = 14;
		//float len = 3;
		//float seg = len / cps;

		//std::vector<Vec3> vecs;
		//for (int i = 0; i < cps; ++i){
		//	vecs.push_back(Vec3(random(-.03, .03), seg*i, random(-.03, .03)));
		//}

		//for (int i = 0; i < TUBE_COUNT; ++i){
		//	int sub = int(random(14));
		//	tubes[i] = Tube(Spline3(vecs, 5, false, 1), .2, 12, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(random(.2, .75), random(.75, 1.5)), int(random(2, 12))), true, texs[sub]);
		//	tubes[i].setBumpMap(texs[sub]);
		//	tubes[i].setTextureScale(Vec2f(3, .2));
		//	tubes[i].setSpecularMaterial(Col4f(1, 1, 1, 1.0));
		//	tubes[i].setShininess(4);
		//}
		//save("roots", 7);
}


void rootBallStudy01::run() {
	save("roots", 4);
}

// update screen
void rootBallStudy01::display(){
	setBackground(0);
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

	/*push();
	rotate(-getFrameCount()*.06, 0, 1, 0);
	theta = 0;
	for (int i = 0; i < TUBE_COUNT; ++i){
	push();
	translate(cos(theta)*6.2, -8, sin(theta)*6.2);
	scale(3);
	rotate(getFrameCount()*.12, 0, 1, 0);
	tubes[i].display();
	pop();
	theta += TWO_PI / TUBE_COUNT;
	}
	pop(); */
}
