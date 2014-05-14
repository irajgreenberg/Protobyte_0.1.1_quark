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
	globalAmbient = Col3f(.25f, .19f, .47f); // slight violet color

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

	//170, 150
	//rootBallCore = RootBall(Vec3f(), Vec3f(), Dim3f(1.55f), Col4f(.9f), 1, 30, .2, Tup2f(.5, 2.25));
	TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.2f, .75f), 35); // local, so can't be sent as reference
	//rootBallCore.setTransformFunction(t1);

	rootBall = RootBall(Vec3f(), Vec3f(), Dim3f(1.345f), Col4f(.9f), 1, 40, .2, Tup2f(.2, 3), "leather2.jpg", 1);
	TransformFunction t2 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.14f, .22f), 80); // local, so can't be sent as reference
	rootBall.setTransformFunction(t2);
	//std::vector<Tup4v> vs = rootBall.getGeomData();

	// export geometry data to 
	//std::vector<Tup4v> vs;
	//std::vector<Tup4v> temp = rootBallCore.getGeomData();
	//vs.insert(vs.end(), temp.begin(), temp.end());
	//std::vector<Tup4v> temp2 = rootBall.getGeomData();
	//vs.insert(vs.end(), temp2.begin(), temp2.end());
	//export(vs, STL);

	plane = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 1, 1), 1, 1, "leather2.jpg", 1);
	plane.textureOn();
	plane.setBumpMap("shipPlate.jpg");
}

void ProtoRootBall02::run() {
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


void ProtoRootBall02::render(int scaleFactor){

	push(); 
	translate(0, 0, 0);
	scale(3);
	rotate(getFrameCount()*.02, 0, 1, 0);
	//rootBallCore.display();
	//rootBall.display();
	pop();

	rotate(90, 1, 0, 0);
	plane.display();
}
