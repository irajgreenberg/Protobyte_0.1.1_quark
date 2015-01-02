/*!  \brief  ProtoPath2.h: Class for drawing methods, moveTo, lineTo, curveTo...
ProtoPath2.h
Protobyte Library v02

Created by Ira on 1/2/15.
Copyright (c) 2015 Ira Greenberg. All rights reserved.

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

#ifndef PROTO_PATH2_H
#define PROTO_PATH2_H

#if defined(_WIN32) || defined(__linux__)
#include <GL/glew.h>
#endif

#include "ProtoColor4.h"
#include "ProtoVector2.h"


namespace ijg {

	class ProtoPath2 {
	private:

		GLuint vaoPathID, vboPathID, indexVboPathID;
		std::vector<Vec2f> path; 
		std::vector<float> pathPrims;
		std::vector<int> pathInds;
		Col4f fillCol, strokeCol;

		void init();
	
	public:
		ProtoPath2();
		~ProtoPath2();

		void moveTo(float x, float y); 
		void moveTo(const Vec2f& v);
		void lineTo(float x, float y); 
		void lineTo(const Vec2f& v);
		void curveTo(float x, float y); 
		void curveTo(const Vec2f& v);

		void fill(const Col4f& col);
		void fill(float r, float g, float b, float a);
		void stroke(const Col4f& col);
		void stroke(float r, float g, float b, float a);
	};
}

#endif //PROTO_PATH2_H
