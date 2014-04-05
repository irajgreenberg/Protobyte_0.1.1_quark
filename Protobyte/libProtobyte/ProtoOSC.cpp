/*!  \brief  ProtoOSC.cpp:
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

#include "ProtoOSC.h"

using namespace ijg;

ProtoOSC::ProtoOSC(){
}

void ProtoOSC::ProcessMessage(const osc::ReceivedMessage& m,
	const IpEndpointName& remoteEndpoint)
{
	
	//std::cout << ("In ProcessMessage()") << std::endl;
	try{
		// example of parsing single messages. osc::OscPacketListener
		// handles the bundle traversal.
		if (strcmp(m.AddressPattern(), "/squeakData") == 0){
			// example #1 -- argument stream interface
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 a1;
			osc::int32 a2;
			float a3;
			float a4;
			args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;
			
			data.elem0 = a1;
			data.elem1 = a2;
			data.elem2 = a3;
			data.elem3 = a4;

			//trace(a1, ",", a2, ",", a3, ",", a4);
			//trace(data.elem0, ",", data.elem1, ",", data.elem2, ",", data.elem3);

			/*std::cout << "received '/squeakdata' message with arguments: "
				<< a1 << " " << a2 << " " << a3 << " " << a4 << "\n";*/

		}
		else if (strcmp(m.AddressPattern(), "/jumpData") == 0){
			// example #1 -- argument stream interface
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 a1;
			osc::int32 a2;
			float a3;
			float a4;
			args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;


			data.elem0 = a1;
			data.elem1 = a2;
			data.elem2 = a3;
			data.elem3 = a4;
			//trace(data.elem0, ",", data.elem1, ",", data.elem2, ",", data.elem3);

		/*	std::cout << "received '/jumpData' message with arguments: "
				<< a1 << " " << a2 << "\n";*/
		}
	}
	catch (osc::Exception& e){
		// any parsing errors such as unexpected argument types, or
		// missing arguments get thrown as exceptions.
		/*std::cout << "error while parsing message: "
			<< m.AddressPattern() << ": " << e.what() << "\n";*/
	}
}


ProtoTuple4<int, int, float, float> ProtoOSC::getData() const{
	trace(data.elem0, ",", data.elem1, ",", data.elem2, ",", data.elem3);

	return data;
}

void ProtoOSC::printData(){
	trace(data.elem0, ",", data.elem1, ",", data.elem2, ",", data.elem3);
}