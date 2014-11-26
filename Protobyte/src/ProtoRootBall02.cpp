/*!  \brief  ProtoRootBall02.h:
Root ball study
Protobyte Library v02

Created by Ira on 4/30/14.
Copyright (c) 2014 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.
Some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#include "ProtoRootBall02.h"

#include <thread>


void ProtoRootBall02::init() {

	//170, 150
	// set Materials for composite objects - or setup as multiple inheritance/interface
	rootBallCore = RootBall(Vec3f(), Vec3f(), Dim3f(2.55f), Col4f(.9f), 1, 30, .2, Tup2f(.5, 2.25), "shipPlate_yellow.jpg", 8);
	TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.2f, .75f), 3); // local, so can't be sent as reference
	rootBallCore.setTransformFunction(t1);


	//rootBall = RootBall(Vec3f(), Vec3f(), Dim3f(1.345f), Col4f(.9f), 1, 40, .2, Tup2f(.2, 3), "vascular3.jpg", 1);
	TransformFunction t2 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.14f, .22f), 80); // local, so can't be sent as reference
	//rootBall.setTransformFunction(t2);
	//std::vector<Tup4v> vs = rootBall.getGeomData();

	// export geometry data to 
	//std::vector<Tup4v> vs;
	//std::vector<Tup4v> temp = rootBallCore.getGeomData();
	//vs.insert(vs.end(), temp.begin(), temp.end());
	//std::vector<Tup4v> temp2 = rootBall.getGeomData();
	//vs.insert(vs.end(), temp2.begin(), temp2.end());
	//export(vs, STL);

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
	ground = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 1, 1), 1, 1, "pink2.jpg");
	//plane.textureOn();
	ground.setBumpMap("pink2.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	ground.setTextureScale(Vec2f(.25));
	//plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	ground.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	ground.setShininess(3);
	//trace("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS =", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);


	std::string texs[] = { "pebbles.jpg", "gold_foil2.jpg", "vascular.jpg", "greenCrocSkin.jpg", "pink2.jpg", "metal_screwHeads.jpg", "woodPlank.jpg", "metal_blue.jpg", "shipPlate_yellow.jpg", "reptile2_invert.jpg", "corroded_metal.jpg", "giraffe.jpg", "shipPlate.jpg", "metal_grate.jpg" };

	for (int i = 0; i < W*H*D; ++i){
		int sub = int(random(14));
		toroids[i] = Toroid(Vec3f(), Vec3f(random(45), random(45), random(45)), Dim3f(3, 3, 3), Col4f(.5, .5, .5, 1), 12, 12, 3, 1.2, texs[sub]);
		toroids[i].setBumpMap(texs[sub]);
		//toroids[i].setBumpMap("grime.jpg");
		toroids[i].setDiffuseMaterial(Col4f(.65, .75, 1, 1.0));
		toroids[i].setSpecularMaterial(Col4f(1, 1, 1, 1.0));
		toroids[i].setTextureScale(Vec2f(random(.25, 8.5)));
		toroids[i].setShininess(int(random(15, 40)));
	}



}


void ProtoRootBall02::run() {
	static int frameCounter = 0;
	if (frameCounter++ < 1){
		//save("roots", 13);
		/*std::thread t(&this->save, "roots", 13);
		t.join();*/
	}



}


void ProtoRootBall02::display(){

	
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


	float width = 5;
	float height = 5;
	float depth = 5;

	float colSpan = width / (W - 1);
	float rowSpan = height / (H - 1);
	float layerSpan = depth / (D - 1);
	int counter = 0;
	
	arcballBegin();
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
	arcballEnd();
}


