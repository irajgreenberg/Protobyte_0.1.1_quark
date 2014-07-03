#include "ProtoPlasm.h"
#include "libProtobyte/ProtoOSC.h"
#include "sample_prog01.h"
#include "ProtoJuncusEffusus04.h"
#include "ProtoJuncusEffusus05.h"
#include "ProtoRootBall01.h"
#include "ProtoRootBall02.h"
#include "shadowTest.h"
#include "rootBallStudy01.h"
#include <thread>

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
	
	
	ijg::ProtoPlasm p(1300, 800, "rootBall study 01", new rootBallStudy01());
	//ijg::ProtoPlasm p(1200, 900, "shadow test", new shadowTest());
	return EXIT_SUCCESS;
}