/*!  \brief  ProtoShader.h: class for managing shaders
 ProtoShader.h
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

#ifndef PROTO_SHADER_H
#define PROTO_SHADER_H

#if defined(_WIN32) || defined(__linux__)
#include <GL/glew.h>
#else
#include <OpenGL/gl.h>
#endif

#include <stdlib.h>
#include <string>
#include "ProtoUtility.h"

#include <sstream>
#include <fstream>


namespace ijg {

    class ProtoShader {
    public:
        ProtoShader();
        ProtoShader(const std::string& vShader, const std::string& fShader);
		ProtoShader(const ProtoShader& shdr);
		ProtoShader& operator=(const ProtoShader& shdr);
        ~ProtoShader();

        void init();

        void bind();
        void unbind();

        GLuint getID();
        GLuint shader_id;

		// encapsulate passing shader loacations 
		// for attribute and uniform vars
		void addAttribute(std::string name);
		void addUniform(std::string name);


    private:
        // must initialize these before using!!!
        std::string vShader, fShader;
        GLuint shader_vp;
        GLuint shader_fp;
        void printLog(GLuint program);

		// vector for attribute and uniform locations
		std::vector<GLuint> attribLocs, uniformLocs;

    };

	inline GLuint ProtoShader::getID() {
		return shader_id;
	}

	inline void ProtoShader::bind() {
		glUseProgram(shader_id);
	}

	inline void ProtoShader::unbind() {
		glUseProgram(0);
	}

}


#endif //PROTO_SHADER_H
