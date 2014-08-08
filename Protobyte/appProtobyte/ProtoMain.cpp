#include "ProtoPlasm.h"
#include "libProtobyte/ProtoOSC.h"
#include "sample_prog01.h"
#include "ProtoJuncusEffusus04.h"
#include "ProtoJuncusEffusus05.h"
#include "ProtoRootBall01.h"
#include "ProtoRootBall02.h"
#include "shadowTest.h"
#include <thread>
#include "rootBallStudy01.h"
#include "myApp01.h"
#include "myApp02.h"

namespace {
	//ijg::ProtoOSC listener;
	//ProtoJuncusEffusus02 listener;
	//ProtoJuncusEffusus02;
}

//void runOSC(){
//	UdpListeningReceiveSocket s(
//		IpEndpointName(IpEndpointName::ANY_ADDRESS, 12002),
//		&listener);
//	s.RunUntilSigInt();
//
//}

int main(int argc, char const** argv)
{
	
	//std::thread t1(runOSC);
	
	
	ijg::ProtoPlasm p(1300, 800, "My App 02", new myApp02());
	//ijg::ProtoPlasm p(1200, 900, "shadow test", new shadowTest());
	return EXIT_SUCCESS;
}