#include "collisionTest.h"


void collisionTest::init() {
	t = Tri(Vec3(-175, 100, -50), Vec3(-25, 100, -150), Vec3(-100, -100, -100));
	orb = Vec3(100, 150, 200);
	spd = t.C() - orb;
	spd *= .002;
	strokeWeight(3);

	trace(t.C());
	trace(t.N());
}

void collisionTest::run() {
}

void collisionTest::display() {

	background(.75, .85, .95);
	beginArcBall();
	orb += spd;
	fill(.75, .345, .1);
	push();
	translate(orb);
	noStroke();
	box(6);
	pop();
	fill(.5, .5, 1);
	stroke(.15, .45, .2);
	t.draw(this);
	t.drawNorm(this);
	endArcBall();


}