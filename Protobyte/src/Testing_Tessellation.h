/*!  \brief  ProtoTessellator.h: Basedon GLUTessellator
ProtoTessellator.h
Protobyte Library v02

Created by Ira on 12/14/14.
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

Based on tutorials:
http://www.songho.ca/opengl/gl_tessellation.html
// calss design
http://www.flipcode.com/archives/Polygon_Tessellation_In_OpenGL.shtml

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/




#ifndef _TESTING_TESSELLATION_H_
#define _TESTING_TESSELLATION_H_


#include <vector>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
#include <GL/glew.h>
#endif

// from OF documentation
// OSX link with " " instead of < > to avoid putting in defualt include path
#if defined(_WIN32) || defined(_WIN64)
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#else
#include "GLFW/glfw3.h"
#endif

#ifndef CALLBACK
#define CALLBACK
#endif

//GLUtesselator* iraTesselator2;

int iraInit();
void iraSetWindingRule(GLenum windingRule);
void iraBeginPolygon();
void iraBeginContour();
void iraCountourVertex(std::vector<GLdouble> data);
void iraAddContourVertex(GLdouble obj_data[][6], int num_vertices);
void iraEndContour();
void iraEndPolygon();
void iraEnd();
void CALLBACK iraTestMeBegin(GLenum triangleMode);
void CALLBACK iraVertexCallback(GLvoid *vertex);
void CALLBACK iraTestMeEnd();
void CALLBACK iraTesellationError(GLenum errorCode);
void CALLBACK iraCombineCallback(GLdouble coords[3],
	GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut);




#endif // _TESTING_TESSELLATION_H_


