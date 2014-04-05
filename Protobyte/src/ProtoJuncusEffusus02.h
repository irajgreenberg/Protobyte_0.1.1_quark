/*!  \brief  ProtoJuncusEffusus02.h: Single wrapped starnd study
 ProtoJuncusEffusus01.h
 Protobyte Library v02
 
 Created by Ira on 3/3/14.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.
 
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

#ifndef Protobyte_dev_OSX_2_ProtoJuncusEffusus02_cpp
#define Protobyte_dev_OSX_2_ProtoJuncusEffusus02_cpp

#include <iostream>
//#include <thread> 
//#include <dirent.h> // no native implementation in WIN
#include "appProtobyte/ProtoBaseApp.h"
//#include  "libProtobyte/ProtoOSC.h"

#include <cstring>
#include <stdlib.h>




using namespace ijg;
    
class ProtoJuncusEffusus02 : public ProtoBaseApp, public osc::OscPacketListener  {
    
    public:
        
		ProtoJuncusEffusus02();
		ProtoJuncusEffusus02(const ProtoOSC& listener);
		
		void init();
        void run();

		
		ProtoTuple4<int, int, float, float> data;

		int tubuleCount;
		std::vector<ProtoJuncusEffusus> juncs;

		GroundPlane ground;
        
		ProtoLight globalAmbient;
		ProtoShader shader;

		// for shadowmap
		GLuint depthTextureID;
		GLuint framebufferID;

		ProtoShader depthShader;

		//void saveTiles(int rows, int columns);
		//void save(std::string name = "img", int scaleFactor = 1);
		//bool stitchTiles(std::string url, int tiles);


		// override base
		void render(int scaleFactor = 1);

		bool initShadowMap();
		void setShadowMapTransform();
		void initUniforms();

		int test;

		
        
protected:
	void ProcessMessage(const osc::ReceivedMessage& m,
		const IpEndpointName& remoteEndpoint); 

private:
        
    };

#endif // Protobyte_dev_OSX_2_ProtoJuncusEffusus02_cpp
