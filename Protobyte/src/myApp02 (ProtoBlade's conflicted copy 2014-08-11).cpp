
#include "myApp02.h"

void myApp02::init() {

	globalAmbient = Col3f(1, .1, .1);
	shadowsOn();
	// wall
	plane = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 0, 1), 1, 1, "orange.jpg");
	//Plane.textureOn();
	plane.setBumpMap("white_tile.jpg");
	plane.setTextureScale(Vec2f(.5));
	//Plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	plane.setSpecularMaterial(Col4f(.1, .1, .1, 1.0));
	plane.setShininess(100);


	//tube = ProtoTube();

	float radius = .107;
	Vec3f v(0, 0, 0);

	int segments = 10; // 60;
	v = Vec3f(0, 0, 0);
	Vec3f spd(0, 0, 0);

	//cps.push_back(v);
	float turbulence = .1f;
	Dim3f size(4.25, 4.25, 4.25);


	float startY = -.5;

	int ribCount = 3;// 17;
	float ribSpan = 4.5;
	float ribRadius = 0;
	float ribRadiusMax = 2.0;
	float ribTheta = 0;

	float ribGap = ribSpan / ribCount;

	for (int i = 0; i < ribCount; ++i){

		float theta = 0, weaveTheta = 0;
		std::vector <Vec3> cps;
		Spline3 spline;
		ribRadius = fabs(sin(ribTheta) * ribRadiusMax);
		for (int j = 0; j < segments; ++j){
			//spd = Vec3(random(-turbulence*.1, turbulence*.1), 0, random(-turbulence*.1, turbulence*.1));
			//v = spd + Vec3f(sin(theta)*2+random(-turbulence, turbulence), startY+=.1, cos(theta)*2+random(-turbulence, turbulence));
			//cps.push_back(Vec3(v.x, v.y, v.z));
			cps.push_back(Vec3(sin(theta) * ribRadius, -ribSpan / 2 + ribGap*i + sin(weaveTheta) * .15, cos(theta) * ribRadius));
			theta += TWO_PI / segments;
			//weaveTheta += j*j*j*.125 * PI / 180;
			weaveTheta += TWO_PI / segments * (ribRadius * 4);
		}
		//trace("ribradius = ", ribRadius*4);
		ribTheta += PI / ribCount;

		//spline = Spline3(cps, 4, false, .5);
		spline = Spline3(cps, 5, false, .5);

		TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.02, .95 + (ribRadius*random(.07, .31))), 1/*int(random(1, 3))*/);

		ribs.push_back(ProtoTube(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), spline, .09, 12, t1, true, "pitted.jpg", Vec2f(1, random(.0825, .2))));
		ribs.at(i).setIsClosed(0);
		ribs.at(i).setSpecularMaterial(Col4f(.4, .275, .1, 1));
		ribs.at(i).setShininess(6);
		ribs.at(i).setBumpMap("pitted.jpg");

		// rib tendrils
		std::vector <Vec3> ribCps;
		for (int j = 0; j < ribs.at(i).getFrenetFrameLength(); j += int(random(1, 3))){
			for (int k = 0; k < ribs.at(i).getCrossSectionDetail(); k += int(random(1, 3))){
				ribCps.push_back(ribs.at(i).getVertices().at(j*ribs.at(i).getCrossSectionDetail() + k).pos);
			}
		}

		Spline3 ribSpline = Spline3(ribCps, 2, false, .5);
		TransformFunction ribT = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(random(.05, .2), random(..3, .5)), int(random(5, 12)));
		ribBands.push_back(ProtoTube(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), ribSpline, .09, 12, ribT, true, "vascular.jpg", Vec2f(1, random(.0825, 1))));
		ribBands.at(i).setIsClosed(0);
		ribBands.at(i).setSpecularMaterial(Col4f(.8, .275, .1, 1));
		ribBands.at(i).setShininess(5);
		ribBands.at(i).setBumpMap("vascular.jpg");
	}

	
	//yRot = xRot = 0;
	//xRotLast = yRotLast = 0;
	//mouseXIn = mouseYIn = 0;

}

void myApp02::run() {
	//save("protoRibs", 9);  //use 9
}

void myApp02::display() {
	background(1.0, .5, 0);
	scale(1.06);
		// shadowsOn();
		// shape display()
		push();
		{
			translate(0, 0, -16);
			scale(13.75, 12.75, 1);
			rotate(90, 1, 0, 0);
			plane.display();
		}
		pop();

		push();
		{
			translate(0, 0, 2);

			/*rotate(xRot, 1, 0, 0);
			rotate(yRot, 0, 1, 0);*/
			//rotate(getFrameCount()*.065f, 0, 0, 1);
			scale(3, 3, 3);

			//tube.display();

			//cylinder.display();

			//ellipse.display();
			arcballBegin();
			for (int i = 0; i < ribs.size(); ++i){
				ribs.at(i).display();
				ribBands.at(i).display();
			}

			

			arcballEnd();
		}
		pop();

}

void myApp02::mousePressed(){
	//trace("mouse pressed");
}

void myApp02::mouseReleased(){
	//trace("mouse released");
	//save("protoRibs", 9);
}

void myApp02::mouseMoved() {
	//trace("mouse moving");
}

void myApp02::mouseDragged() {
	//trace("mouse dragging");
}