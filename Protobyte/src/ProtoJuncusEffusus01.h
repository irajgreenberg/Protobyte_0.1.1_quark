/*!  \brief  ProtoJuncusEffusus01.h: Single wrapped starnd study
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

#ifndef Protobyte_dev_OSX_2_ProtoJuncusEffusus01_cpp
#define Protobyte_dev_OSX_2_ProtoJuncusEffusus01_cpp

#include <iostream>
//#include <dirent.h>
#include "appProtobyte/ProtoBaseApp.h"


namespace ijg {
    
    class ProtoJuncusEffusus01 : public ProtoBaseApp {
    
    public:
        
        void init();
        void run();
      
        Tube tubule;
        Tube tubulesWrap;

		int tubuleCount;
		std::vector<Tube> tubules;
		std::vector<Tube> tubulesWraps;

		GroundPlane ground;
        
		ProtoLight globalAmbient;
		ProtoShader shader, shadowMapShader;

		// for shadowmap
		GLuint depthTexture;
		GLuint framebufferName;
		ProtoShader depthShader;

		void saveTiles(int rows, int columns);
		void save(std::string name = "img", int scaleFactor = 1);
		bool stitchTiles(std::string url, int tiles);

		int beings;
		std::vector<Vec3f> locs;

		void render();

		bool initShadowMap();
		void setShadowMapTransform();
        
    private:
        
    };
}

#endif // Protobyte_dev_OSX_2_ProtoJuncusEffusus01_cpp
