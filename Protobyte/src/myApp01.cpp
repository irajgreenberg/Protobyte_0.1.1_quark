
#include "myApp01.h"

void myApp01::init() {



	//_initUniforms(&shader3D);
	globalAmbient = Col3f(.7, .7, .7);

	light0.setPosition(Vec3f(.1, 300, .1));
	//light0.setPosition(Vec3f(-14.2, 2.5, 8));
	light0.setIntensity(Vec3f(1, 1, 1));


	shadowsOn();
	// wall
	plane = GroundPlane(Vec3(), Vec3(), Dim2f(800, 700), Col4f(0, 0, 0, 1), 1, 1, "linen.jpg");
	plane.textureOn();
	plane.setBumpMap("linen.jpg");
	plane.loadBumpMapTexture("shipPlate_normal.jpg");
	plane.setTextureScale(Vec2f(.5));
	plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	plane.setSpecularMaterial(Col4f(.85, .85, .85, 1.0));
	plane.setShininess(45);
	//trace("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS =", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);


	tube = ProtoTube();

	float theta = 0;
	float radius = .107;
	Vec3f v(0, 0, 0);

	int segments = 20;
	v = Vec3f(0, 0, 0);
	Vec3f spd(0, 0, 0);
	std::vector <Vec3> cps;
	cps.push_back(v);
	float turbulence = 2.5f;
	Dim3f size(3.25, 3.25, 3.25);
	Spline3 spline;

	for (int j = 0; j < segments; ++j){
		spd = Vec3(random(-turbulence*.1, turbulence*.1), random(-turbulence*.1, turbulence*.1), random(-turbulence*.1, turbulence*.1));
		v += spd + Vec3f(sin(theta)*random(-turbulence, turbulence), -sin(theta)*random(-turbulence, turbulence), cos(theta)*random(-turbulence, turbulence));
		cps.push_back(Vec3(v.x, v.y, v.z));
		if (v.mag() > size.w / 2.5f){
			float shift = (size.w / 2.5f) / v.mag();
			v *= shift;
			spd *= -(1 + random(-turbulence*.1, turbulence*.1));
		}

		theta += PI / 15.0f;
	}

	spline = Spline3(cps, 12, false, .5);

	TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(2.2, random(3, 8)), 40/*int(random(3, 25))*/);

	tube = ProtoTube(Vec3f(), Vec3f(), Dim3f(1), Col4f(.2, .275, 1, 1), spline, .09, 24, t1, true, "metal_flaky_blue.jpg", Vec2f(1, .01));
	tube.setShininess(int(random(6, 20)));
	tube.setBumpMap("metal_flaky_blue.jpg");
	tube.setSpecularMaterial(Col4f(1, 1, 1, 1.0));

	//ProtoCylinder::ProtoCylinder(int detail, Registration reg) :
	cylinder = Cylinder(60, "pitted.jpg", ProtoCylinder::CENTER);
	cylinder.setShininess(1);
	cylinder.setBumpMap("pitted.jpg");
	cylinder.setDiffuseMaterial(Col4f(1, 1, 1, 1.0));
	cylinder.setSpecularMaterial(Col4f(1, 1, 1, 1.0));

	//ellipse = ProtoEllipse(Vec3f(), Vec3f(), Dim2f(1, 1),
	//Col4f(1, 0, .75, 1), 24);
	//ellipse.setDiffuseMaterial(Col4f(1.0, 0.0, 0.0, 1.0));
	//ellipse.setDiffuseMap("ship_plate.jpg");
	//ellipse.setBumpMap("ship_plate.jpg");
	//ellipse.setTextureScale(Vec2f(3, 3));

	//ProtoPath3(const Col4f& col4, const std::vector<Vec3f>& pathVecs);
	//myPath = ProtoPath3(Col4f(.2, .75, 1, 1), cps);

	//shader3D.unbind();
	//shader3D.bind();
	//_initUniforms(&shader3D);

	//tesselator = gluNewTess();

	for (int i = 0, ind = 0; i < ROWS; ++i){
		for (int j = 0; j < COLUMNS; ++j){
			for (int k = 0; k < LAYERS; ++k){
				colors[ind] = Col4f(random(), random(), random(), 1.0);
				rots[ind] = 0;
				rotSpds[ind++] = random(-8, 8);
			}
		}
	}
	//fill(.5, .75, .34);
	//beginPath();
	//vertex(23, 45, 104);
	//vertex(223, 45, 104);

	//vertex(23, 45, 104);
	//vertex(23, 345, 104);
	//vertex(3, 45, -104);
	//endPath();
	// 

	// for testing only
	//GLdouble myStar[5][6] = {
	//	0.6f, -0.1f, -2.0f, 1.0f, 1.0f, 1.0f,
	//	1.35f, 1.4f, -2.0f, 1.0f, 1.0f, 1.0f,
	//	2.1f, -0.1f, -2.0f, 1.0f, 1.0f, 1.0f,
	//	0.6f, 0.9f, -2.0f, 1.0f, 1.0f, 1.0f,
	//	2.1f, 0.9f, -2.0f, 1.0f, 1.0f, 1.0f };

	//GLdouble quad[4][6] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, };

	//
	//iraInit();
	//iraBeginPolygon();
	//iraBeginContour();
	//iraAddContourVertex(quad, 4);
	//iraEndContour();
	//iraEndPolygon();
	//iraEnd();

	//path1 = ProtoPath2(this);
	//path1.stroke(1.0, .75, .125);
	//path1.fill(0, .5, .75);
	//theta = 0;
	//int sides = 21;
	//path1.moveTo(cos(theta) * random(-13, 13), sin(theta) * random(-13, 13));
	//for (int i = 0; i < sides; ++i){
	//	theta += TWO_PI / sides;
	//	path1.lineTo(cos(theta) * random(-13, 13), sin(theta) * random(-13, 13));
	//	
	//}
	//path1.end(CLOSE);



}

