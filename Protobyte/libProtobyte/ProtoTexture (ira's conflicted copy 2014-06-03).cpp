/*!  \brief  ProtoProtoTexture.cpp: 2D texture class with w,h fields
 ProtoProtoTexture.cpp
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

#include "ProtoTexture.h"



namespace ijg {
    

    std::ostream& operator<<(std::ostream& output, const ProtoTexture& texture) {
        output << "texture2.textureURL: " << texture.textureURL <<
                ", texture2.w: " << texture.w <<
                ", texture2.h: " << texture.h <<
                ", texture2.textureID: " << texture.textureID;
        return output;
    }

}

using namespace ijg;

ProtoTexture::ProtoTexture() {
    textureURL = "";
}

// one being used
ProtoTexture::ProtoTexture(const std::string& textureURL, GLenum image_format, GLint internal_format, GLint level, GLint border,  GLuint textureID):
textureURL(textureURL), image_format(image_format), internal_format(internal_format), level(level), border(border), textureID(textureID)  {
   // std::cout << "in ProtoTexture class, ProtoTexture::textureID = " <<  ProtoTexture::textureID << std::endl;
    init();
}




bool ProtoTexture::init() {
    if (textureURL != "") {
        
        // FreeImage implementaiont from:
        //Singleton Texture Manager class
        //Written by Ben English
        //benjamin.english@oit.edu
        
        //image format
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        //pointer to the image, once loaded
        FIBITMAP *dib(0);
        //pointer to the image data
        BYTE* imageData(0);
        //image width and height
        unsigned int width(0), height(0);
        //OpenGL's image ID to map to
        GLuint gl_texID;
        
        //check the file signature and deduce its format
        const char* fileURL = textureURL.c_str();
        fif = FreeImage_GetFileType(fileURL, 0);
        //if still unknown, try to guess the file format from the file extension
        if(fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(fileURL);
        //if still unkown, return failure
        if(fif == FIF_UNKNOWN)
            return false;
        
        //check that the plugin has reading capabilities and load the file
        if(FreeImage_FIFSupportsReading(fif))
            dib = FreeImage_Load(fif, fileURL);
        //if the image failed to load, return failure
        if(!dib)
            return false;
        
        //retrieve the image data
        imageData = FreeImage_GetBits(dib);
        //get the image width and height
        width = FreeImage_GetWidth(dib);
        height = FreeImage_GetHeight(dib);
        //std::cout << "image width = " << width << std::endl;
        //std::cout << "image height = " << height << std::endl;
        //if this somehow one of these failed (they shouldn't), return failure
        if((imageData == 0) || (width == 0) || (height == 0))
            return false;
        
        
        // texture creation/loading code from:
        // http://www.nullterminator.net/gltexture.html
        
        
        // allocate a texture name
        // now handled in ProtoGeom3
        //glGenTextures(1, &textureID);
        
        
        // select our current texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        
        // select modulate to mix texture with color for shading
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        
        // when texture area is small, bilinear filter the closest MIP map
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_NEAREST);
        // when texture area is large, bilinear filter the first MIP map
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // if wrap is true, the texture wraps over at the edges (repeat)
        //       ... false, the texture ends at the edges (clamp)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        isWrap ? GL_REPEAT : GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                        isWrap ? GL_REPEAT : GL_CLAMP);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
		//std::cout << "texture width =" << width << std::endl;
		// give opengl the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
        
        // build our texture mipmaps
        //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        // free memory
        //delete [] data;
        
        //Free FreeImage's copy of the data
        FreeImage_Unload(dib);
        
        //return success
        return true;
    }
    return false;
}



