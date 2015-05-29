#include "ProtoPlasm.h"
#include "BlockNet.h"
#include "myApp02.h"

int main(int argc, char const** argv) {
		ijg::ProtoPlasm p(600, 700, "BlockNet 01", new BlockNet());
		return EXIT_SUCCESS;
	}