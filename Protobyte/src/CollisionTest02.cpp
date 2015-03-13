
#include "CollisionTest02.h"

void CollisionTest02::init() {

	globalAmbient = Col3f(.15, .15, .15);

	//light0.setPosition(Vec3f(.1, 300, 0));
	light0.setPosition(Vec3f(0, 150, -50));
	light0.setIntensity(Vec3f(.85, .85, .85));

	light1.setPosition(Vec3f(-10, -400, 0));
	light1.setIntensity(Vec3f(1, 1, 1));

	float theta = 0.0;
	float phi = 0.0;
	for (int i = 0; i < ORB_COUNT; i++){
		float x = sin(theta) * 400;
		float y = -200 + i + sin(theta*random(1.5))*random(50, 40);
		//float y = 0;
		float z = cos(theta) * 400;

		//y' = y*cos q - z*sin q
		//z' = y*sin q + z*cos q

		float ty = y*cos(phi) - z*sin(phi);
		float tz = y*sin(phi) + z*cos(phi);

		orbs[i] = Vec3(x, ty, tz);
		spds[i] = Vec3f() - orbs[i];
		/*spds[i].x *= random(.15, 1.3);
		spds[i].y *= random(.15, 1.3);
		spds[i].z *= random(.15, 1.3);*/
		spds[i] *= .001;
		theta += (TWO_PI / ORB_COUNT)*50;
		phi += (TWO_PI / ORB_COUNT) * 11;
	}

	// ProtoSphere(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
					//const ProtoColor4f col4, const std::string& textureImageURL, 
					//float textureScale, int spines, int spineNodes); 
	
	sphere = ProtoSphere(Vec3f(), Vec3f(), Dim3f(400.0), Col4f(1, 1, 1, 1.0), "metal_flaky_blue.jpg", 1, 34, 34);
	sphere.setBumpMap("metal_flaky_blue.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	sphere.setTextureScale(Vec2f(.2));
	sphere.setAmbientMaterial(Col4f(1, 1, 1, 1.0));
	sphere.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	sphere.setShininess(5);

	faces = sphere.getFaces();
}

void CollisionTest02::run() {
}

void CollisionTest02::display() {

	strokeWeight(.25);
	stroke(.75);
	beginArcBall(); 
	for (int j = 0; j < ORB_COUNT; j++){
		push();
		translate(orbs[j]);
		noFill();
		rect(0, 0, 2, 2);
		pop();
		orbs[j] += spds[j];
	}
	
	push();
	scale(.965);
	sphere.display(WIREFRAME);
	pop();


	// collision detection/response
	for (int i = 0; i < faces.size(); i++){
		for (int j = 0; j < ORB_COUNT; j++){
			if (collide(faces.at(i), orbs[j])){
				// glue to surface
				//spds[j] *= 1;
				spds[j] = 0;
				
				//spds[i] = Vec3(random(-.3, .3), random(-.3, .3), random(-.3, .3));
			}
		}
	}

	strokeWeight(5); 
	stroke(1, .5, .125, .75);
	beginShape();
	for (int i = 0; i < ORB_COUNT; i++){
		curveVertex(orbs[i]);
	}
	endShape();

	endArcBall();

	for (int j = 0; j < ORB_COUNT; j++){
		//trace(spds[j]);
	}

}

bool CollisionTest02::collide(Face3& t, const Vec3& orb) {
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