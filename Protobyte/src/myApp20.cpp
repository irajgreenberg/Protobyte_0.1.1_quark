
#include "myApp20.h"

void myApp20::init() {
	setBackground(0.7);


	setFrameRate(5.0);

	std::cout << "width = " << getWidth() << std::endl;
	std::cout << "height = " << getHeight() << std::endl;
	std::cout << "size = " << getSize() << std::endl;

	std::cout << "canvasWidth = " << getCanvasWidth() << std::endl;
	std::cout << "canvasHeight = " << getCanvasHeight() << std::endl;
	std::cout << "canvasSize = " << getCanvasSize() << std::endl;

	std::cout << "windowFrameSize = " << getWindowFrameSize() << std::endl;

	std::cout << "frameRate = " << getFrameRate() << std::endl;

	x = - (getWidth() / 2 );
	y = 0;

	topCornerX = x;
	topCornerY = getHeight() / 2;
}

void myApp20::run() {
}

void myApp20::display() {
	strokeColor = Col4(1);
	fillColor = red;
	isStroke = true;
	lineWidth = 2;
	rect(100, 100, 50, 50);
	//rect(200, -50, 50, 34.5);
	isStroke = true;
	isFill = false;
	lineWidth = 3;
	rect(0, 0, 100, 100, CENTER);
	//ellipse(-100, -200, 100, 100);
	lineWidth = 1;
	//ellipse(-75, -300, 10, 10);
	isFill = true;
	fillColor = blue;
	ellipse(0, 0, 10, 10);
	fillColor = Col4(0, 1, 1, 1);
	//ellipse(200, 0, 10, 10);
	//ellipse(0, -385, 10, 10);

	fill(green);

	ellipse(x, y, 20, 20);
	
	if (x <= -( getWidth() / 2)) {
		xSpeed = 1;
	}
	else if (x >= ( getWidth() / 2)) {
		xSpeed = -1;
	}
	x += xSpeed;

	lineWidth = 1;
	isStroke = true;
	strokeColor = black;
	isFill = true;
	fillColor = red;

	rect(topCornerX, topCornerY, 25, 25);

	fillColor = black;
	rect(topCornerX, topCornerY, 1, getHeight());
	rect(topCornerX, topCornerY, getWidth(), 1);

}

void myApp20::mousePressed() {
	std::cout << "mouseX = " << mouseX << std::endl;
	std::cout << "mouseY = " << mouseY << std::endl;
	std::cout << "frameCount = " << getFrameCount() << std::endl;
	//glm::vec3 testVec = glm::project(glm::vec3(x, y, 1), M, P, glm::vec4(0, 0, getWidth(), getHeight()));
	//trace("testVec =", testVec.x);

}