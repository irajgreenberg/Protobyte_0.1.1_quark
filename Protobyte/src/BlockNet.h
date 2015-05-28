
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
};

#endif //__BLOCKNET_H__
