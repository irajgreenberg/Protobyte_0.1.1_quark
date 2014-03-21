/*!  \brief  ProtoGeom3.h: Abstact Base Geometry class
 ProtoGeom3.h
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

#ifndef PROTO_GEOM3_H
#define PROTO_GEOM3_H


#if defined(_WIN32) || defined(__linux__)
#include <GL/glew.h>
#endif

// for image path to texture
#if defined(__APPLE__) || defined(__linux__)
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

//#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "ProtoVector2.h"
#include "ProtoVector3.h"
#include "ProtoVector4.h"
#include "ProtoFace3.h"
#include "ProtoTuple3.h"
#include "ProtoDimension2.h"
#include "ProtoDimension3.h"
#include "ProtoColor4.h"
#include "ProtoTexture.h"
//#include "ProtoGLInfo.h"
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "ProtoShape3.h"
#include "ProtoGeomSet.h"


namespace ijg {
    
    
    // for offset into the FBO interleaved buffer (ugly I know!)
#define BUFFER_OFFSET(i) ((void*)(i))
    
    class ProtoGeom3: public ProtoShape3{
        
        friend class ProtoVertex3;
    
    protected:
        
        std::string textureImageURL;
        ProtoTexture bumpMap; //?
        ProtoTexture texture;
        float textureScale;
        
        
        virtual void init();
        virtual void calcVerts() = 0;
        virtual void calcInds() = 0;
        virtual void calcFaces(); // probably not necessary to override
        virtual void calcVertexNorms();
        virtual void calcPrimitives();
        virtual void createTexture();
        
        void fillDisplayLists();
        

        
       // std::vector<Vec2f> uvs;
        
        // composite guts
        std::vector<ProtoVertex3> verts;
        //std::vector<ProtoVertex3*> verts;
        std::vector<ProtoFace3> faces;
        std::vector< ProtoTuple3<int> > inds;

        
        //primitive guts
        std::vector<float> vertPrims;
        std::vector<unsigned int> indPrims;
        std::vector<float> normPrims;
        std::vector<float> colorPrims;
        std::vector<float> texturePrims;
        std::vector<float> interleavedPrims;
        
        // Display List var
        GLuint displayListIndex;
        
        // VBO stuff
        GLuint vboID, indexVboID;
        
        //shared memory pointer for dynamic VBO's
        float* sharedMemPointer;
        
        // Utility for extension support
        // ProtoGLInfo glInfo;
        
        std::vector<ProtoGeomSet> geomSets;
        
        // material properties
        // diffuse and ambient materials are controlled by glColor
        GLfloat shininess[1]; // 0-128
        GLfloat specularMaterialColor[4];
        GLfloat emissionMaterialColor[4];
        
        
        bool isTextureEnabled;
		void updateBuffer(); // currently used for texture scale only.
        void updateTextureBuffer(); // new one

		// update buffers for GPU - need to do for all relevant fields
		void updateColorBuffer();
        
        
    public:
//        
//        enum renderMode {
//            POINTS,
//            WIREFRAME, // begin at 0
//            SURFACE
//        };
        
        ProtoGeom3();
        
        ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
                   const ProtoColor4f col4);
        
        ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
                   const std::vector< ProtoColor4f > col4s);
        
        
        // with textureImageURL
        ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4, const std::string& textureImageURL);
        
        ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const std::vector< ProtoColor4f > col4s, const std::string& textureImageURL);
        
        ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4, const std::string& textureImageURL, float textureScale);
        
        ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
                   const std::vector< ProtoColor4f > col4s, const std::string& textureImageURL, float textureScale);
        
        
        
        virtual ~ProtoGeom3();
        
        virtual void move(const Vec3f& v);
        virtual void rotate(const Vec3f& r);
        virtual void scale(const ProtoDimension3f& s);
        
        virtual void transform(const ProtoMatrix4f& mat4);
        
        
        // vertex arrays are implemented by default
        virtual void display(RenderMode render = SURFACE, float pointSize = .5f);
        
        // setters/getters
       // overload Shape3 methods
		virtual void setPosition(const Vec3f& pos);
        virtual void setRotation(const Vec3f& rot);
        virtual void setSize(const ProtoDimension3f size);
        virtual void setColor(const ProtoColor4f col4);
        
        virtual Vec3f& getPosition();
        virtual Vec3f& getRotation();
        virtual ProtoDimension3f& getSize();
        virtual ProtoColor4f& getColor();
        
        // a bit dangerous to return references, so be careful
        // justification, you got no 3d if you delete this stuff
        
        std::vector<ProtoFace3>& getFaces();
        std::vector<ProtoVertex3>& getVertices();
        std::vector<float>& getInterleavedPrims();
        
        
        virtual void sortFaces();
        
        void setTextureScale(float textureScale);
        float getTextureScale() const;
        
        void setBumpMap(ProtoTexture bumpMap);
        ProtoTexture getBumpMap() const;
        
        // stl exporter
        //        void exportSTL();
        
        // required by ProtobteRenderer
        GLuint getVboID() const;
        GLuint getIndexVboID() const;
        int getIndicesSize() const;
        
        // material setters
        void setShininess(float shininess = 45);
        void setSpecularMaterialColor(const Col4f& specularMaterialColor = Col4f(1, 1, 1, 1));
        void setEmissionMaterialColor(const Col4f&  emissionMaterialColor= Col4f(0, 0, 0, 1));
        
        // ensure unquie id for each texture per geom obj - this needs to be rethought eventually.
        static GLuint textureID;
        ProtoTexture getTexture()const;
        void textureOn();
        void textureOff();
        
        
    };
    
    
    // setters/getters
    inline void ProtoGeom3::setPosition(const Vec3f& pos) {
        this->pos = pos;
    }
    
    inline void ProtoGeom3::setRotation(const Vec3f& rot) {
        this->rot = rot;
    }
    
    inline void ProtoGeom3::setSize(const ProtoDimension3f size) {
        this->size = size;
    }
    
    inline void ProtoGeom3::setColor(const ProtoColor4f col4) {
        this->col4 = col4;
		if (col4s.size() > 0){
			for (int i = 0; i < col4s.size(); ++i){
				col4s.at(i) = col4;
			}
		}
		// need to update primitives for GPU
		updateColorBuffer();
    }
    
    inline Vec3f& ProtoGeom3::getPosition() {
        return pos;
    }
    
    inline Vec3f& ProtoGeom3::getRotation() {
        return rot;
    }
    
    inline ProtoDimension3f& ProtoGeom3::getSize() {
        return size;
    }
    
    inline ProtoColor4f& ProtoGeom3::getColor() {
        return col4;
    }
    
    inline std::vector<ProtoFace3>& ProtoGeom3::getFaces() {
        return faces;
    }
    
    inline std::vector<ProtoVertex3>& ProtoGeom3::getVertices() {
        return verts;
    }
    
    inline  std::vector<float>& ProtoGeom3::getInterleavedPrims(){
        return interleavedPrims;
    }
    
    inline void ProtoGeom3::setTextureScale(float textureScale) {
        this->textureScale = textureScale;
		updateTextureBuffer();
    }
    
    inline float ProtoGeom3::getTextureScale() const {
        return textureScale;
    }
    
    inline void ProtoGeom3::setBumpMap(ProtoTexture bumpMap) {
        this->bumpMap = bumpMap;
    }
    
    inline ProtoTexture ProtoGeom3::getBumpMap() const {
        return bumpMap;
    }
    
    inline GLuint ProtoGeom3::getVboID() const {
        return vboID;
    }
    
    inline GLuint ProtoGeom3::getIndexVboID() const {
        return indexVboID;
    }
    
    inline int ProtoGeom3::getIndicesSize() const{
        return static_cast<int>(inds.size());
    }
    
    // materials
    inline void ProtoGeom3::setShininess(float shininess){
        this->shininess[0]=shininess;
    }
    inline void ProtoGeom3::setSpecularMaterialColor(const Col4f& specularMaterialColor){
        this->specularMaterialColor[0] = specularMaterialColor.getR();
        this->specularMaterialColor[1] = specularMaterialColor.getG();
        this->specularMaterialColor[2] = specularMaterialColor.getB();
        this->specularMaterialColor[3] = specularMaterialColor.getA();
        
    }
    inline void ProtoGeom3::setEmissionMaterialColor(const Col4f&  emissionMaterialColor){
        this->emissionMaterialColor[0] = emissionMaterialColor.getR();
        this->emissionMaterialColor[1] = emissionMaterialColor.getG();
        this->emissionMaterialColor[2] = emissionMaterialColor.getB();
        this->emissionMaterialColor[3] = emissionMaterialColor.getA();
        
    }
    
    inline ProtoTexture ProtoGeom3::getTexture()const{
        return texture;
    }
    

    
}
#define Geom3 ProtoGeom3
#endif /* defined(PROTO_GEOM3_H) */
