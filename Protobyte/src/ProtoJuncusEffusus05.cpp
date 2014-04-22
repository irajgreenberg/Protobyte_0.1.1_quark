/*!  \brief  ProtoJuncusEffusus05.h:
Form study 3 for Zhulong Sattellite Exhibition: 4/2014
Protobyte Library v02

Created by Ira on 3/26/14.
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

#include "ProtoJuncusEffusus05.h"

void ProtoJuncusEffusus05::init() {
	globalAmbient = ProtoLight(Col4f(.25f, .19f, .27f, 1)); // slight violet color

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

	juncsCount = 32;// 9;// 36;
	float ht = 2.25;
	int segs = 8;
	float step = ht / segs;
	float theta = 0;
	float radius = .107;
	float x, y, z;
	float chi = 0;

	// thanks to gamblin colors
	for (int i = 0; i < juncsCount; ++i){
		theta = TWO_PI / juncsCount * i;
		y = -ht / 2;
		std::vector <Vec3> cps;
		radius = .14;
		chi = 0;
		for (int j = 0; j < segs; ++j){
			z = (cos(theta + sin(chi)*random(j))*radius + random(-.08, .08)*j) * (random(1, 3.5) / (j + 1));
			y += step;
			x = (sin(theta + sin(chi)*random(j))*radius + random(-.08, .08)*j) * (random(1, 3.5) / (j + 1));
			cps.push_back(Vec3(x, y, z));
			theta += TWO_PI / segs;
			radius += .085;
			chi += PI / 2;
		}
		std::string skin;
		int dice = int(random(12));
		if (dice == 0)
		{
			skin = "aluminum_foil.jpg";
		}
		else if (dice == 1){
			skin = "gold_foil2.jpg";
		}
		else if (dice == 2){
			skin = "metal_grate.jpg";
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
			skin = "bronze_fans.jpg";
		}
		else if (dice == 8){
			skin = "gold_foil2.jpg";
		}
		else if (dice == 9){
			skin = "metal_screwHeads.jpg";
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
		juncs.push_back(ProtoJuncusEffusus(Col4f(.7, .7, .6, 1), skin, skin, cps, ProtoJuncusEffusus::MEDIUM));
	}




	// For exporting geometry to STL
	std::vector<Tup4v> vs;
	for (int i = 0; i < juncs.size(); ++i){
		bool isTubule = false;
		if (i % 4 == 0)isTubule = false; else isTubule = true;
		std::vector<Tup4v> temp = juncs.at(i).getGeomData(isTubule, true);
		vs.insert(vs.end(), temp.begin(), temp.end());
	}

	// export geometry data to STL
	//export(vs, STL);


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
}

void ProtoJuncusEffusus05::run() {
	setBackground(.82, .81, .82);

	// save high resolution rendering
	// currently only works with max 999 tiles
	render(); 
	
	static int frameCounter = 0;
	if (frameCounter++ < 1){
		 save("juncs", 13);
	}

	

}


void ProtoJuncusEffusus05::render(int scaleFactor){

	push(); 
	translate(0, 0, 0);
	rotate(getFrameCount()*.02, 0, 1, 0);
	for (int i = 0; i < juncsCount; ++i){
		if (i % 3 == 0){
			juncs.at(i).display(SURFACE, SURFACE, 2, 1);
		}
		else {
			juncs.at(i).display(SURFACE, SURFACE, 4, 1);
		}
	}
	pop();
}
