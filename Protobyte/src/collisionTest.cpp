#include "collisionTest.h"


void collisionTest::init() {
	Vec3f avgPos;
	for (int i = 0; i < TRI_COUNT; i++){
		float x = random(-95, 95);
		float y = random(-95, 95);
		float z = random(-350, -250);
		Vec3 v0 = Vec3(x, y, z);
		Vec3 v1 = Vec3(x + 35, y + 15, z - 5);
		Vec3 v2 = Vec3(x + 17.5, y - 25, z - 10);
		ts[i] = Tri(v0 *= 2.3, v1 *= 2.3, v2 *= 2.3);
		avgPos += ts[i].C();
	}
	avgPos /= TRI_COUNT;

	for (int i = 0; i < ORB_COUNT; i++){
		orbs[i] = Vec3(random(100, 200), random(-100, 100), random(-50));
		spds[i] = avgPos - orbs[i];
		spds[i].x *= random(.15, 1.3);
		spds[i].y *= random(.15, 1.3);
		spds[i].z *= random(.15, 1.3);
		spds[i] *= .01;
	}
	strokeWeight(3);

	//trace(t.C());
	//trace(t.N());
}

void collisionTest::run() {
}

void collisionTest::display() {

	background(.75, .85, .95);
	beginArcBall();

	strokeWeight(.25);
	for (int j = 0; j < ORB_COUNT; j++){
		push();
		translate(orbs[j]);
		noStroke();
		box(10);
		pop();
		orbs[j] += spds[j];
	}

	fill(.75, .345, .1);
	for (int i = 0; i < TRI_COUNT; i++){

		fill(.5, .5, 1);
		stroke(0);
		ts[i].draw(this);
		stroke(1, 0, 0);
		ts[i].drawNorm(this, 9);
	}

	// collision detection/response
	for (int i = 0; i < TRI_COUNT; i++){
		for (int j = 0; j < ORB_COUNT; j++){
			if (collide(ts[i], orbs[j])){
				// glue to surface
				spds[j] *= 1;
				spds[j] = 0;
				//spds[i] = Vec3(random(-.3, .3), random(-.3, .3), random(-.3, .3));
			}
		}
	}
	endArcBall();
}

bool collisionTest::collide(Tri& t, const Vec3& orb) {
	Vec3f tmp = orb;
	tmp.normalize();
	Vec3 d = t.C() - orb;
	d.normalize();

	// 1st check on infinite plane
	if (t.N().dot(d) > 0){

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