/*!  \brief  ProtoRootBall01.h:
Root ball study
Protobyte Library v02

Created by Ira on 4/27/14.
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

#include "ProtoRootBall01.h"

#include <thread>


void ProtoRootBall01::init() {
	globalAmbient = Col3f(0, 0, 0); // slight violet color

	// light0
	light0.setPosition(Vec3f(0, 0, 1));
	light0.setDiffuse(Col4f(1, 1, 1, 1.0f));
	light0.setAmbient(Col4f(.5, .3, .3, 1.0));
	light0.setSpecular(Col4f(1, 1, 1, 1.0));
	light0.on();

	light1.setPosition(Vec3f(-1, 0, 1));
	light1.setDiffuse(Col4f(.2, .5, .65, 1.0f));
	light1.setAmbient(Col4f(.3, .3, .3, 1.0));
	light1.setSpecular(Col4f(1, 1, 1, 1.0));
	light1.on();

	rootCount = 1;// 22;// 9;// 36
	int segs = 180;
	float theta = 0;
	float radius = .107;
	Vec3f v(0,0,0);
	float ballRadius = 2;

	
	// thanks to gamblin colors
	for (int i = 0; i < rootCount; ++i){
		theta = 0;
		v = Vec3f(0, 0, 0);
		Vec3f spd(0,0,0);
		std::vector <Vec3> cps;
		cps.push_back(v);

		for (int j = 0; j < segs; ++j){
			//trace("Vec3f(x, y, z).mag() =", Vec3f(v.x, v.y, v.z).mag());
				spd = Vec3(random(-.02, .02), random(-.02, .02), random(-.02, .02));
				v += spd + Vec3f(sin(theta)*random(-.2, .2), -sin(theta)*random(-.2, .2), cos(theta)*random(-.2, .2));
				//trace("v before shift =", v);
				cps.push_back(Vec3(v.x, v.y, v.z));
			if (v.mag() > ballRadius/2.5){
				float shift = (ballRadius/2.5) / v.mag();
				//trace("shift = ", shift);
				v *= shift;
				//trace("v after shift =", v);
				//spd = Vec3f(random(TWO_PI), random(TWO_PI), random(TWO_PI));
				spd *= -(1+random(-.02,.02));
				//spd.normalize();
			}
			
			theta += PI / 15.0f;
		}
		std::string skin;
		int dice = int(random(12));
		if (dice == 0)
		{
			skin = "greenCrocSkin.jpg";
		}
		else if (dice == 1){
			skin = "moss.jpg";
		}
		else if (dice == 2){
			skin = "cross_hatch.jpg";
		}
		else if (dice == 3){
			skin = "aluminum_foil.jpg";
		}
		else if (dice == 4){
			skin = "gold_foil.jpg";
		}
		else if (dice == 5){
			skin = "corroded_shipPlate.jpg";
		}
		else if (dice == 6){
			skin = "ship_plate2.jpg";
		}
		else if (dice == 7){
			skin = "pebbles.jpg";
		}
		else if (dice == 8){
			skin = "gold_foil2.jpg";
		}
		else if (dice == 9){
			skin = "leather2.jpg";
		}
		else if (dice == 10){
			skin = "brushed_metal.jpg";
		}
		else if (dice == 11){
			skin = "metal_grate.jpg";
		}
		else {
			skin = "brushed_metal.jpg";
		}
		//juncs.push_back(ProtoJuncusEffusus(Col4f(.7, .7, .6, 1), skin, skin, cps, ProtoJuncusEffusus::LOW));

		//ProtoTube(pos, rot, size, col4, path, radius, crossSectionDetail, transFuncObj, isClosed, textureImageURL)
		Spline3 s(cps, 5, false, .5);
		//const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed
		tubes.push_back(ProtoTube(Vec3f(), Vec3f(), Dim3f(1, 1, 1), Col4f(1, 1, 1, 1), s, .02, 9, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, ProtoTuple2f(random(.1, .75), random(.25, 6)), 50), false, skin));
		tubes.at(i).textureOn();

	}




	// For exporting geometry to STL
	// JuncusEffusus Roots
	std::vector<Tup4v> vs;
	/*for (int i = 0; i < juncs.size(); ++i){
		bool isTubule = false;
		if (i % 4 == 0)isTubule = false; else isTubule = true;
		std::vector<Tup4v> temp = juncs.at(i).getGeomData(isTubule, true);
		vs.insert(vs.end(), temp.begin(), temp.end());
	}
*/
	// plain tube roots
	for (int i = 0; i <tubes.size(); ++i){
		bool isTubule = true;
		//if (i % 4 == 0)isTubule = false; else isTubule = true;
		std::vector<Tup4v> temp = tubes.at(i).getGeomData();
		vs.insert(vs.end(), temp.begin(), temp.end());
	}

	// export geometry data to STL
	export(vs, STL);


	// Locations for page placement
	float arrayW = 9 * .37;
	float arrayH = 13 * .39;
	float gapX = arrayW / (COLUMNS - 1);
	float gapY = arrayH / (ROWS - 1);
	for (int i = 0; i < ROWS; ++i){
		for (int j = 0; j < COLUMNS; ++j){
			locs[i*COLUMNS + j] = Vec3(-arrayW / 2 + gapX*(j), arrayH / 2 - gapY*(i), 0);
			thetas[i*COLUMNS + j] = random(360.0);
			juncIDCounts[i*COLUMNS + j] = static_cast<int>(random(3, 24));
		}
	}


	//sphere = ProtoSphere(Vec3f(), Vec3f(), Dim3f(2, 2, 2), Col4f(.7, .7, .7, 1), 12, 12);
}

void ProtoRootBall01::run() {
	setBackground(.82, .81, .82);

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


void ProtoRootBall01::render(int scaleFactor){

	push(); 
	translate(0, 0, 0);
	scale(3);
//	sphere.display(WIREFRAME);
	rotate(getFrameCount()*.02, 0, 1, 0);

	for (int i = 0; i < tubes.size(); ++i){
		tubes.at(i).display();
	}


	/*for (int i = 0; i < juncs.size(); ++i){
		if (i % 3 == 0){
			juncs.at(i).display(SURFACE, SURFACE, 2, 1);
		}
		else {
			juncs.at(i).display(SURFACE, SURFACE, 4, 1);
		}
	}*/
	pop();
}
