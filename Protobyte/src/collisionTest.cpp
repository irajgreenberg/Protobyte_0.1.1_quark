#include "collisionTest.h"


void collisionTest::init() {
	t = Tri(Vec3(-175, 100, -50), Vec3(-25, 100, -150), Vec3(-100, -100, -100));
	for (int i = 0; i < COUNT; i++){
		orbs[i] = Vec3(random(20, 200), random(-100, 100), random(-100, -50));
		spds[i] = t.C() - orbs[i];
		spds[i].x *= random(.03);
		spds[i].y *= random(.03);
		spds[i].z *= random(.03);
		spds[i] *= .1;
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

		orbs[i] += spds[i];
		if (collide(orbs[i])){
			spds[i] *= -1;
			spds[i] = Vec3(random(-.3, .3), random(-.3, .3), random(-.3, .3));
		}
	}
	endArcBall();


}

bool collisionTest::collide(const Vec3& orb) {
	Vec3f tmp = orb;
	tmp.normalize();
	Vec3 d = t.C() - orb;
	d.normalize();
	if (t.N().dot(d) < 0){
		return false;
	}
	else {
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