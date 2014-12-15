/*!  \brief  ProtoTessellator.cpp: Basedon GLUTessellator
ProtoTessellator.cpp
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

\ingroup common
This class is part of the group common (update)
\sa NO LINK


*/

#include "ProtoTessellator.h"


ProtoTessellator::ProtoTessellator() {
}


ProtoTessellator::~ProtoTessellator() {
}


int ProtoTessellator::init() {
	// Create a new tessellation object 
	tesselator = gluNewTess();
	if (!tesselator) return 0;

	// Set callback functions
	//gluTessCallback(tesselator, GLU_TESS_VERTEX, (void(*)()) &vertexCallback);
	//gluTessCallback(tesselator, GLU_TESS_BEGIN, (void()) &glBegin);
	//gluTessCallback(tesselator, GLU_TESS_END, (void()) &glEnd);
	//gluTessCallback(tesselator, GLU_TESS_COMBINE, (void()) &combineCallback);

	//gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())tessBeginCB);
	//gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())tessEndCB);
	//gluTessCallback(tess, GLU_TESS_ERROR, (void (CALLBACK *)())tessErrorCB);
	//gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())tessVertexCB);

	return 1;
}

void ProtoTessellator::setWindingRule(GLenum windingRule) {
	gluTessProperty(tesselator, GLU_TESS_WINDING_RULE, windingRule);
}

void ProtoTessellator::RenderContour(GLdouble data[][7], int vertexCount) {
	for (int i = 0; i < vertexCount; ++i) //loop through the vertices
	{
		gluTessVertex(tesselator, data[i], data[i]); //store the vertex
	}
}

void ProtoTessellator::beginPolygon() {
	gluTessBeginPolygon(tesselator, NULL);
}

void ProtoTessellator::endPolygon() {
	gluTessEndPolygon(tesselator);
}

void ProtoTessellator::beginContour() {
	gluTessBeginContour(tesselator);
}

void ProtoTessellator::endContour() {
	gluTessEndContour(tesselator);
}

void ProtoTessellator::end() {
	gluDeleteTess(tesselator);
}

void CALLBACK combineCallback(GLdouble coords[3], GLdouble *vertex_data[4],
	GLfloat weight[4], GLdouble **dataOut) {
	
	/*GLdouble *vertex;

	vertex = (GLdouble *)malloc(6 * sizeof(GLdouble));
	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];

	for (int i = 3; i < 6; i++)
	{
		vertex[i] = weight[0] * vertex_data[0][i] +
			indent indweight[1] * vertex_data[1][i] +
			indent indweight[2] * vertex_data[2][i] +
			indent indweight[3] * vertex_data[3][i];
	}

	*dataOut = vertex;*/
}

void CALLBACK vertexCallback(GLvoid *vertex) {
	GLdouble *ptr;

	//ptr = (GLdouble *)vertex;
	//glVertex3dv((GLdouble *)ptr);
	//glColor3dv((GLdouble *)ptr + 3);
}

