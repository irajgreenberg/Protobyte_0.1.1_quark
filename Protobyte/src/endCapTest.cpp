
#include "endCapTest.h"
struct MyQuad {
	Vec3 vecs[4];

	MyQuad() {}

	MyQuad(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& v3){
		vecs[0] = v0;
		vecs[1] = v1;
		vecs[2] = v2;
		vecs[3] = v3;
	}

	MyQuad(Vec3 vecs[]){
		std::copy(vecs, vecs + 4, this->vecs);
	}
};

const int VEC_COUNT = 9;
Vec3 vecs[VEC_COUNT];



MyQuad quads[VEC_COUNT - 1];
float thickness = 19;

Vec3 dv;
Vec3 past;

void endCapTest::init() {
	for (int i = 0; i < VEC_COUNT; ++i){
		vecs[i] = Vec3(random(-getWidth() / 2 + 100, getWidth() / 2 - 100), random(-getHeight() / 2 + 100, getHeight() / 2 - 100), 0);
	}

	// test 1



	

}

void endCapTest::run() {
}

void endCapTest::display() {
	strokeWeight(2);
	background(.75, .25, .65);
	noFill();
	stroke(.75, 0, 0);
	

	beginShape(); 
	for (int i = 0; i < VEC_COUNT; ++i){
		vertex(vecs[i]);
	}
	endShape();

	for (int i = 0; i < VEC_COUNT; ++i){
		if (i>0){


			dv = vecs[i] - vecs[i-1];

			if (i > 1){
				dv += past;
			}
			//trace(dv);
			dv.normalize();
			float x = dv.x;
			dv.x = -dv.y;
			dv.y = x;
			//trace(dv);
			dv *= thickness;

			//vertex(vecs[i-1]);
			//vertex(vecs[i]);
			//endShape(CLOSE);

			if (i == 1){
				stroke(0, 0, .75);
			}
			else {
				stroke(.75, 0, 0);
			}
			
			beginShape();
			vertex(vecs[i-1]);
			vertex(vecs[i-1] - dv);
			endShape(CLOSE);

			beginShape();
			vertex(vecs[i-1]);
			vertex(vecs[i-1] + dv);
			endShape();
		}
		if (i > 1){
			past = dv;
		}
	}



}