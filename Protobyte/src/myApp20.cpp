
#include "myApp20.h"

void myApp20::init() {
	background(0.5);
}

void myApp20::run() {
}

void myApp20::display() {
	rect(100, 100, 50, 50);
	rect(200, -50, 50, 34.5);
	rect(0, 0, 100, 100, CENTER);
	ellipse(-100, -200, 100, 100);
	ellipse(-75, -300, 10, 10);
	ellipse(0, 0, 10, 10);
	ellipse(200, 0, 10, 10);
}