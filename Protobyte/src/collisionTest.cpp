#include "collisionTest.h"


void collisionTest::init() {
	t = Tri(Vec3(-175 * 2, 100 * 2, -50 * 2), Vec3(-25 * 2, 100 * 2, -150 * 2), Vec3(-100 * 2, -100 * 2, -100 * 2));
	for (int i = 0; i < COUNT; i++){
		orbs[i] = Vec3(random(20, 200), random(-100, 100), random(-100, -50));
		spds[i] = t.C() - orbs[i];
		spds[i].x *= random(.35, 1);
		spds[i].y *= random(.35, 1);
		spds[i].z *= random(.35, 1);
		spds[i] *= .01;
	}

	strokeWeight(3);

	//trace(t.C());
	//trace(t.N());

	int vals[3];
	trace(vals);
	trace(&vals[0]);
}

void collisionTest::run() {
}

void collisionTest::display() {

	background(.75, .85, .95);
	beginArcBall();

	fill(.75, .345, .1);
	for (int i = 0; i < COUNT; i++){

		push();
		translate(orbs[i]);
		noStroke();
		box(1);
		pop();
		fill(.5, .5, 1);
		stroke(.15, .45, .2);
		t.draw(this);
		t.drawNorm(this);

		orbs[i] += spds[i]+random(.6);

		// collision detection/response
		Vec3f pos;
		if (collide(orbs[i], pos)){
			
			// glue to surface

			spds[i] *= -1;
			//spds[i] = Vec3(random(-.3, .3), random(-.3, .3), random(-.3, .3));
		}
	}
	endArcBall();


}

bool collisionTest::collide(const Vec3& orb, Vec3& pos) {
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
		pos = orb;
		trace(pos);
		return (r + t <= 1);
	}
	return false;
}