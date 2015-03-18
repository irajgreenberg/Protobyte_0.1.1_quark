
#include "trailExperiment01.h"

void trailExperiment01::init() {

	plane = ProtoGroundPlane(Vec3f(0, -300, 0), Vec3f(), Dim2f(500, 500),
		Col4f(.5, .4, .6, 1), 10, 10, "white_tile.jpg");

	for (int i = 0; i < VEIN_COUNT; ++i){
		Vec3f orb(0, 850, 0);
		float gravity = random(-.53, -.28);
		float friction = random(.96, .99);
		float damping = random(.275, .59);
		std::vector<Vec3> orbs;
		Vec3f spd(random(-4.04, 4.04), random(-6, -4), random(-4.04, 4.04));
		for (int j = 0; j < 270; ++j){
			Vec3f jitter(random(-20.04, 20.04), random(-1.9, -1.0), random(-20.04, 20.04));
			if (j % 5 == 0){
				orbs.push_back(orb);
			}
			spd.y += gravity;
			orb += spd + jitter;
			if (orb.y < -200){
				orb.y = -200;
				spd.y *= -1;
				spd.y *= damping;
				spd.x *= friction;
				spd.z *= friction;
			}
		}
		spline = ProtoSpline3(orbs, 3, FALSE, .5);
		ProtoTransformFunction tf(ProtoTransformFunction::LINEAR, ProtoTuple2f(random(3.4, 4.5), random(.085, .15)), 1);
		if (i % 3 == 0){
			veins.push_back(ProtoTube(spline, 3.125, 6, tf, true, "shipPlate_yellow.jpg", Vec2f(.5, .1)));
			veins.at(veins.size() - 1).setBumpMap("shipPlate_yellow.jpg");
		}
		else if (i % 5 == 0){
			veins.push_back(ProtoTube(spline, 3.125, 6, tf, true, "textures/skin.jpg", Vec2f(.5, .1)));
			veins.at(veins.size() - 1).setBumpMap("textures/skin.jpg");
		}
		else if (i % 7 == 0){
			veins.push_back(ProtoTube(spline, 3.125, 6, tf, true, "metal_flaky_blue.jpg", Vec2f(.5, .1)));
			veins.at(veins.size() - 1).setBumpMap("metal_flaky_blue.jpg");
		}
		else if (i % 9 == 0){
			veins.push_back(ProtoTube(spline, 3.125, 6, tf, true, "textures/rock.jpg", Vec2f(.5, .1)));
			veins.at(veins.size() - 1).setBumpMap("textures/rock.jpg");
		}
		else {
			veins.push_back(ProtoTube(spline, 3.125, 6, tf, true, "vascular5.jpg", Vec2f(.5, .1)));
			veins.at(veins.size() - 1).setBumpMap("vascular5.jpg");
		}

		veins.at(veins.size() - 1).setDiffuseMaterial(Col4f(1, 1, 1, 1.0));
		veins.at(veins.size() - 1).setAmbientMaterial(Col4f(1, 1, 1, 1.0));
		veins.at(veins.size() - 1).setSpecularMaterial(Col4f(1, 1, 1, 1.0));
		veins.at(veins.size() - 1).setShininess(3);
	}
}

void trailExperiment01::run() {
}

void trailExperiment01::display() {
	translate(0, 0, -600);
	strokeWeight(5);
	stroke(1, .5, .125, .75);
	beginArcBall();
	for (int i = 0; i < VEIN_COUNT; ++i){
		veins.at(i).display();
	}
	//veins.at(0).display();
	endArcBall();
}

bool trailExperiment01::collide(Face3& t, const Vec3& orb) {
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