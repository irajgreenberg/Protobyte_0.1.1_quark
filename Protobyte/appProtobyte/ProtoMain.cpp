#include "ProtoPlasm.h"
#include "ProtoJuncusEffusus01.h"
#include "Zhulong02.h"

int main(int argc, char const** argv)
{
	ijg::ProtoPlasm p(1500, 820, "ProtoJuncusEffusus 01", new ProtoJuncusEffusus01());
   return EXIT_SUCCESS;
    
   // ijg::ProtoPlasm p(150, 150, "ProtoJuncusEffusus 01", new ProtoJuncusEffusus01());
   // return EXIT_SUCCESS;
}
