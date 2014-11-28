
#include "ThanksgivingBeast.h"

void ThanksgivingBeast::init() {

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


	// ribs
	float radius = .107;
	Vec3f v(0, 0, 0);

	int segments = 12; // 60;
	v = Vec3f(0, 0, 0);
	Vec3f spd(0, 0, 0);

	//cps.push_back(v);
	float turbulence = .1f;
	Dim3f size(4.25, 4.25, 4.25);


	float startY = -.5;

	int ribCount = 11;// 17;
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
		spline = Spline3(cps, 3, false, .5);

		TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.02, .95 + (ribRadius*random(.07, .31))), 1/*int(random(1, 3))*/);

		ribs.push_back(ProtoTube(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), spline, .09, 12, t1, true, "pitted.jpg", Vec2f(1, random(.0825, .2))));
		ribs.at(i).setDiffuseMaterial(Col4f(1, 1, 1, .25));
		ribs.at(i).setIsClosed(0);
		ribs.at(i).setSpecularMaterial(Col4f(.4, .275, .1, 1));
		ribs.at(i).setShininess(6);
		ribs.at(i).setBumpMap("pitted.jpg");
		ribs.at(i).setColor(Col4f(1, 1, 1, .25));

		//// rib tendrils
		//std::vector <Vec3> ribCps;
		//for (int j = 0; j < ribs.at(i).getFrenetFrameLength(); j += int(random(1, 3))){
		//	for (int k = 0; k < ribs.at(i).getCrossSectionDetail(); k += 1){
		//		int counter = j*ribs.at(i).getCrossSectionDetail() + k;
		//		ribCps.push_back(ribs.at(i).getVertices().at(counter).pos);
		//		if (i>0){
		//			Vec3 v = ribs.at(i).getVertices().at(counter).pos*.75f;
		//			tempVecs.push_back(v);
		//		}

		//	}

		//}






		//Spline3 ribSpline = Spline3(ribCps, 2, false, .5);
		//TransformFunction ribT = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(random(.09, .15), random(.2, .4)), int(random(1, 12)));
		//ribBands.push_back(ProtoTube(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), ribSpline, .09, 5, ribT, true, "vascular.jpg", Vec2f(1, random(.0825, .2))));
		//ribBands.at(i).setIsClosed(0);
		//ribBands.at(i).setSpecularMaterial(Col4f(.4, .275, .1, 1));
		//ribBands.at(i).setShininess(6);
		//ribBands.at(i).setBumpMap("vascular.jpg");
	}



	// mesh - not working!!
	//std::vector <Vec3> wrapCps;
	//for (int i = 0; i < tempVecs.size(); i += 4){
	//	allVecs.push_back(tempVecs.at(static_cast<int>(random(tempVecs.size()))));
	//}

	//Spline3 wrapSpline = Spline3(allVecs, 12, false, random(.48, .53));
	//TransformFunction wrapT = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(random(.08, .15), random(.15, .3)), static_cast<int>(random(100, 300)));
	//vascularWrap = ProtoTube(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), wrapSpline, .09, 6, wrapT, true, "corrogated_metal2_color.jpg", Vec2f(1, random(.000825, .85)));
	//vascularWrap.setIsClosed(0);
	//vascularWrap.setSpecularMaterial(Col4f(.5, .5, .5, 1));
	//vascularWrap.setShininess(6);
	//vascularWrap.setBumpMap("corrogated_metal2_color.jpg");


}

void ThanksgivingBeast::run() {
}

void ThanksgivingBeast::display() {

	background(1.0, .5, 0);
	
	push();
		/*translate(0, 0, -66);
		scale(13.75, 12.75, 1);
		rotate(90, 1, 0, 0);*/
		//plane.display();
	pop();

	arcballBegin();
	translate(0, 0, -5);
	
	// ribs
	push();
	rotate(195, 0, .75, 1);
	scale(6.25);
	for (int i = 0; i < ribs.size(); ++i){
		ribs.at(i).display();
		//ribBands.at(i).display();
	}
	pop();
	
	
	push();
		rotate(135, 1, .75, 1);
		scale(5.25);
	for (int i = 0; i < ribs.size(); ++i){
		ribs.at(i).display();
		//ribBands.at(i).display();
	}
	pop(); 
	
	push();
	scale(4);
	for (int i = 0; i < ribs.size(); ++i){
		ribs.at(i).display();
		//ribBands.at(i).display();
	}
	pop();

	push();
	rotate(135, 1, .75, .25);
	scale(3.25);
	for (int i = 0; i < ribs.size(); ++i){
		ribs.at(i).display();
		//ribBands.at(i).display();
	}
	pop();

	push();
	rotate(235, .25, .75, 1);
	scale(2.75);
	for (int i = 0; i < ribs.size(); ++i){
		ribs.at(i).display();
		//ribBands.at(i).display();
	}
	pop();

	push();
	rotate(25, .25, .75, 1);
	scale(1.75);
	for (int i = 0; i < ribs.size(); ++i){
		ribs.at(i).display();
		//ribBands.at(i).display();
	}
	pop();
	arcballEnd();

}