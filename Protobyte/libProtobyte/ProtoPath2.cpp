/*!  \brief  ProtoPath2.cpp: Class for drawing methods, moveTo, lineTo, curveTo...
ProtoPath2.cpp
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

#include "ProtoPath2.h"

using namespace ijg;


ProtoPath2::ProtoPath2() {
}


ProtoPath2::~ProtoPath2() {
}


void ProtoPath2::init() {
	// 1. Create and bind VAO
	//GLuint vaoID;
	glGenVertexArrays(1, &vaoPathID); // Create VAO
	glBindVertexArray(vaoPathID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	//GLuint vboID;
	glGenBuffers(1, &vboPathID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboPathID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof (GLfloat)* pathPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STATIC_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &pathPrims[0]); // upload the data

	// indices data
	//GLuint indexVboID;
	glGenBuffers(1, &indexVboPathID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboPathID); // Bind element buffer

	int indsDataSize = pathDetail * 3 * sizeof(GL_UNSIGNED_INT);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &pathInds[0]); // upload data

	// fill state is true - need to create this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// draw ellipse
	glBindBuffer(GL_ARRAY_BUFFER, vboPathID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboPathID);

	glEnableVertexAttribArray(0); // vertices
	glEnableVertexAttribArray(2); // color
	// stride is 7: pos(3) + col(4)
	// (x, y, z, r, g, b, a)
	int stride = 7;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof (GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride * sizeof (GLfloat), BUFFER_OFFSET(12)); // col

	//glDisable(GL_LIGHTING);
	//glDrawElements(GL_TRIANGLES, ellipseDetail * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Disable buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	pathPrims.clear();
	pathInds.clear();

}