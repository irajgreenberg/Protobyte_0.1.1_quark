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
 Inspiration and assistance from: http://subversion.assembla.com/svn/184/src/LoadImage.cpp
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

// called from Geom3 class, which manages unique textureID's - for access in shader
//ProtoTexture::ProtoTexture(const std::string& textureURL, GLuint textureID) :
//textureURL(textureURL), textureID(textureID) {
//	createNormalMap();
//}

// one being used
ProtoTexture::ProtoTexture(const std::string& textureURL, GLenum image_format, GLint internal_format, GLint level, GLint border, GLuint textureID) :
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
		FIBITMAP* dib(0);
		//pointer to the image data
		BYTE* imageData(0);
		//image width and height
		unsigned int width(0), height(0);
		//OpenGL's image ID to map to
		// GLuint gl_texID;

		//check the file signature and deduce its format
		const char* fileURL = textureURL.c_str();
		fif = FreeImage_GetFileType(fileURL, 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(fileURL);
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return false;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, fileURL);
		//if the image failed to load, return failure
		if (!dib)
			return false;

		//retrieve the image data
		imageData = FreeImage_GetBits(dib);
		//get the image width and height
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);

		//std::cout << "image width = " << width << std::endl;
		//std::cout << "image height = " << height << std::endl;
		//if this somehow one of these failed (they shouldn't), return failure
		if ((imageData == 0) || (width == 0) || (height == 0))
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
			GL_LINEAR_MIPMAP_LINEAR);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
	/*	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
			isWrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			isWrap ? GL_REPEAT : GL_CLAMP);*/

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//std::cout << "texture width =" << width << std::endl;
		// give opengl the texture
		// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_BGR, GL_UNSIGNED_BYTE, imageData);

		//Free FreeImage's copy of the data
		FreeImage_Unload(dib);

		//return success
		return true;
	}
	return false;
}


bool ProtoTexture::createNormalMap(const std::string& textureURL, GLuint textureID)  {
	if (textureURL != "") {
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP* heightMap(0);
		//pointer to the image data
		BYTE* imageData(0);
		//check the file signature and deduce its format
		const char* fileURL = textureURL.c_str();
		fif = FreeImage_GetFileType(fileURL, 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(fileURL);
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return false;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			heightMap = FreeImage_Load(fif, fileURL);
		//if the image failed to load, return failure
		if (!heightMap)
			return false;


		// get grayscale values(aka height map)
		unsigned width = FreeImage_GetWidth(heightMap);
		unsigned height = FreeImage_GetHeight(heightMap);
		float* greyVals = new float[width*height]; // rmember to clean up

		//manual conversion to greyscale
		for (int i = 0; i < height; ++i){
			for (int j = 0; j < width; ++j){
				RGBQUAD col;
				FreeImage_GetPixelColor(heightMap, j, i, &col);
				float r = col.rgbRed;
				float g = col.rgbGreen;
				float b = col.rgbBlue;
				greyVals[i*width + j] = (r*.21 + g*.72 + b*.07) / 255.0;
				//greyVals[i*width + j] = (r+g+b)/3 / 255.0;

			}
		}

		FreeImage_Unload(heightMap);

		// eventually create other operator options
		int sobelX[] = {
			1, 0, -1, 2, 0, -2, 1, 0, -1
		};
		int sobelY[] = {
			1, 2, 1, 0, 0, 0, -1, -2, -1
		};

		// bumpier <-  .5  -> smoother - eventually obviously paramerterize
		float bumpinessFactor = .5;

		// allocate for normal map
		FIBITMAP* normalMap = FreeImage_Allocate(width, height, 24);

		int k0, k1, k2,
			k3, k4, k5,
			k6, k7, k8;
		RGBQUAD color;

		for (int i = 0, k = 0; i < height; ++i){
			for (int j = 0; j < width; ++j){

				// within edge safety limit
				if (i>0 && i<height - 1 && j>0 && j < width - 1){

					k0 = (i - 1)*width + (j - 1);
					k1 = (i - 1)*width + j;
					k2 = (i - 1)*width + (j + 1);

					k3 = i*width + (j - 1);
					k4 = i*width + j;
					k5 = i*width + (j + 1);

					k6 = (i + 1)*width + (j - 1);
					k7 = (i + 1)*width + j;
					k8 = (i + 1)*width + (j + 1);


					float x = greyVals[k0] * sobelX[0] + greyVals[k1] * sobelX[1] + greyVals[k2] * sobelX[2] +
						greyVals[k3] * sobelX[3] + greyVals[k4] * sobelX[4] + greyVals[k5] * sobelX[5] +
						greyVals[k6] * sobelX[6] + greyVals[k7] * sobelX[7] + greyVals[k8] * sobelX[8];


					float y = greyVals[k0] * sobelY[0] + greyVals[k1] * sobelY[1] + greyVals[k2] * sobelY[2] +
						greyVals[k3] * sobelY[3] + greyVals[k4] * sobelY[4] + greyVals[k5] * sobelY[5] +
						greyVals[k6] * sobelY[6] + greyVals[k7] * sobelY[7] + greyVals[k8] * sobelY[8];


					//sqrt(1-(cx*cx+cy*cy))
					float z = bumpinessFactor * sqrt(1.0f - x * x + y * y);

					Vec3f v(x * 2, y * 2, z);
					v.normalize();
					color.rgbRed = (v.x * 0.5f + .5f) * 255;
					color.rgbGreen = (v.y * 0.5f + .5f) * 255;
					color.rgbBlue = (v.z * 0.5f + .5f) * 255;
					FreeImage_SetPixelColor(normalMap, j, i, &color);
				}
			}
		}

		delete[] greyVals;

		//

		// retrieve the image data
		BYTE* normalMapData = FreeImage_GetBits(normalMap);

		// check this all actually worked
		//get the image width and height
		width = FreeImage_GetWidth(normalMap);
		height = FreeImage_GetHeight(normalMap);

		//if this somehow one of these failed (they shouldn't), return failure
		if ((normalMapData == 0) || (width == 0) || (height == 0))
			return false;

		// send normal map to GL 
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		/*	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
		isWrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		isWrap ? GL_REPEAT : GL_CLAMP);*/

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// build our texture mipmaps
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_LUMINANCE, width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, normalMapData);
		//	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);

		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_BGR, GL_UNSIGNED_BYTE, normalMapData);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, normalMapData);

		// deallocate
		FreeImage_Unload(normalMap);

		//return success
		return true;
	}
	return false;
}


