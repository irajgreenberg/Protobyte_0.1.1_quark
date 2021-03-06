
#include "myApp01.h"

const int pointCount = 6;
Col4f fCols[pointCount];
Vec3 pts[pointCount];
Vec3 pts2[pointCount];
float curveRadius = 700;

float c3 = .0001;

void myApp01::init() {

	for (int i = 0; i < pointCount; ++i){
		fCols[i] = Col4f(random(), random(), random(), 1);
	}

	for (int i = 0; i < pointCount; i++){
		pts[i] = Vec3(random(-curveRadius, curveRadius), random(-curveRadius, curveRadius), random(-curveRadius, curveRadius));
		pts2[i] = Vec3(random(-curveRadius, curveRadius), random(-curveRadius, curveRadius), random(-curveRadius, curveRadius));
	}

	//_initUniforms(&shader3D);
	globalAmbient = Col3f(.65, .65, .65);

	//light0.setPosition(Vec3f(.1, 300, 0));
	light0.setPosition(Vec3f(0, 150, -50));
	light0.setIntensity(Vec3f(.85, .85, .85));

	light1.setPosition(Vec3f(-10, -400, 0));
	light1.setIntensity(Vec3f(1, 1, 1));
	//camera0.setPosition(Vec3f(0, 0, 500));


	shadowsOn();
	// wall
	plane = GroundPlane(Vec3(), Vec3(), Dim2f(50, 50), Col4f(1, 1, 1, 1), 1, 1, "yellow2.jpg", Vec2f(1, 1));
	//GroundPlane()
	plane.textureOn();
	plane.setBumpMap("yellow2.jpg");
	plane.loadBumpMapTexture("yellow2.jpg");
	plane.setTextureScale(Vec2f(.05));
	plane.setAmbientMaterial(Col4f(.3, .3, .3, 1.0));
	plane.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	plane.setShininess(6);
	//trace("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS =", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);


	//tube = ProtoTube();

	float theta = 0;
	float radius = .307;
	Vec3f v(0, 0, 0);

	int segments = 50;
	v = Vec3f(0, 0, 0);
	Vec3f spd(0, 0, 0);
	std::vector <Vec3> cps;
	cps.push_back(v);
	float turbulence = 4.5f;
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

	TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(1.2, random(3, 8)), 40/*int(random(3, 25))*/);

	tube = ProtoTube(Vec3f(), Vec3f(), Dim3f(1), Col4f(1, 1, 1, .85), spline, .09, 24, t1, true, "metal_panel01.jpg", Vec2f(3, .025));
	tube.setShininess(int(random(6, 27)));
	tube.setDiffuseMaterial(Col4f(1, 1, 1, .2));
	tube.setBumpMap("metal_panel01.jpg");
	tube.setSpecularMaterial(Col4f(1, 1, 1, 1.0));

	//tube = ProtoTube(Vec3f(), Vec3f(), Dim3f(1), Col4f(.55, .55, .55, 1), spline, .09, 24, t1, true);


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

	path1 = ProtoPath2(this);
	path1.stroke(1.0, .75, .125);
	path1.fill(0, .5, .75);
	theta = 0;
	int sides = 21;
	path1.moveTo(cos(theta) * random(-13, 13), sin(theta) * random(-13, 13));
	for (int i = 0; i < sides; ++i){
		theta += TWO_PI / sides;
		path1.lineTo(cos(theta) * random(-13, 13), sin(theta) * random(-13, 13));

	}
	path1.end(CLOSE);

	//trace("GL_MAX_TEXTURE_UNITS =", GL_MAX_TEXTURE_UNITS);

	// pre-load textures for box TEST

	textureScale.x = .3;
	textureScale.y = .3;

	tex1 = Texture("pitted.jpg", ProtoTexture::DIFFUSE_MAP);
	tex2 = Texture("pitted.jpg", ProtoTexture::BUMP_MAP);

	tex3 = Texture("metal_blue.jpg", ProtoTexture::DIFFUSE_MAP);
	tex4 = Texture("metal_blue.jpg", ProtoTexture::BUMP_MAP);

	std::vector<Vec3f> splineVecs;
	for (int i = 0; i < 500; ++i){
		splineVecs.push_back(Vec3(random(-300, 300), random(-300, 300), random(-300, 300)));
	}
	spline2 = ProtoSpline3(splineVecs, 15, false, 0.5);

	
}
void myApp01::run() {

}

