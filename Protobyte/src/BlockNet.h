
#ifndef __BLOCKNET_H__
#define __BLOCKNET_H__

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"

using namespace ijg;

class BlockNet : public ProtoBaseApp {

public:
void init();
void run();
void display();

private:
	ProtoBlock block;
	const static int BLOCK_COUNT = 150;
	ProtoBlock blocks[BLOCK_COUNT];
	Vec3 pos[BLOCK_COUNT];
	Vec3 rot[BLOCK_COUNT];
	Dim3f dim[BLOCK_COUNT];
	Spline3 path;
	ProtoTube tube;
};

#endif //__BLOCKNET_H__
