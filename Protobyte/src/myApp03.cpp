
#include "myApp03.h"

void myApp03::init() {

	/*for (int i = 0; i < 6; ++i) {
		vertex(random(-50, 50), random(-50, 50));
	}*/
	toroid = Toroid(Vec3f(), Vec3f(), Dim3f(8, 8, 8), Col4f(.5f, .4567f, .6f, 1.0f), 32, 32, 10, 4);
}

void myApp03::run() {
}

void myApp03::display() {
	background(1.0, .5, 0);
	translate(0, 0, -100);
	scale(5.26);
	//plot example 
	//stroke();
	//fill();
	arcBallBegin();
	toroid.display();
	arcBallEnd(); 
	
	//begin(); // path or shape?
	//for (int i = 0; i < 6; ++i) {
	//	vertex(random(-50, 50), random(-50, 50));
	//}
	//end();	

	
}


void myApp03::mousePressed() {
}

void myApp03::mouseReleased() {
}

void myApp03::mouseMoved() {
}

void myApp03::mouseDragged() {
}