void myApp01::display() {
	
	background(0.2);
	translate(0, 0, -100);

	beginArcball();
	////push();
	////translate(0, 0, 0);


	////fill(0.0, .75, 1);
	////ellipseDetail = 36;
	////for (int i = 0; i < 50; i++){
	////	fill(1.0, 1.0, 0); 
	////	ellipse(random(-400, 400), random(-300, 300), 75, 75);
	////	fill(1.0, 0, 1);
	////	rect(random(-400, 400), random(-300, 300), 75, 75);
	////}


	////fill(1.0, .75, 0.0);
	////ellipse(0, 0, 200, 200, CENTER);
	////fill(1.0, .75, 1.0);
	////ellipse(200, 0, 200, 200, CENTER);
	////fill(.5, .75, 0.5);
	////ellipse(400, 0, 200, 200, CENTER);
	////rect(0, 0, 200, 200);
	////pop();

	////push();
	////translate(0, 0, 0);
	////scale(200);
	////fill(0.0, 1.0, .65); 
	////rect(1, 1, CENTER);
	////rect(1, 1.5, 1, 1, CENTER);
	////fill(1, 1, 0);
	////ellipse(1, 1, .5, .5, CENTER);
	////pop();

	push();
	translate(0, -400, 0);
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
		scale(90);
		//tube.display();
	}
	pop();
	////
	////
	////glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//push();
	//{
	//	//cylinder.display();
	//	/*translate(50, 0, 0);
	//	rotate(-getFrameCount()*.5f, 1, 0, 0);
	//	rotate(getFrameCount()*.05f, 0, 1, 0);
	//	rotate(-getFrameCount()*.065f, 0, 0, 1);
	//	scale(100);*/

	//	//shader3D.setShaders("bumpmapping.vs.glsl", "bumpmapping.fs.glsl");
	//	//shader3D.bind();
	//	//_initUniforms(&shader3D); 
	//	//ellipse.display();
	//	//myPath.display();

	//}
	//pop();
	////GLUquadric* quadric = gluNewQuadric();
	////gluPartialDisk(quadric,50,100,20,5,0,270);

	//rotate(-getFrameCount()*.5f, 1, 0, 0);
	//rotate(getFrameCount()*.5f, 0, 1, 0);
	//rotate(-getFrameCount()*.5f, 0, 0, 1);

	//push();
	//path1.display();
	//pop();


	//float xStep = W / float(COLUMNS);
	//float yStep = H / float(ROWS);
	//float zStep = D / float(LAYERS);
	//strokeWeight(1);
	//for (int i = 0, ind = 0; i < ROWS; ++i){
	//	for (int j = 0; j < COLUMNS; ++j){
	//		for (int k = 0; k < LAYERS; ++k){
	//			fill(colors[ind]);
	//			push();
	//			translate(-W/2+xStep*j, -H/2+yStep*i, -D/2+zStep*k);
	//			rotate(rots[ind], 1, 1, 1);
	//			scale(1.25);
	//			if (ind % 2 == 0){
	//				//noFill();
	//				stroke(colors[ind]);
	//				rect(-5, -5, 10, 10);
	//			}
	//			else {
	//				fill(colors[ind]);
	//				stroke(1);
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

	fill(1, 0, .25);
	stroke(0, .9, .85);
	//noStroke();
	noFill();
	strokeWeight(3);

	push();
	//scale(3);
	
	/*beginShape();
	float theta = 0;
	int sides = 12;
	fill(1, 1, 0);
	for (int i = 0; i < sides; ++i){
		vertex(cos(theta) * abs(sin(theta) * 65), sin(theta) * abs(sin(theta) * 65), sin(theta) * sin(theta) * 50);
		theta += TWO_PI / sides;
	}
	endShape();*/

	noFill();
	stroke(.5, .45, .6);
	strokeWeight(6);
	ellipseDetail = 24;
	//rect(0, 0, 50, 50);
	pop();


	noFill();
	push();
	scale(0.5);
	stroke(0, 1, 1);
	strokeWeight(10);
	float step = 2000.0 / pointCount;
	beginShape();
	float theta = 0.0;
	curveTension(0);
	for (int i = 0; i < pointCount; ++i){
		stroke(fCols[i]);
		/*vertex(pts[i].x, pts[i].y, pts[i].z);
		if (i % 15 == 0) {*/
		curveDetail(i);
		curveVertex(-1000+step*i, -200+sin(theta) * 150, 0);
			theta += TWO_PI*2 / pointCount;
		//}
	}
	endShape(OPEN);

	theta = 0;
	beginShape();
	strokeWeight(2);
	theta = 0.0;
	curveTension(-1); 
	//curveDetail(int(getFrameCount()*.001));
	for (int i = 0; i < pointCount; ++i){
		stroke(fCols[i]);
		//strokeWeight(i*2);
		//curveVertex(-1000 + step*i, 200+sin(theta) * 150, 0);
		theta += TWO_PI*2 / pointCount;
	}
	endShape(OPEN);

	theta = 0;
	beginShape();
	theta = 0.0;
	for (int i = 0; i < pointCount; ++i){
		stroke(fCols[i]);
		//vertex(-1000 + step*i, sin(theta) * 150, 0);
		theta += TWO_PI * 2 / pointCount;
	}
	endShape(OPEN);



	beginShape();
	strokeWeight(3);
	for (int i = 0; i <20; i++){
		stroke(fCols[i]);
		curveVertex(pts[i]);
		//vertex(pts2[i]);
	}
	endShape(false);

	pop();


	push();
	strokeWeight(.25);
	stroke(.85, .12, .4, .4);
	scale(6);
	quad(0, 0, 0, -40, 40, -40, 40, 0);
	quad(0, 0, 0, -40, 40, -40, 40, 0, CORNER_BL);
	quad(0, 0, 0, -40, 40, -40, 40, 0, CORNER_BR);
	quad(0, 0, 0, -40, 40, -40, 40, 0, CORNER_TR);
	quad(0, 0, 0, -40, 40, -40, 40, 0, CORNER);
	pop();

	strokeWeight(1);
	stroke(1, 1, 0);
	//noFill();
	//noStroke();
	fill(.4, .3, .1, .85);
	//noFill();

	//enable2DRendering();



	//GLuint bumpMap = boxBumpMapTexture.getTextureID();



	push();
	translate(-150, 0, 0);
	diffuseTexture(tex3);
	bumpTexture(tex2);
	//noTexture();
	//box(120, 20, 60);
	pop();

	push();
	stroke(1, 0, 1);
	//fill(1, 1, 0, .5);
	strokeWeight(2);
	translate(150, 0, 0);
	diffuseTexture(tex1);
	bumpTexture(tex4);
	//noTexture();
	//box(120, 40, 200);
	pop();
	//disable2DRendering();

	
	push(); 
	//spline2.display(4);
	//spline2.displayInterpPts(12);
	pop();


	endArcball();
	//...
	//	path.display();


}

void myApp01::mousePressed(){
	//save("Test_image01", 4);
}

void myApp01::mouseReleased(){
	//trace("mouse released");
	//save("protoRibs", 9);
}

void myApp01::mouseMoved() {
	//glViewport(1000, 1000, 400, 400);
	//trace("mouse moving");
}

void myApp01::mouseDragged() {
	//trace("mouse dragging");
}

