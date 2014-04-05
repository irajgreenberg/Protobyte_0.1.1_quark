/*!  \brief  ProtoOSC.h:
Simple OSC Send/receive implementation
utilizing oscpack_1_1_0
Protobyte Library v02

Created by Ira on 3/23/14.
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

#ifndef PROTO_OSC_H
#define	PROTO_OSC_H

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "ProtoTuple4.h"

#if defined(__BORLANDC__) // workaround for BCB4 release build intrinsics bug
namespace std {
	using ::__strcmp__;  // avoid error: E2316 '__strcmp__' is not a member of 'std'.
}
#endif


#include "OscReceivedElements.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"

#define PORT 7000

namespace ijg{
	class ProtoOSC : public osc::OscPacketListener {
		/*
		Example of two different ways to process received OSC messages using oscpack.
		Receives the messages from the SimpleSend.cpp example.
		*/
	protected:
		virtual void ProcessMessage(const osc::ReceivedMessage& m,
			const IpEndpointName& remoteEndpoint);

	private:
		

	public:
		ProtoOSC();
		ProtoTuple4<int, int, float, float> data;
		ProtoTuple4<int, int, float, float>  getData() const;
		void printData();
	
	};

}

#endif // PROTO_OSC_H