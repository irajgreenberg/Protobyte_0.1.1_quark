/*!  \brief  ProtoTexture.h: 2D texture class with w,h fields
 ProtoTexture.h
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
 This class is templated to allow for varied single collection types
 This class is part of the group common (update)
 \sa NO LINK
 */

#ifndef TEXTURE_H
#define	TEXTURE_H



#ifdef _WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl.h>
#endif

#include "FreeImage.h"
//#include<SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h> // for File input

namespace ijg {

    class ProtoTexture {
    public:

        friend class ProtoGeom3;
        
        friend std::ostream& operator<<(std::ostream& output, const ProtoTexture& texture);

        ProtoTexture();
        ProtoTexture(const std::string& textureURL, GLenum image_format=GL_RGB, GLint internal_format=GL_RGB, GLint level=0, GLint border=0, GLuint textureID=0);
    
//        ProtoTexture(const std::string& textureURL, GLuint w, GLuint h, bool isWrap);
//        ProtoTexture(unsigned char*& data, GLuint w, GLuint h, bool isWrap);
//        ProtoTexture(std::vector<unsigned char>& data, GLuint w, GLuint h, bool isWrap);
//        ProtoTexture(const int* packedData32, GLuint w, GLuint h, bool isWrap);

        // getters/setters
        void setH(GLuint h);
        GLuint getH() const;
        void setW(GLuint w);
        GLuint getW() const;
        void setTextureURL(std::string textureURL);
        std::string getTextureURL() const;
        void setTextureID(GLuint textureID);
        GLuint getTextureID() const;




    private:
        std::string textureURL;
        GLenum image_format;
        GLint internal_format;
        GLint level;
        GLint border;
        
        GLuint w;
        GLuint h;
        bool isWrap;
        GLuint textureID;

        bool init();
    };

    inline void ProtoTexture::setH(GLuint h) {
        this->h = h;
    }

    inline GLuint ProtoTexture::getH() const {
        return h;
    }

    inline void ProtoTexture::setW(GLuint w) {
        this->w = w;
    }

    inline GLuint ProtoTexture::getW() const {
        return w;
    }

    inline void ProtoTexture::setTextureURL(std::string textureURL) {
        this->textureURL = textureURL;
    }

    inline std::string ProtoTexture::getTextureURL() const {
        return textureURL;
    }

    inline void ProtoTexture::setTextureID(GLuint textureID) {
        this->textureID = textureID;
    }

    inline GLuint ProtoTexture::getTextureID() const {
        return textureID;
    }

}

#endif	// TEXTURE_H

