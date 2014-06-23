
#include "rootBallStudy01.h"

#include <thread>


void rootBallStudy01::init() {

	
	TransformFunction t2 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.14f, .22f), 80); // local, so can't be sent as reference
	
	// wall
	plane = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 1, 1), 1, 1, "leather2.jpg");
	//plane.textureOn();
	plane.setBumpMap("leather2.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	plane.setTextureScale(Vec2f(.5));
	//plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	plane.setSpecularMaterial(Col4f(1, .9, 1, 1.0));
	plane.setShininess(4);
	//trace("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS =", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

	// ground
	ground = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 1, 1), 1, 1, "metal_screwHeads.jpg");
	//plane.textureOn();
	ground.setBumpMap("metal_screwHeads.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	ground.setTextureScale(Vec2f(.05));
	//plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	ground.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	ground.setShininess(3);

	std::string texs[] = { "pebbles.jpg", "gold_foil2.jpg", "vascular.jpg", "greenCrocSkin.jpg", "pink2.jpg", "metal_screwHeads.jpg", "woodPlank.jpg", "metal_blue.jpg", "shipPlate_yellow.jpg", "reptile2_invert.jpg", "corroded_metal.jpg", "giraffe.jpg", "shipPlate.jpg", "metal_grate.jpg" }; 
	
	
	const int cps = 14;
	float len = 3;
	float seg = len / cps;
	
	std::vector<Vec3> vecs;
	for (int i = 0; i < cps; ++i){
		vecs.push_back(Vec3(random(-.03, .03), seg*i, random(-.03, .03)));
	}
	
	for (int i = 0; i < TUBE_COUNT; ++i){
		int sub = int(random(14));
		tubes[i] = Tube(Spline3(vecs, 5, false, 1), .2, 4, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(random(.2, .75), random(.75, 1.5)), int(random(2, 12))), true, texs[sub], Vec2f(1, .05));
		tubes[i].setBumpMap(texs[sub]);
		//tubes[i].setTextureScale(Vec2f(1, .25));
		tubes[i].setSpecularMaterial(Col4f(1, 1, 1, 1.0));
		tubes[i].setShininess(4);
	}

	//, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(1, 4), int(random(2, 4)))


		

		for (int i = 0; i < W*H*D; ++i){
			int sub = int(random(14));
			toroids[i] = Toroid(Vec3f(), Vec3f(random(45), random(45), random(45)), Dim3f(3, 3, 3), Col4f(.5, .5, .5, 1), 12, 12, 3, 1.2, texs[sub], Vec2f(2.5, 2.5));
			toroids[i].setBumpMap(texs[sub]);
			//toroids[i].setBumpMap("grime.jpg");
			toroids[i].setDiffuseMaterial(Col4f(.65, .75, 1, 1.0));
			toroids[i].setSpecularMaterial(Col4f(1, 1, 1, 1.0));
			toroids[i].setTextureScale(Vec2f(random(.25, 8.5)));
			toroids[i].setShininess(int(random(15, 40)));
		}

		createShadowMap();

}




void rootBallStudy01::run() {

	
	setBackground(0);

	// save high resolution rendering
	// currently only works with max 999 tiles
	//
	//std::thread t(&ProtoBaseApp::render);
	//t.join();
	render();

	static int frameCounter = 0;
	if (frameCounter++ < 1){
		//save("roots", 13);
		/*std::thread t(&this->save, "roots", 13);
		t.join();*/
	}



}


void rootBallStudy01::render(int scaleFactor){

	//push();
	//rotate(getFrameCount()*.15f, 0, 1, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowBufferID);
	//clear depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);
	//reset viewport to the shadow map texture size
	glViewport(0, 0, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);

	// enable front face culling for shadowing
	glCullFace(GL_FRONT);

	glUniform1i(shaderPassFlag_U, 1); // controls render pass in shader

	//glUniform1i(shadowMap_U, 5);

	//// wall
	//push();
	//translate(0, 0, -14);
	//scale(13.75, 12.75, 1);
	//rotate(90, 1, 0, 0);
	//plane.display();
	//pop();

	//// ground 
	//push();
	//translate(0, -7, 5);
	//scale(13.75, 1, 10);
	//ground.display();
	//pop();


	float theta = 0;
	push();
	rotate(-getFrameCount()*.06, 0, 1, 0);
	theta = 0;
	for (int i = 0; i < TUBE_COUNT; ++i){
		push();
		translate(cos(theta)*6.2, -8, sin(theta)*6.2);
		scale(3);
		rotate(getFrameCount()*.5, 0, 1, 0);
		tubes[i].display();
		pop();
		theta += TWO_PI / TUBE_COUNT;
	}
	pop();

	float width = 5;
	float height = 5;
	float depth = 5;

	float colSpan = width / (W - 1);
	float rowSpan = height / (H - 1);
	float layerSpan = depth / (D - 1);
	int counter = 0;

	push();
	rotate(getFrameCount()*.15f, 0, 1, 0);
	rotate(getFrameCount()*.165f, 0, 0, 1);
	rotate(getFrameCount()*.05f, 1, 0, 0);
	for (int i = 0; i < W; ++i){
		for (int j = 0; j < H; ++j){
			for (int k = 0; k < D; ++k){
				push();
				translate(colSpan*i - width / 2, rowSpan*j - height / 2, layerSpan*k - depth / 2);
				scale(.2);
				rotate(-getFrameCount()*.75, toroids[counter].getRotation().x, toroids[counter].getRotation().y, toroids[counter].getRotation().z);
				toroids[counter].display();
				pop();
				counter++;
			}
		}
	}

	pop();

	//pop();
	//renable back face culling
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDrawBuffer(GL_BACK_LEFT);
	glViewport(0, 0, getWidth(), getHeight());

	glCullFace(GL_BACK);
	//glDisable(GL_CULL_FACE);

	glUniform1i(shaderPassFlag_U, 0); // controls render pass in shader
	//glUniform1i(shadowMap_U, 0);

	
	
	// wall
	push();
	translate(0, 0, -14);
	scale(13.75, 12.75, 1);
	rotate(90, 1, 0, 0);
	plane.display();
	pop();

	// ground 
	push();
	translate(0, -7, 5);
	scale(13.75, 1, 10);
	ground.display();
	pop();


	push();
	rotate(-getFrameCount()*.06, 0, 1, 0);
	theta = 0;
	for (int i = 0; i < TUBE_COUNT; ++i){
		push();
		translate(cos(theta)*6.2, -8, sin(theta)*6.2);
		scale(3);
		rotate(getFrameCount()*.5, 0, 1, 0);
		tubes[i].display();
		pop();
		theta += TWO_PI / TUBE_COUNT;
	}
	pop();


	counter = 0;

	push();
	rotate(getFrameCount()*.15f, 0, 1, 0);
	rotate(getFrameCount()*.165f, 0, 0, 1);
	rotate(getFrameCount()*.05f, 1, 0, 0);
	for (int i = 0; i < W; ++i){
		for (int j = 0; j < H; ++j){
			for (int k = 0; k < D; ++k){
				push();
				translate(colSpan*i - width / 2, rowSpan*j - height / 2, layerSpan*k - depth / 2);
				scale(.2);
				rotate(-getFrameCount()*.75, toroids[counter].getRotation().x, toroids[counter].getRotation().y, toroids[counter].getRotation().z);
				toroids[counter].display();
				pop();
				counter++;
			}
		}
	}

	pop();



}


