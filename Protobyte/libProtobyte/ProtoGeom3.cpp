/*!  \brief  ProtoGeom3.cpp: Abstact Base Geometry class
 ProtoGeom3.cpp
 Protobyte Library v02
 
 Created by Ira on 7/23/13.
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


#include "ProtoGeom3.h"


using namespace ijg;

GLuint ProtoGeom3::textureID = 0;

ProtoGeom3::ProtoGeom3() {
}



ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4) :
ProtoShape3(pos, rot, size, col4), textureImageURL("") {
}

ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const std::vector< ProtoColor4f > col4s) :
ProtoShape3(pos, rot, size, col4s), textureImageURL("") {
}


// with textures
ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4, const std::string& textureImageURL) :
ProtoShape3(pos, rot, size, col4), textureImageURL(textureImageURL) {
}

ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const std::vector< ProtoColor4f > col4s, const std::string& textureImageURL) :
ProtoShape3(pos, rot, size, col4s), textureImageURL(textureImageURL) {
}

ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4, const std::string& textureImageURL, float textureScale) :
ProtoShape3(pos, rot, size, col4), textureImageURL(textureImageURL), textureScale(textureScale) {
}

ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
					   const std::vector< ProtoColor4f > col4s, const std::string& textureImageURL, float textureScale) :
ProtoShape3(pos, rot, size, col4s), textureImageURL(textureImageURL), textureScale(textureScale) {
}

ProtoGeom3::~ProtoGeom3() {
	// glDeleteLists(displayListIndex, 1);
	// trace("in Geom3 dstr");
    
    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise();
#endif
}


void ProtoGeom3::init() {
	createTexture();
    calcVerts();
	calcInds();
	calcFaces();
	calcVertexNorms();
	calcPrimitives();
	//fillDisplayLists(); // just in case we want to render with display Lists: Data can't be changed though
    
    // set object material default settings
    // mid shiny, white specular highlights, no emission
    setShininess();
    setSpecularMaterialColor();
    setEmissionMaterialColor();
    
    // initialize glew for Windows
#if defined(_WIN32) || defined(__linux__)
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	//fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
	
	
	//glGenVertexArrays(1, &planeVAOID);
	//glGenBuffers(1, &planeVerticesVBO);
	//glGenBuffers(1, &planeIndicesVBO);
	//glBindVertexArray(planeVAOID);

	//glBindBuffer(GL_ARRAY_BUFFER, planeVerticesVBO);
	////pass vertices to the buffer object
	//glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	//GL_CHECK_ERRORS
	//	//enable vertex attribute array for position
	//	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//GL_CHECK_ERRORS
	//	//enable vertex attribute array for normals
	//	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, normal)));
	//GL_CHECK_ERRORS
	//	//pass plane indices to element array buffer
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeIndicesVBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLushort), &indices[0], GL_STATIC_DRAW); 
	

	glGenBuffers(1, &vboID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof (float) * static_cast<int>(interleavedPrims.size());
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW); // allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
	//glEnableVertexAttribArray(0);
	//glBufferData(GL_ARRAY_BUFFER, vertsDataSize, &interleavedPrims[0], GL_STATIC_DRAW); // allocate and upload
	//sharedMemPointer = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	//std::cout << "sharedMemPointer = " << sharedMemPointer << std::endl;
    
	//indices data - use GL_ELEMENT_ARRAY_BUFFER
	glGenBuffers(1, &indexVboID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID); // Bind the element array buffer
	int indsDataSize = static_cast<int>(inds.size()) * 3 * sizeof (GL_UNSIGNED_INT);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &indPrims[0]); // upload the data
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, &indPrims[0], GL_STATIC_DRAW); // allocate and upload
    
	//    if (glMapBuffer && glUnmapBuffer) {
	//        //std::cout << "glMapBuffer is supported" << std::endl;
	//    }
    
    // set default texture enabled state
    isTextureEnabled = false;
}

void ProtoGeom3::calcFaces() {
    if(faces.size()>0){
        faces.clear();
    }
	// pass vertex addresses
	for (int i = 0; i < inds.size(); i++) {
		faces.push_back(ProtoFace3(&verts.at(inds.at(i).elem0), &verts.at(inds.at(i).elem1),
                                   &verts.at(inds.at(i).elem2)));
		//std::cout << faces.at(i)[2]->pos.z << std::endl;
	}
}




void ProtoGeom3::calcVertexNorms() {
    
    // calculate initial vertex normals and fill geomsets with vertex face association
    // to enable easier runtime vertex normal calcs
    if(geomSets.size()>0){
        geomSets.clear();
    }
    
    for (int i = 0; i < verts.size(); i++) {
		Vec3f v;
        std::vector<ProtoFace3*> fs;
		for (int j = 0; j < faces.size(); j++) {
			if (&verts.at(i) == faces.at(j)[0] || &verts.at(i) == faces.at(j)[1] ||
				&verts.at(i) == faces.at(j)[2]) {
                //std::cout << "i = " << i << ", " << "face " << j << std::endl;
                v += faces.at(j).getNorm();
                fs.push_back(&faces.at(j));
			}
		}
        geomSets.push_back(ProtoGeomSet(&verts.at(i), fs));
        //std::cout << "vertex has this many linked faces: " << geomSets.at(i).getLinkedFaces().size() << std::endl;
		v.normalize();
		verts.at(i).setNormal(v);
	}
}



void ProtoGeom3::sortFaces() {
	bool swapped = true;
	int j = 0;
	//ProtoFace3 tmp;
	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < faces.size() - j; i++) {
			if (faces.at(i).getCentroid().z > faces.at(i + 1).getCentroid().z) {
				ProtoFace3 tmp = faces.at(i);
				faces.at(i) = faces.at(i + 1);
				faces.at(i + 1) = tmp;
				swapped = true;
			}
		}
	}
}

void ProtoGeom3::calcPrimitives() {
    if (vertPrims.size()>0) vertPrims.clear();
    if (normPrims.size()>0) normPrims.clear();
    if (colorPrims.size()>0) colorPrims.clear();
    if (texturePrims.size()>0) texturePrims.clear();
    if (interleavedPrims.size()>0) interleavedPrims.clear();
    if (indPrims.size()>0) indPrims.clear();
    
	for (int i = 0; i < verts.size(); i++) {
        
		// fill individual primitive arrays - eventually remove
		vertPrims.push_back(verts.at(i).pos.x);
		vertPrims.push_back(verts.at(i).pos.y);
		vertPrims.push_back(verts.at(i).pos.z);
        
		normPrims.push_back(verts.at(i).getNormal().x);
		normPrims.push_back(verts.at(i).getNormal().y);
		normPrims.push_back(verts.at(i).getNormal().z);
        
		colorPrims.push_back(verts.at(i).getColor().getR());
		colorPrims.push_back(verts.at(i).getColor().getG());
		colorPrims.push_back(verts.at(i).getColor().getB());
		colorPrims.push_back(verts.at(i).getColor().getA());
        
		texturePrims.push_back(verts.at(i).getUV().elem0);
		texturePrims.push_back(verts.at(i).getUV().elem1);
        
		// fill interleaved primitive arrays
		interleavedPrims.push_back(verts.at(i).pos.x);
		interleavedPrims.push_back(verts.at(i).pos.y);
		interleavedPrims.push_back(verts.at(i).pos.z);
        
		interleavedPrims.push_back(verts.at(i).getNormal().x);
		interleavedPrims.push_back(verts.at(i).getNormal().y);
		interleavedPrims.push_back(verts.at(i).getNormal().z);
        
		interleavedPrims.push_back(verts.at(i).getColor().getR());
		interleavedPrims.push_back(verts.at(i).getColor().getG());
		interleavedPrims.push_back(verts.at(i).getColor().getB());
		interleavedPrims.push_back(verts.at(i).getColor().getA());
        
		interleavedPrims.push_back(verts.at(i).getUV().elem0);
		interleavedPrims.push_back(verts.at(i).getUV().elem1);
        
        
	}
	// test
	//for(int i=0; i<interleavedPrims.size(); ++i){
	//std::cout << interleavedPrims.at(i) << std::endl;
	//}
    
	//    std::cout << "verts.size() = " << verts.size() << std::endl;
	//    std::cout << "interleavedPrims.size()/12 = " << interleavedPrims.size()/12 << std::endl;
    
    
	// explode inds arrays to primitives
	for (int i = 0, j = 0; i < inds.size(); i++) {
		indPrims.push_back(inds.at(i).elem0);
		indPrims.push_back(inds.at(i).elem1);
		indPrims.push_back(inds.at(i).elem2);
	}
}


//void ProtoGeom3::calcPrimitives() {
//	vertPrims.resize(verts.size()*3);
//	normPrims.resize(verts.size()*3);
//	colorPrims.resize(verts.size()*4);
//	texturePrims.resize(verts.size()*2);
//	interleavedPrims.resize(verts.size()*12);
//    
//	indPrims.resize(inds.size()*3);
//    
//	for (int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0; i < verts.size(); i++) {
//        
//		// fill individual primitive arrays - eventually remove
//		vertPrims.at(j++) = verts.at(i).pos.x;
//		vertPrims.at(j++) = verts.at(i).pos.y;
//		vertPrims.at(j++) = verts.at(i).pos.z;
//        
//		normPrims.at(k++) = verts.at(i).getNormal().x;
//		normPrims.at(k++) = verts.at(i).getNormal().y;
//		normPrims.at(k++) = verts.at(i).getNormal().z;
//        
//		colorPrims.at(l++) = verts.at(i).getColor().getR();
//		colorPrims.at(l++) = verts.at(i).getColor().getG();
//		colorPrims.at(l++) = verts.at(i).getColor().getB();
//		colorPrims.at(l++) = verts.at(i).getColor().getA();
//        
//		texturePrims.at(m++) = verts.at(i).getUV().elem0;
//		texturePrims.at(m++) = verts.at(i).getUV().elem1;
//        
//		// fill interleaved primitive arrays
//		interleavedPrims.at(n++) = verts.at(i).pos.x;
//		interleavedPrims.at(n++) = verts.at(i).pos.y;
//		interleavedPrims.at(n++) = verts.at(i).pos.z;
//        
//		interleavedPrims.at(n++) = verts.at(i).getNormal().x;
//		interleavedPrims.at(n++) = verts.at(i).getNormal().y;
//		interleavedPrims.at(n++) = verts.at(i).getNormal().z;
//        
//		interleavedPrims.at(n++) = verts.at(i).getColor().getR();
//		interleavedPrims.at(n++) = verts.at(i).getColor().getG();
//		interleavedPrims.at(n++) = verts.at(i).getColor().getB();
//		interleavedPrims.at(n++) = verts.at(i).getColor().getA();
//        
//		interleavedPrims.at(n++) = verts.at(i).getUV().elem0;
//		interleavedPrims.at(n++) = verts.at(i).getUV().elem1;
//        
//        
//	}
//	// test
//	//for(int i=0; i<interleavedPrims.size(); ++i){
//	//std::cout << interleavedPrims.at(i) << std::endl;
//	//}
//    
//	//    std::cout << "verts.size() = " << verts.size() << std::endl;
//	//    std::cout << "interleavedPrims.size()/12 = " << interleavedPrims.size()/12 << std::endl;
//    
//    
//	// explode inds arrays to primitives
//	for (int i = 0, j = 0; i < inds.size(); i++) {
//		indPrims.at(j++) = inds.at(i).elem0;
//		indPrims.at(j++) = inds.at(i).elem1;
//		indPrims.at(j++) = inds.at(i).elem2;
//	}
//}

void ProtoGeom3::createTexture(){
    // only buld texture if an image url was passed in
    if(textureImageURL != ""){
        
        // 1. ensure path is to resources directory
        char cCurrentPath[FILENAME_MAX];
        
#if defined (__APPLE__)
		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
        {
            std::cout << "error loading from relative directory" << std::endl;
            //return errno;
        }
#elif defined(_WIN32) || (_WIN64)
		//char full[_MAX_PATH];
		if (_fullpath(cCurrentPath, "", FILENAME_MAX) != NULL) {
			printf("");
		}
		else {
			printf("Invalid path\n");
		}

#endif

        // NOTE - make workspace project relative instead of using default derivedData path in Library
        //std::cout << "cCurrentPath = " << cCurrentPath << std::endl;
        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
        std::string cp = cCurrentPath; //cast char[] to string
#if defined(_WIN32) || (_WIN64)
		// need to escape backslashes with themselves, ick
        std::string pathExtension = "\\resources\\imgs\\";
#else
		// osx/posix use "normal" directory dividers
		std::string pathExtension = "/resources/imgs/";
        
#endif

        std::string url = cp + pathExtension + textureImageURL;
        // trace("url =", url);
		// trace("image URL = ", url);
        // 2. create texture
        // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
        FreeImage_Initialise();
#endif
        texture = ProtoTexture(url, GL_RGB, GL_RGB, 0, 0, textureID++);
        
        //std::cout << "texture.getTextureID() = " << texture.getTextureID() << std::endl;
        
    }
}

void ProtoGeom3::textureOn(){
    //glEnable(GL_TEXTURE_2D);
    isTextureEnabled = true;
}

void ProtoGeom3::textureOff(){
     isTextureEnabled = false;
   
}

void ProtoGeom3::fillDisplayLists() {
	glNewList(displayListIndex, GL_COMPILE);
	for (int i = 0; i < faces.size(); ++i) {
		faces.at(i).display();
	}
	glEndList();
}
// Includes multiple display implementations

/* NOTE:: Drawing will/MAY eventually get delegated to a
 world type class, to enable aggregate face sorting and
 and primitive processing*/
