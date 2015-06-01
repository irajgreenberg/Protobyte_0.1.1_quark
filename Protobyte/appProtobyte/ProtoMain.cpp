#include "ProtoPlasm.h"
#include "BlockNet.h"
#include "myApp02.h"

int main(int argc, char const** argv) {
		new ijg::ProtoPlasm (1600, 900, "BlockNet 01", new BlockNet());
		return EXIT_SUCCESS;
	}