
#include "myApp01.h"

void myApp01::init() {

	//globalAmbient = Col3f(.3, .3, .3);
	shadowsOn();
	// wall
	plane = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(0, 0, 0, 1), 1, 1, "linen.jpg");
	//Plane.textureOn();
	plane.setBumpMap("linen.jpg");
	//Plane.loadBumpMapTexture("shipPlate_normal.jpg");
	plane.setTextureScale(Vec2f(.5));
	//Plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
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

	TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.2, random(3, 6)), 130/*int(random(3, 25))*/);

	tube = ProtoTube(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), spline, .09, 24, t1, false, "metal_flaky_blue.jpg", Vec2f(1, .01));
	tube.setShininess(int(random(6, 20)));
	tube.setBumpMap("metal_flaky_blue.jpg");
	tube.setSpecularMaterial(Col4f(1, 1, 1, 1.0));

	//ProtoCylinder::ProtoCylinder(int detail, Registration reg) :
	cylinder = Cylinder(60, "pitted.jpg", ProtoCylinder::CENTER);
	cylinder.setShininess(1);
	cylinder.setBumpMap("pitted.jpg");
	cylinder.setDiffuseMaterial(Col4f(1, 1, 1, 1.0));
	cylinder.setSpecularMaterial(Col4f(1, 1, 1, 1.0));

	ellipse = ProtoEllipse(Vec3f(), Vec3f(), Dim2f(1, 1),
		Col4f(1, 1, 1, 1), 24);
	ellipse.setDiffuseMap("ship_plate.jpg");
	ellipse.setBumpMap("ship_plate.jpg");
	ellipse.setTextureScale(Vec2f(3, 3));

}

void myApp01::run() {
}

void myApp01::display() {
	background(1.0, .5, 0);

	/*push();
	{*/
		//scale(1.06);
		// shadowsOn();
		// shape display()
		//push();
		//translate(0, 0, -14);
		//scale(13.75, 12.75, 1);
		//rotate(90, 1, 0, 0);
		//plane.display();
		//pop();
//
	arcballBegin(); 
	
	push();
		
		translate(-4, 0, -2);

		rotate(getFrameCount()*.05f, 1, 0, 0);
		rotate(getFrameCount()*.05f, 0, 1, 0);
		rotate(getFrameCount()*.065f, 0, 0, 1);
		scale(4);
		ellipse.display();
		//tube.display();
		
		pop();
		//cylinder.display();
		translate(5, 0, -2);
		ellipse.display();
		arcballEnd();
		//pop();
	/*}
	pop();*/
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

