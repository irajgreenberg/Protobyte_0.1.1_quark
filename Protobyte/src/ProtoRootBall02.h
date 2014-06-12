/*!  \brief  ProtoRootBall02.h:
Protobyte Library v02

Created by Ira on 4/30/14.
Copyright (c) 2014 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.
// thanks to: http://designdivala.deviantart.com/art/Green-Croc-texture-268499409

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#ifndef PROTOROOTBALL_02_H
#define PROTOROOTBALL_02_H

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"
#include "libProtobyte/ProtoRootBall.h"


using namespace ijg;

class ProtoRootBall02 : public ProtoBaseApp {
public:
	void init();
	void run();


	void render(int scaleFactor = 1);
	RootBall rootBallCore, rootBall;
	ProtoGroundPlane plane;
	Toroid toroid;
	static const int W = 5;
	static const int H = 4;
	Toroid toroids[W*H];

private:
	
};

#endif // PROTOROOTBALL_01_H