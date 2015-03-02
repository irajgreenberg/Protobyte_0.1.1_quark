
#include "CollisionTest02.h"

void CollisionTest02::init() {
	float theta = 0.0;
	for (int i = 0; i < ORB_COUNT; i++){
		orbs[i] = Vec3(sin(theta)*400, -200+i+sin(theta*random(1.5))*random(10, 20), cos(theta)*400);
		spds[i] = Vec3f() - orbs[i];
		/*spds[i].x *= random(.15, 1.3);
		spds[i].y *= random(.15, 1.3);
		spds[i].z *= random(.15, 1.3);*/
		spds[i] *= .01;
		theta += (TWO_PI / ORB_COUNT)*5;
	}

	// ProtoSphere(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
					//const ProtoColor4f col4, const std::string& textureImageURL, 
					//float textureScale, int spines, int spineNodes); 
	
	sphere = ProtoSphere(Vec3f(), Vec3f(), Dim3f(400.0), Col4f(1, 1, 1, 1), "vascular.jpg", 1, 12, 12);
	sphere.setBumpMap("vascular.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	sphere.setTextureScale(Vec2f(.2));
	sphere.setAmbientMaterial(Col4f(.62, .62, .62, 1.0));
	sphere.setSpecularMaterial(Col4f(.95, .95, .85, 1.0));
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
	sphere.display();
	pop();


	// collision detection/response
	for (int i = 0; i < faces.size(); i++){
		for (int j = 0; j < ORB_COUNT; j++){
			if (collide(faces.at(i), orbs[j])){
				// glue to surface
				spds[j] *= 1;
				spds[j] = 0;
				//spds[i] = Vec3(random(-.3, .3), random(-.3, .3), random(-.3, .3));
			}
		}
	}

	strokeWeight(1.2); 
	stroke(1, .125, .125, .95);
	beginShape();
	for (int i = 0; i < ORB_COUNT; i++){
		curveVertex(orbs[i]);
	}
	endShape();

	endArcBall();

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