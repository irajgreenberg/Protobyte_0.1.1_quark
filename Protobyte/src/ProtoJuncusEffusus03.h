/*!  \brief  ProtoJuncusEffusus03.h:
Form study 3 for Zhulong Sattellite Exhibition: 4/2014
Protobyte Library v02

Created by Ira on 3/26/14.
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

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#ifndef PROTOJUNCUS_EFFUSUS_03_H
#define PROTOJUNCUS_EFFUSUS_03_H

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"


using namespace ijg;

class ProtoJuncusEffusus03 : public ProtoBaseApp {
public:
	void init();
	void run();

	GroundPlane ground;

	ProtoLight globalAmbient;
	ProtoShader shader;

	void render(int scaleFactor = 1);
	void initUniforms();

	ProtoJuncusEffusus junc01;
	int juncsCount;
	std::vector<ProtoJuncusEffusus> juncs;

	int ROWS = 5;
	int COLUMNS = 4;
	Vec3 locs[5*4];
	float thetas[5 * 4];
	int juncIDCounts[5 * 4];

private:
	
};

#endif // PROTOJUNCUS_EFFUSUS_03_H