void myApp01::run() {

}

void myApp01::display() {
	background(1.0, .5, 0);
	//translate(0, 0, -200);

	beginArcball();
	//push();
	//translate(0, 0, 0);


	//fill(0.0, .75, 1);
	//ellipseDetail = 36;
	//for (int i = 0; i < 50; i++){
	//	fill(1.0, 1.0, 0); 
	//	ellipse(random(-400, 400), random(-300, 300), 75, 75);
	//	fill(1.0, 0, 1);
	//	rect(random(-400, 400), random(-300, 300), 75, 75);
	//}


	//fill(1.0, .75, 0.0);
	//ellipse(0, 0, 200, 200, CENTER);
	//fill(1.0, .75, 1.0);
	//ellipse(200, 0, 200, 200, CENTER);
	//fill(.5, .75, 0.5);
	//ellipse(400, 0, 200, 200, CENTER);
	//rect(0, 0, 200, 200);
	//pop();

	//push();
	//translate(0, 0, 0);
	//scale(200);
	//fill(0.0, 1.0, .65); 
	//rect(1, 1, CENTER);
	//rect(1, 1.5, 1, 1, CENTER);
	//fill(1, 1, 0);
	//ellipse(1, 1, .5, .5, CENTER);
	//pop();

	push();
	translate(0, -300, 0);
	scale(20, 1, 20);
	//plane.display();
	pop();
	//rotate(getFrameCount()*.05f, 1, 0, 0);
	//rotate(getFrameCount()*.05f, 0, 1, 0);
	//rotate(getFrameCount()*.065f, 0, 0, 1);
	push();
	{
		translate(-50, 0, 0);

		rotate(getFrameCount()*.05f, 1, 0, 0);
		rotate(getFrameCount()*.05f, 0, 1, 0);
		rotate(getFrameCount()*.065f, 0, 0, 1);
		scale(100);

		//tube.display();
	}
	pop();
	//
	//
	push();
	{
		//cylinder.display();
		/*translate(50, 0, 0);
		rotate(-getFrameCount()*.5f, 1, 0, 0);
		rotate(getFrameCount()*.05f, 0, 1, 0);
		rotate(-getFrameCount()*.065f, 0, 0, 1);
		scale(100);*/

		//shader3D.setShaders("bumpmapping.vs.glsl", "bumpmapping.fs.glsl");
		//shader3D.bind();
		//_initUniforms(&shader3D); 
		//ellipse.display();
		//myPath.display();

	}
	pop();
	//GLUquadric* quadric = gluNewQuadric();
	//gluPartialDisk(quadric,50,100,20,5,0,270);

	rotate(-getFrameCount()*.5f, 1, 0, 0);
	rotate(getFrameCount()*.5f, 0, 1, 0);
	rotate(-getFrameCount()*.5f, 0, 0, 1);

	//push();
	//path1.display();
	//pop();


	//float xStep = W / float(COLUMNS);
	//float yStep = H / float(ROWS);
	//float zStep = D / float(LAYERS);
	//for (int i = 0, ind = 0; i < ROWS; ++i){
	//	for (int j = 0; j < COLUMNS; ++j){
	//		for (int k = 0; k < LAYERS; ++k){
	//			fill(colors[ind]);
	//			push();
	//			translate(-W/2+xStep*j, -H/2+yStep*i, -D/2+zStep*k);
	//			rotate(rots[ind], 1, 1, 1);
	//			if (ind % 2 == 0){
	//				rect(0, 0, 13, 13, CENTER);
	//			}
	//			else {
	//				//ellipse(0, 0, 13, 13);
	//				path1.fill(colors[ind]);
	//				path1.display();
	//			}
	//			pop();
	//			rots[ind] += rotSpds[ind];
	//			ind++;
	//		}
	//	}
	//}
	// tranform matrix not reset here?

	//fill(1, 0, .25);
	//stroke(0, .9, .85);
	//noStroke();
	//noFill();
	strokeWeight(3);
	push();
	beginShape();
	float theta = 0;
	int sides = 12;
	for (int i = 0; i < sides; ++i){
		vertex(cos(theta) * abs(sin(theta) * 65), sin(theta) * abs(sin(theta) * 65), sin(theta) * sin(theta)*50);
		theta += TWO_PI / sides;
	}
	endShape(OPEN);
	
	/*fill(0, 0, 1);
	beginPath();
	theta = 0;
	for (int i = 0; i < sides; ++i){
		vertex(cos(theta) * abs(sin(theta) * 65), sin(theta) * abs(sin(theta) * 65), 0);
		theta += TWO_PI / sides;
	}
	endPath(0);*/

	ellipseDetail = 24;
	//ellipse(0, 0, 200, 200);
	pop();


	endArcball();




	//...
	//	path.display();
}

void myApp01::mousePressed(){
	//trace("mouse pressed");
}

void myApp01::mouseReleased(){
	//trace("mouse released");
	//save("protoRibs", 9);
}

void myApp01::mouseMoved() {
	//trace("mouse moving");
}

void myApp01::mouseDragged() {
	//trace("mouse dragging");
}

