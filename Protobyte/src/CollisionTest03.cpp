
#include "CollisionTest03.h"

void CollisionTest03::init() {

	globalAmbient = Col3f(.13, .13, .13);

	//light0.setPosition(Vec3f(.1, 300, 0));
	light0.setPosition(Vec3f(0, 150, 50));
	light0.setIntensity(Vec3f(1, .95, .95));

	//light1.setPosition(Vec3f(-10, -400, 100));
	//light1.setIntensity(Vec3f(.1, .1, .1));

	float theta = 0.0;
	float phi = 0.0;
	for (int i = 0; i < ORB_COUNT; i++){
		float x = sin(theta) * random(380, 420);
		float y = -200 + i + sin(theta*random(1.5))*random(32, 32);
		//float y = 0;
		float z = cos(theta) * random(380, 420);

		//y' = y*cos q - z*sin q
		//z' = y*sin q + z*cos q

		float ty = y*cos(phi) - z*sin(phi);
		float tz = y*sin(phi) + z*cos(phi);

		orbs.push_back(Vec3(x, ty, tz));
		spds.push_back(Vec3f() - orbs[i]);
		/*spds[i].x *= random(.15, 1.3);
		spds[i].y *= random(.15, 1.3);
		spds[i].z *= random(.15, 1.3);*/
		spds.at(i) *= .001;
		theta += (TWO_PI / ORB_COUNT) * 50;
		phi += (TWO_PI / ORB_COUNT) * 11;
	}

	// ProtoSphere(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
	//const ProtoColor4f col4, const std::string& textureImageURL, 
	//float textureScale, int spines, int spineNodes); 

	//sphere
	sphere = ProtoSphere(Vec3f(), Vec3f(), Dim3f(600.0), Col4f(1, 1, 1, .65), "metal_flaky_blue.jpg", 1, 20, 20);
	sphere.setBumpMap("metal_flaky_blue.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	sphere.setTextureScale(Vec2f(.2));
	sphere.setAmbientMaterial(Col4f(1, 1, 1, 1.0));
	sphere.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	sphere.setShininess(5);
	faces = sphere.getFaces();

	

	// toroid
	// ProtoToroid(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4,
	// int ringCount, int ringDetail, float ringRadius, float ringThickness, const // //std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));
	
	toroid = ProtoToroid(Vec3f(), Vec3f(), Dim3f(400.0), Col4f(1, 1, 1, 1.0), 30, 30, 200, 60, "metal_flaky_blue.jpg", Vec2f(1, 1));
	toroid.setBumpMap("metal_flaky_blue.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	toroid.setTextureScale(Vec2f(.2));
	toroid.setAmbientMaterial(Col4f(1, 1, 1, 1.0));
	toroid.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	toroid.setShininess(5);
	//faces = toroid.getFaces();


	while (counter++ < 800) {
		for (int j = 0; j < ORB_COUNT; j++){
			orbs.at(j) += spds.at(j);
		}
		
		// collision detection/response
		for (int i = 0; i < faces.size(); i++){
			for (int j = 0; j < ORB_COUNT; j++){

				if (collide(faces.at(i), orbs.at(j))){
					// glue to surface
					spds.at(j) = 0;
				}
			}
		}

		if (counter >798){
			std::vector<Vec3f> tempVecs;
			for (int i = 0; i < ORB_COUNT; i++){
				tempVecs.push_back(orbs.at(i));
			}
			spline = ProtoSpline3(tempVecs, 4, FALSE, .5);
		}
	}

	ProtoTransformFunction tf(ProtoTransformFunction::SINUSOIDAL, ProtoTuple2f(.65, 2.65), 620);
	tube = ProtoTube(spline, 3.125, 6, tf, true, "vascular5.jpg", Vec2f(.5, .001));
	tube.setBumpMap("vascular5.jpg");
	tube.setAmbientMaterial(Col4f(1, 1, 1, 1.0));
	tube.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	tube.setShininess(30);


	// vein
	//outer sphere
	outerSphere = ProtoSphere(Vec3f(), Vec3f(), Dim3f(610.0), Col4f(1, 1, 1, .65), "metal_flaky_blue.jpg", 1, 20, 20, Vec3f(.02, .02, .02));
	outerSphere.setBumpMap("metal_flaky_blue.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	outerSphere.setTextureScale(Vec2f(.2));
	outerSphere.setAmbientMaterial(Col4f(1, 1, 1, 1.0));
	outerSphere.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	outerSphere.setShininess(5);
	outerSphereFaces = outerSphere.getFaces();
	theta = 0.0;
	phi = 0.0;
	orbs.clear();
	spds.clear();
	for (int i = 0; i < VEIN_COUNT; i++){
		float x = sin(theta) * random(380, 420);
		float y = -200 + i + sin(theta*random(1.5))*random(32, 32);
		//float y = 0;
		float z = cos(theta) * random(380, 420);

		//y' = y*cos q - z*sin q
		//z' = y*sin q + z*cos q

		float ty = y*cos(phi) - z*sin(phi);
		float tz = y*sin(phi) + z*cos(phi);

		orbs.push_back(Vec3(x, ty, tz));
		spds.push_back(Vec3f() - orbs.at(i));
		/*spds[i].x *= random(.15, 1.3);
		spds[i].y *= random(.15, 1.3);
		spds[i].z *= random(.15, 1.3);*/
		spds.at(i) *= .001;
		theta += (TWO_PI / VEIN_COUNT) * 50;
		phi += (TWO_PI / VEIN_COUNT) * 11;
	}

	counter = 0;
	while (counter++ < 900) {
		for (int j = 0; j < VEIN_COUNT; j++){
			orbs.at(j) += spds.at(j);
		}

		// collision detection/response
		for (int i = 0; i < outerSphereFaces.size(); i++){
			for (int j = 0; j < VEIN_COUNT; j++){

				if (collide(outerSphereFaces.at(i), orbs.at(j))){
					// glue to surface
					spds.at(j) = 0;
				}
			}
		}

		if (counter >898){
			std::vector<Vec3f> tempVecs;
			for (int i = 0; i < VEIN_COUNT; i++){
				tempVecs.push_back(orbs.at(i));
			}
			spline = ProtoSpline3(tempVecs, 2, FALSE, .5);
		}
	}

	tf = ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, ProtoTuple2f(.075, .29), 620);
	vein = ProtoTube(spline, 3.125, 4, tf, true, "metal_flaky_blue.jpg", Vec2f(.5, .001));
	vein.setColor(Col4(.01, .35, .55, .75));
	vein.setBumpMap("metal_flaky_blue.jpg");
	vein.setAmbientMaterial(Col4f(1, 1, 1, 1.0));
	vein.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	vein.setShininess(30);


	// vein 2
	theta = 0.0;
	phi = 0.0;
	orbs.clear();
	spds.clear();
	for (int i = 0; i < VEIN_COUNT; i++){
		float x = sin(theta) * random(380, 420);
		float y = -200 + i + sin(theta*random(1.5))*random(32, 32);
		//float y = 0;
		float z = cos(theta) * random(380, 420);

		//y' = y*cos q - z*sin q
		//z' = y*sin q + z*cos q

		float ty = y*cos(phi) - z*sin(phi);
		float tz = y*sin(phi) + z*cos(phi);

		orbs.push_back(Vec3(x, ty, tz));
		spds.push_back(Vec3f() - orbs.at(i));
		/*spds[i].x *= random(.15, 1.3);
		spds[i].y *= random(.15, 1.3);
		spds[i].z *= random(.15, 1.3);*/
		spds.at(i) *= .001;
		theta += (TWO_PI / VEIN_COUNT) * 50;
		phi += (TWO_PI / VEIN_COUNT) * 11;
	}

	counter = 0;
	while (counter++ < 900) {
		for (int j = 0; j < VEIN_COUNT; j++){
			orbs.at(j) += spds.at(j);
		}

		// collision detection/response
		for (int i = 0; i < outerSphereFaces.size(); i++){
			for (int j = 0; j < VEIN_COUNT; j++){

				if (collide(outerSphereFaces.at(i), orbs.at(j))){
					// glue to surface
					spds.at(j) = 0;
				}
			}
		}

		if (counter >898){
			std::vector<Vec3f> tempVecs;
			for (int i = 0; i < VEIN_COUNT; i++){
				tempVecs.push_back(orbs.at(i));
			}
			spline = ProtoSpline3(tempVecs, 2, FALSE, .5);
		}
	}

	tf = ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, ProtoTuple2f(.075, .29), 620);
	vein2 = ProtoTube(spline, 3.125, 4, tf, true, "metal_flaky_blue.jpg", Vec2f(.5, .001));
	vein2.setColor(Col4(.01, .55, .35, .75));
	vein2.setBumpMap("metal_flaky_blue.jpg");
	vein2.setAmbientMaterial(Col4f(1, 1, 1, 1.0));
	vein2.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	vein2.setShininess(30);
}

void CollisionTest03::run() {
}

void CollisionTest03::display() {
	background(1);
	strokeWeight(.25);
	stroke(.75);
	translate(0, 0, -25);
	beginArcBall();
	//for (int j = 0; j < ORB_COUNT; j++){
	//	push();
	//	translate(orbs[j]);
	//	noFill();
	//	rect(0, 0, 2, 2);
	//	pop();
	//	//orbs[j] += spds[j];
	//}

	//push();
	//scale(.935);
	////sphere.display();
	////toroid.display();
	//pop();


	//// collision detection/response
	//for (int i = 0; i < faces.size(); i++){
	//	for (int j = 0; j < ORB_COUNT; j++){
	//		if (collide(faces.at(i), orbs[j])){
	//			// glue to surface
	//			//spds[j] *= 1;
	//			spds[j] = 0;

	//			//spds[i] = Vec3(random(-.3, .3), random(-.3, .3), random(-.3, .3));
	//		}
	//	}
	//}

	strokeWeight(5);
	stroke(1, .5, .125, .75);
	//std::vector<Vec3f> tempVecs;
	////beginShape();
	//for (int i = 0; i < ORB_COUNT; i++){
	//	//curveVertex(orbs[i]);
	//	tempVecs.push_back(orbs[i]);
	//}
	////endShape();
	//spline = ProtoSpline3(tempVecs, 6, FALSE, .5);
	////spline.display();
	////ProtoTube::ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed, const std::string& textureImageURL, const Vec2f& textureScale)
	//tube = ProtoTube(spline, .8, 12, true, "white_tile.jpg", Vec2f(1, .01));
	tube.display();
	vein.display();
	vein2.display();
	endArcBall();


}

bool CollisionTest03::collide(Face3& t, const Vec3& orb) {
	//
	Vec3f tmp = orb;
	tmp.normalize();
	Vec3 d = t.getCentroid() - orb;
	d.normalize();


	// 1st check on infinite plane
	if (t.getNorm().dot(d) > 0){

		// next check within triangle
		Vec3 u = t.v1 - t.v0;
		Vec3 v = t.v2 - t.v0;
		Vec3 w = orb - t.v0;

		Vec3 vw = v.cross(w);
		Vec3 vu = v.cross(u);

		if (vw.dot(vu) < 0){
			return false;
		}

		Vec3 uw = u.cross(w);
		Vec3 uv = u.cross(v);

		if (uw.dot(uv) < 0){
			return false;
		}

		float denom = uv.mag();
		float r = vw.mag() / denom;
		float t = uw.mag() / denom;

		return (r + t <= 1);
	}
	return false;
}