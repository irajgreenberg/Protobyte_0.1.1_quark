
#include "myApp20.h"

void myApp20::init() {
	setBackground(0.7);
	std::cout << "width = " << width << std::endl;
	std::cout << "height = " << height << std::endl;

	std::cout << "width2 = " << getWidth() << std::endl;
	std::cout << "height2 = " << getHeight() << std::endl;

	std::cout << "canvas size = " << getSize() << std::endl;

	std::cout << appTitle << "c" << std::endl;

	std::cout << "canvasWidth = " << canvasWidth << std::endl;
	std::cout << "canvasHeight = " << canvasHeight << std::endl;

	std::cout << "windowFrameSize = " << windowFrameSize << std::endl;

	x = -width / 2;
	y = 0;
}

void myApp20::run() {
}

void myApp20::display() {
	strokeColor = Col4(1);
	fillColor = red;
	isStroke = true;
	lineWidth = 2;
	rect(100, 100, 50, 50);
	rect(200, -50, 50, 34.5);
	isStroke = true;
	isFill = false;
	lineWidth = 3;
	rect(0, 0, 100, 100, CENTER);
	ellipse(-100, -200, 100, 100);
	lineWidth = 1;
	ellipse(-75, -300, 10, 10);
	isFill = true;
	fillColor = blue;
	ellipse(0, 0, 10, 10);
	fillColor = Col4(0, 1, 1, 1);
	ellipse(200, 0, 10, 10);
	ellipse(0, -385, 10, 10);

	fill(green);

	ellipse(x, y, 20, 20);
	
	if (x <= -(width / 2)) {
		xSpeed = 1;
	}
	else if (x >= (width / 2)) {
		xSpeed = -1;
	}
	x += xSpeed;
}

void myApp20::mousePressed() {
	std::cout << "mouseX = " << mouseX << std::endl;
	std::cout << "mouseY = " << mouseY << std::endl;
	std::cout << std::endl;
}