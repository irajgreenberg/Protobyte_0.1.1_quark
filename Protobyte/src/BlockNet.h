
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
	const static int BLOCK_COUNT = 100;
	ProtoBlock blocks[BLOCK_COUNT];
	Vec3 pos[BLOCK_COUNT];
	Vec3 rot[BLOCK_COUNT];
	Vec3 scl[BLOCK_COUNT];
	ProtoTube tube;
};

#endif //__BLOCKNET_H__
