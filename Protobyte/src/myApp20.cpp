
#include "myApp20.h"

void myApp20::init() {
	background(0.5);
}

void myApp20::run() {
}

void myApp20::display() {
	//RECT
		//rect(float radius1, float radius2)
			//rect(width, height);
				//Draws rectangle centered at origin (in center of window)
				//rectangle's width and height are equal to parameters passed to it
	
	rect(Vec2(100, 200), Vec2(300, 300));



	ellipse(100, 200, 10, 10);
	ellipse(300, 100, 10, 10);
	//ellipse(200, 0, 10, 10);

}