void ProtoGeom3::display(RenderMode render, float pointSize) {

    if(isTextureEnabled) {
         glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texture.textureID);
    } else {
        glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    //glBindTexture(GL_TEXTURE_2D,texture.textureID); // added to conditional above
    
    // set materials not controlled by glColor
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularMaterialColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissionMaterialColor);
    
	switch (render) {
        case POINTS:
            //glDisable(GL_CULL_FACE);
            //glDisable(GL_LIGHTING);
            glPointSize(pointSize);
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
            
        case WIREFRAME:
            //glDisable(GL_CULL_FACE);
            //glDisable(GL_LIGHTING);
            glLineWidth(pointSize);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
            
        case SURFACE:
            //glDisable(GL_CULL_FACE);
            //glEnable(GL_LIGHTING);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            //glPolygonMode(GL_FRONT, GL_FILL);
            break;
	}
	//  hackity-hack - fix eventually
	//  static float rx = .02;
	//  static float ry = .03;
	//  static float rz = .04;
	//  glPushMatrix();
	//  glLoadIdentity();
    
    //	glTranslatef(pos.x, pos.y, pos.z);
    //	glRotatef(rot.x, 1, 0, 0); // x-axis
    //	glRotatef(rot.y, 0, 1, 0); // y-axis
    //	glRotatef(rot.z, 0, 0, 1); // z-axis
	//  glScalef(size.w, size.h, size.d);
    
    
    
    
	//rot.x += rx;
	//rot.y += ry;
	//rot.z += rz;
    
	//sortFaces();
	/* NOTE:: sorting here is not solving self-overlap highlighting with alpha
     possible solution will be doing manual rotations on geometry
     (as coampdre to modelview matrix transformation) and then sorting faces.
     * See note aovbe above delegating this to a world type class.*/
    
    
    
    // make sure data is bound to buffer
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID);
    
    // enable and specify pointers to vertex arrays
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_NORMAL_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// switched to vertexAttrib approach 
	// help from http://stackoverflow.com/questions/8704801/glvertexattribpointer-clarification
	for (int i = 0; i < 4; i++) {
		glEnableVertexAttribArray(i);
	}


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof (GLfloat), BUFFER_OFFSET(0)); // xyz
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof (GLfloat), BUFFER_OFFSET(12)); // norms
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 12 * sizeof (GLfloat), BUFFER_OFFSET(24)); // cols
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof (GLfloat), BUFFER_OFFSET(40)); // uvs
    
    // stride is 12 : (x, y, z, nx, ny, nz, r, g, b, a, u, v)
    // vertices, normals, color
    //glVertexPointer(3, GL_FLOAT, 12 * sizeof (GLfloat), BUFFER_OFFSET(0));
    //glNormalPointer(GL_FLOAT, 12 * sizeof (GLfloat), BUFFER_OFFSET(12)); // step over 3 bytes
    //glColorPointer(4, GL_FLOAT, 12 * sizeof (GLfloat), BUFFER_OFFSET(24)); // step over 6 bytes
    //glTexCoordPointer(2, GL_FLOAT, 12 * sizeof (GLfloat), BUFFER_OFFSET(40)); // step over 10 bytes
    
    if (render == POINTS) {
        glDrawElements(GL_POINTS, static_cast<int>(inds.size())*3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    } else {
        glDrawElements(GL_TRIANGLES, static_cast<int>(inds.size())*3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    }
    
    //glDisableClientState(GL_NORMAL_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
    //glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
	//glDisableVertexAttribArray(3);
	for (int i = 0; i < 4; i++) {
		glDisableVertexAttribArray(i);
	}
    
    // free pointers to data
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
	//glPopMatrix();
    
	// reset fill and lighting
    //	glEnable(GL_LIGHTING);
    //	glPolygonMode(GL_FRONT, GL_FILL);
}

void ProtoGeom3::move(const Vec3f& v) {
	pos += v;
}

void ProtoGeom3::rotate(const Vec3f& r) {
	rot += r;
}

void ProtoGeom3::scale(const ProtoDimension3f& s) {
	size += s;
}

// transform VBO primitives using glBufferSubData
void ProtoGeom3::transform(const ProtoMatrix4f& mat4){
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    for (int i = 0; i < interleavedPrims.size(); i += 12) {// transform verts
        Vec4 v4(interleavedPrims.at(i), interleavedPrims.at(i+1), interleavedPrims.at(i+2), 1);
        Vec3 v3  = mat4*v4;
        interleavedPrims.at(i) = v3.x;
        interleavedPrims.at(i+1) = v3.y;
        interleavedPrims.at(i+2) = v3.z;
        
        // transform vnorms
        // there's a better way to transform v norms (so fix it eventually!)
        ProtoMatrix4f m = mat4;
        m.transpose();
        Vec4 v4n(interleavedPrims.at(i+3), interleavedPrims.at(i+4), interleavedPrims.at(i+5), 1);
        Vec3 v3n = m*v4n;
        interleavedPrims.at(i+3) = v3n.x;
        interleavedPrims.at(i+4) = v3n.y;
        interleavedPrims.at(i+5) = v3n.z;
        
    }
    int vertsDataSize = sizeof (float) *interleavedPrims.size();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void ProtoGeom3::updateColorBuffer(){
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	//trace("col4s.size() =", col4s.size());
	//trace("interleavedPrims.size()/12 =", interleavedPrims.size() / 12);
	for (int i = 0, colCounter=0; i < interleavedPrims.size(); i += 12) {// transform verts
		// NOTE:: this needs work!!!
		if (col4s.size()>0){
			interleavedPrims.at(i + 6) = col4s.at(colCounter).getR();
			interleavedPrims.at(i + 7) = col4s.at(colCounter).getG();
			interleavedPrims.at(i + 8) = col4s.at(colCounter).getB();
			interleavedPrims.at(i + 9) = col4s.at(colCounter).getA();
		}
		else {
			interleavedPrims.at(i + 6) = col4.getR();
			interleavedPrims.at(i + 7) = col4.getG();
			interleavedPrims.at(i + 8) = col4.getB();
			interleavedPrims.at(i + 9) = col4.getA();
		}

	}
	int vertsDataSize = sizeof (float)*interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ProtoGeom3::updateTextureBuffer(){
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	for (int i = 0; i < interleavedPrims.size(); i += 12) {// transform verts
		interleavedPrims.at(i + 10) *= 1.0/textureScale;
		interleavedPrims.at(i + 11) *= 1.0/textureScale;
        
	}
	int vertsDataSize = sizeof (float)*interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ProtoGeom3::updateBuffer(){
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	for (int i = 0; i < interleavedPrims.size(); i += 12) {// transform verts
		interleavedPrims.at(i + 10) *= 1.0/textureScale;
		interleavedPrims.at(i + 11) *= 1.0/textureScale;
		//interleavedPrims.at(i + 12) *= 1.0/textureScale;

	}
	int vertsDataSize = sizeof (float)*interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// this needs to be TOTALLY reworked (binary implementation as well!!!)

//void ProtoGeom3::exportSTL() {
//    if (mkdir("../exportData", 0777) == -1)//creating a directory
//    {
//        //std::cout << "STL file Successfully Written" << std::endl;
//        //std::cerr<<"Error :  "<< strerror (errno)<< std::endl;
//        //exit(1);
//    }
//    std::ofstream myfile;
//    myfile.open("../exportData/geomData.STL");
//
//    myfile << "solid PROTOBYTE\n";
//    for (int i = 0; i < faces.size(); i++) {
//        myfile << std::scientific << std::setprecision(7) << "\tfacet normal " <<
//                faces[i].getNorm().x << " " << faces[i].getNorm().y << " " << faces[i].getNorm().z << "\n" <<
//                "\t\touter loop\n" <<
//                "\t\t\tvertex " << faces[i].v0_p->pos.x << " " << faces[i].v0_p->pos.y << " " << faces[i].v0_p->pos.z << "\n" <<
//                "\t\t\tvertex " << faces[i].v1_p->pos.x << " " << faces[i].v1_p->pos.y << " " << faces[i].v1_p->pos.z << "\n" <<
//                "\t\t\tvertex " << faces[i].v2_p->pos.x << " " << faces[i].v2_p->pos.y << " " << faces[i].v2_p->pos.z << "\n" <<
//                "\t\tendloop\n" <<
//                "\tendfacet\n";
//    }
//    myfile << "endsolid PROTOBYTE\n";
//
//    myfile.close();
//    std::cout << "STL file Successfully Written" << std::endl;
//}



