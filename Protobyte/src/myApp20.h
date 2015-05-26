
#ifndef __MYAPP20_H__
#define __MYAPP20_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

using namespace ijg;

class myApp20 : public ProtoBaseApp {

	public:
		//Variables
		Col4f red = Col4f(1.0, 0, 0, 1.0);
		Col4 blue = Col4(0, 0, 1.0, 1.0);
		Col4 green = Col4(0.0, 1.0, 0.0, 1);
		Col4f black = Col4f(0, 0, 0, 1);

		int topCornerX;
		int topCornerY;

		int x;
		int y;
		
		int xSpeed = 1;

		//Functions
		void init();
		void run();
		void display();
		void mousePressed();

		void twoDims();

	private:

};

#endif //__MYAPP20_H__
