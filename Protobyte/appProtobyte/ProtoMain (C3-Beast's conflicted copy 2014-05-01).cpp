#include "ProtoPlasm.h"
#include "libProtobyte/ProtoOSC.h"
#include "ProtoJuncusEffusus02.h"
#include "ProtoJuncusEffusus03.h"
#include "ProtoJuncusEffusus04.h"
#include "ProtoJuncusEffusus05.h"
#include <thread>

namespace {
	std::thread t1;
	//ijg::ProtoOSC listener;
	ProtoJuncusEffusus02 listener;
	//ProtoJuncusEffusus02;
}

void runOSC(){
	/*std::chrono::milliseconds dura(200);
	std::this_thread::sleep_for(dura); */
	UdpListeningReceiveSocket s(
		IpEndpointName(IpEndpointName::ANY_ADDRESS, 12002),
		&listener);
	s.RunUntilSigInt();

}

int main(int argc, char const** argv)
{
	
	t1 = std::thread(runOSC);


	
	
	ijg::ProtoPlasm p(1920, 1080, "ProtoJuncusEffusus02", new ProtoJuncusEffusus02());
	return EXIT_SUCCESS;
}