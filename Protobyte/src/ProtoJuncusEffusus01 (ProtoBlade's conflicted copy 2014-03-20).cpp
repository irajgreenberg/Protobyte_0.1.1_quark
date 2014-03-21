/*!  \brief  ProtoJuncusEffusus01.h: Single wrapped starnd study
 ProtoJuncusEffusus01.h
 Protobyte Library v02

 Created by Ira on 3/3/14.
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

#include "ProtoJuncusEffusus01.h"


using namespace ijg;


void ProtoJuncusEffusus01::init() {

	setBackground(0);

	globalAmbient = ProtoLight(Col4f(.2f, .15f, .22f, 1)); // slight violet color


	
	
	//lightsOn();

	// light0
	light0.setPosition(Vec3f(0, 0, 1));
	light0.setDiffuse(Col4f(1, 1, 1, 1.0f));
	light0.setAmbient(Col4f(.3, .3, .3, 1.0));
	light0.setSpecular(Col4f(1, 1, 1, 1.0));
	light0.on();

	// light1
	light1.setPosition(Vec3f(0, -27, 20));
	light1.setDiffuse(Col4f(1, 1, 1, 1.0));
	light1.setAmbient(Col4f(.55, .55, .75, 1.0));
	light1.setSpecular(Col4f(1, .6, .8, 1.0));
	light1.on();

	// light 2
	light2.setPosition(Vec3f(50, -12, -130));
	light2.setDiffuse(Col4f(.7, .3, .6, 1.0));
	light2.setAmbient(Col4f(.5, .2, .2, 1.0));
	light2.setSpecular(Col4f(1, 1, 1, 1.0));
	light2.off();
		
		//   ProtoSpline3(const std::vector<Vec3f>& controlPts, int interpDetail, bool isCurveClosed, float smoothness);
	//Spline3 path();

	Dim2f arrayDim(5.75, 16.5);
	int rows = 5;
	int columns = 5;
	float rowH = arrayDim.h / (rows-1);
	float colW = arrayDim.w / (columns-1);
	tubuleCount = rows*columns;
	//tubules.reserve(tubuleCount);
	//tubulesWraps.reserve(tubuleCount);

	// Note: counters int r, int c
	for (int r = 0; r < rows; ++r){
		for (int c = 0; c < columns; ++c){
			int ind = r*columns + c;
			//trace("ind =", ind);
			float theta = 0.0f;
			float tubuleRadius = 2.2;//8.73f;
			float tubuleLen = 2.875;
			int tubuleSegs = 9;
			float tubuleStep = tubuleLen / tubuleSegs;
			int tubuleInterpDetail = 2;//6;
			int tubuleDetail = 12;//18;



			std::vector<Vec3f> cps;

			Vec3 pos = Vec3f(0, tubuleLen / 2, 0);
			for (int k = 0; k < tubuleSegs; ++k){
				if (k < 3){
					cps.push_back(Vec3f(pos.x + random(-.22, .22), pos.y - tubuleStep*k, pos.z + random(-.22, .22)));
				}
				else {
					cps.push_back(Vec3f(pos.x + random(-.06, .06), pos.y - tubuleStep*k, pos.z + random(-.06, .06)));
				}
			}
			// tapered
			//            tubule = Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .08), tubuleDetail, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(tubuleRadius, .21), 1),true, "reptile3.jpg");

			// curvey
			tubules.push_back(Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .08), tubuleDetail, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleRadius, .18), 6), true, "reptile3.jpg"));

			// l-r and f-b
			if (columns == 1){
				tubules.at(ind).setPosition(Vec3f(colW*c, 0, -rowH*r));
			}
			else {
				tubules.at(ind).setPosition(Vec3f(-arrayDim.w / 2.0f + colW*c, 0, -rowH*r));
			}
				
			tubules.at(ind).textureOn();
			tubules.at(ind).setTextureScale(1.0);
			tubules.at(ind).setShininess(104);
			tubules.at(ind).setColor(Col4f(1, 1, 1, 1));




			//    
			std::vector<Vec3f> pts;
			float ht = 2.1f;
			int segs = 125;//325;
			float step = ht / segs;
			theta = 0;
			float phi = 0;
			float radius = .125f;
			float tubuleBuldgeMin = .55f, tubuleBuldgeMax = 1.95f;
			// don't think I need this anymore
			for (int i = 0; i < segs; ++i){
				//radius = tubuleRadius*random(.98f, 1.01);
				//pts.push_back(Vec3f(sin(theta)*(radius + random(.02f, .04f)), -tubuleLen*.245 + step*.175f*i + cos(phi)*random(.05f, .175f), cos(theta)*(radius + random(.02f, .04f))));
				//pts.push_back(Vec3f(sin(theta)*(radius), -tubuleLen*.5 + step*.8375f*i + cos(phi)*random(.05f, .175f), cos(theta)*(radius )));

				//        pts.push_back(Vec3f(random(-sin(theta)*(radius + random(.02f, .04f)), sin(theta)*(radius + random(.02f, .04f))), -tubuleLen*.265 + step*.5375f*i + cos(phi)*random(.05f, .175f), random(-cos(theta)*(radius + random(.02f, .04f)), cos(theta)*(radius + random(.02f, .04f)))));


				theta += PI / segs*random(60, 100);
				phi += PI / random(3, 6);
			}

			//trace("tubule.getVertices().size() =", tubule.getVertices().size());
			for (int i = 0; i < tubules.at(ind).getVertices().size() - 2; ++i){
				// trace("tubule.getVertices() =", tubule.getVertices().at(i).pos);
				pts.push_back(tubules.at(ind).getVertices().at(i).pos);
			}


			for (int i = 0; i < tubules.at(ind).getInterleavedPrims().size(); i += 12){
				// trace("tubule.getVertices() =", tubule.getVertices().at(i).pos);
				float x = tubules.at(ind).getInterleavedPrims().at(i);
				float y = tubules.at(ind).getInterleavedPrims().at(i + 1);
				float z = tubules.at(ind).getInterleavedPrims().at(i + 2);
				// pts.push_back(Vec3(x, y, z));
			}


			Spline3 s(pts, 2, false, .5);
			//tubulesWrap = Tube(s, .165, 4, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(.095, .19), 40), true);
			tubulesWraps.push_back(Tube(s, .03, 6/*12*/, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleBuldgeMin, tubuleBuldgeMax/*2.1*/), 40), true, "leather2.jpg"));
			tubulesWraps.at(ind).setColor(Col4f(.3f, .25f, .2f, 1));
			tubulesWraps.at(ind).textureOn();
		}
	}

	ground = GroundPlane(Vec3f(0, 0/*tubules.at(0).getPosition().y*/, 0), Vec3f(), Dim2f(170, 60), Col4f(.5, .3, .4, 1), 1, 1, "metal_grate.jpg", .02f); 
	//ground = GroundPlane(Vec3f(0, 0/*tubules.at(0).getPosition().y*/, 0), Vec3f(), Dim2f(170, 60), Col4f(.5, .3, .4, 1), 1, 1);
	ground.setTextureScale(.02f);
	ground.textureOn();
	

	shadowMapShader = ProtoShader("shadowMap.vert", "shadowMap.frag");
	shader = ProtoShader("shader1.vert", "shader1.frag");
	shader.bind();




	//trace("ProtoUtility::getPathToOutput() =", ProtoUtility::getPathToOutput());


	//********************** glm tests ********************************//
	// START standard transformation matrices: ModelView / Projection / Normal
	gl_viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	gl_modelMatrix = glm::mat4(1.0f); // set to identity
	gl_modelViewMatrix = gl_viewMatrix*gl_modelMatrix;
	gl_normalMatrix = glm::transpose(glm::inverse(glm::mat3(gl_modelViewMatrix)));

	// projection matrix and MVP Matrix
	float viewAngle = 65.0f;
	float aspect = width / height;
	float nearDist = .1f;
	float farDist = 2000.0f;

	gl_projectionMatrix = glm::perspective(viewAngle, aspect, nearDist, farDist);
	gl_modelViewProjectionMatrix = gl_projectionMatrix * gl_modelViewMatrix;
	// END Model / View / Projection data

	// tranformation matricies
	gl_translationMatrix = glm::mat4(1.0f);
	gl_rotationMatrix = glm::mat4(1.0f);
	gl_scaleMatrix = glm::mat4(1.0f);
	

	// START get all uniform shaders
	GLint nUniforms, maxLen;
	glGetProgramiv(shader.getID(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv(shader.getID(), GL_ACTIVE_UNIFORMS, &nUniforms);

	GLchar* name = (GLchar*)malloc(maxLen);

	GLint size, location;
	GLsizei written;
	GLenum type;
	printf("\n Location | Name\n");
	printf("--------------------------------------------------\n");
	for (int i = 0; i<nUniforms; ++i){
		glGetActiveUniform(shader.getID(), i, maxLen, &written, &size, &type, name);
		location = glGetUniformLocation(shader.getID(), name);
		printf(" %-8d | %s\n", location, name);
	}
	free(name);
	// END get all uniform shaders

	// get info about renderers
	trace("renderer =", glGetString(GL_RENDERER));
	trace("vendor =", glGetString(GL_VENDOR));
	trace(" version =", glGetString(GL_VERSION));
	trace("glslVersion =", glGetString(GL_SHADING_LANGUAGE_VERSION));

	trace("vertexPosition Location =", glGetAttribLocation(shader.getID(), "vertexPosition"));
	trace("vertexNormal Location =", glGetAttribLocation(shader.getID(), "vertexNormal"));
	trace("vertexColor Location =", glGetAttribLocation(shader.getID(), "vertexColor"));
	trace("vertexTexture Location =", glGetAttribLocation(shader.getID(), "vertexTexture"));

	// Lighting 
	//GLuint gl_light0PositionLocation = glGetUniformLocation(shader.getID(), "light0Position");
	//if (gl_light0PositionLocation >= 0){
	//	glUniform3fv(gl_light0PositionLocation, 1, &light0.getPosition().x);
	//}

	//float dl[4];
	//dl[0] = .4;
	//dl[1] = .5;
	//dl[2] = .6;
	//dl[3] = .2234;
	//GLuint gl_light0DiffuseLocation = glGetUniformLocation(shader.getID(), "light0Diffuse");
	//if (gl_light0DiffuseLocation >= 0){
	//	glUniform4fv(gl_light0DiffuseLocation, 1, dl);
	//}

	//GLuint gl_light0AmbientLocation = glGetUniformLocation(shader.getID(), "light0Ambient");
	//if (gl_light0AmbientLocation >= 0){
	//	glUniform4fv(gl_light0AmbientLocation, 1, &light0.getAmbient().r);
	//}

	//GLuint gl_light0SpecularLocation = glGetUniformLocation(shader.getID(), "light0Specular");
	//if (gl_light0SpecularLocation >= 0){
	//	glUniform4fv(gl_light0SpecularLocation, 1, &light0.getSpecular().r);
	//}


	/**************************************
	Start FrameBuffer Object for Shadow Map
	**************************************/
	initShadowMap();

	/**************************************
	End FrameBuffer Object
	**************************************/
}


void ProtoJuncusEffusus01::run() {
	setBackground(0);
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glViewport(0, 0, width, height);

	

	/******************** Realy Important *******************/
	// You MUST bind shader prior to working with Uniforms  //
	/******************** Still Important *******************/
	//shader.bind();

	// Lighting 
	float ltPos[] = {.5f, .5f, 20};
	GLuint gl_light0PositionLocation = glGetUniformLocation(shader.getID(), "light0Position");
	if (gl_light0PositionLocation >= 0){
		glUniform3fv(gl_light0PositionLocation, 1, &light0.getPosition().x);
	}

	GLuint gl_light0DiffuseLocation = glGetUniformLocation(shader.getID(), "light0Diffuse");
	if (gl_light0DiffuseLocation >= 0){
		glUniform4fv(gl_light0DiffuseLocation, 1, &light0.getDiffuse().r);
	}

	GLuint gl_light0AmbientLocation = glGetUniformLocation(shader.getID(), "light0Ambient");
	if (gl_light0AmbientLocation >= 0){
		glUniform4fv(gl_light0AmbientLocation, 1, &light0.getAmbient().r);
	}

	GLuint gl_light0SpecularLocation = glGetUniformLocation(shader.getID(), "light0Specular");
	if (gl_light0SpecularLocation >= 0){
		glUniform4fv(gl_light0SpecularLocation, 1, &light0.getSpecular().r);
	}

	if (frameCount == 1){
		// currently only works with max 999 tiles
		save("juncs", 12);
	}

	render();
}

void ProtoJuncusEffusus01::setShadowMapTransform(){
	glm::vec3 lightInvDir = glm::vec3(0.5f, 2, 2);

	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);
	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// Compute the MVP matrix from the light's point of view
	GLuint shadowMapMatrixLocation = glGetUniformLocation(shader.getID(), "shadowMapMVPMatrix");
	if (shadowMapMatrixLocation >= 0){
		glUniformMatrix4fv(shadowMapMatrixLocation, 1, GL_FALSE, &depthMVP[0][0]);
	}
}

void ProtoJuncusEffusus01::render(){
	setShadowMapTransform();

	for (int i = 0; i <tubuleCount; ++i){
		//trace("tubuleCount =", tubuleCount);
		//GLuint gl_textureLocation = glGetUniformLocation(shader.getID(), "vertexTextureCoords");		gl_scaleMatrix = glm::mat4(1.0);
		gl_rotationMatrix = glm::mat4(1.0);
		gl_translationMatrix = glm::mat4(1.0);
		gl_scaleMatrix = glm::mat4(1.0f);
		gl_translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, -3, 0));

		gl_viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		gl_modelMatrix = gl_translationMatrix * gl_rotationMatrix * gl_scaleMatrix;
		gl_modelViewMatrix = gl_viewMatrix*gl_modelMatrix;
		gl_modelViewProjectionMatrix = gl_projectionMatrix * gl_modelViewMatrix;

		// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
		// update normals
		gl_normalMatrix = glm::transpose(glm::inverse(glm::mat3(gl_modelViewMatrix)));


		// connect Uniforms to GLSL
		// modelView matrix
		GLuint gl_modelViewMatrixLocation = glGetUniformLocation(shader.getID(), "modelViewMatrix");
		if (gl_modelViewMatrixLocation >= 0){
			glUniformMatrix4fv(gl_modelViewMatrixLocation, 1, GL_FALSE, &gl_modelViewMatrix[0][0]);
		}

		// modelViewProjection matrix
		GLuint gl_modelViewProjectionMatrixLocation = glGetUniformLocation(shader.getID(), "modelViewProjectionMatrix");
		if (gl_modelViewProjectionMatrixLocation >= 0){
			glUniformMatrix4fv(gl_modelViewProjectionMatrixLocation, 1, GL_FALSE, &gl_modelViewProjectionMatrix[0][0]);
		}

		// normal matrix
		GLuint gl_normalMatrixLocation = glGetUniformLocation(shader.getID(), "normalMatrix");
		if (gl_normalMatrixLocation >= 0){
			glUniformMatrix3fv(gl_normalMatrixLocation, 1, GL_FALSE, &gl_normalMatrix[0][0]);
		}

		ground.display();

		// now deal with tendrils
		gl_scaleMatrix = glm::mat4(1.0);
		gl_rotationMatrix = glm::mat4(1.0);
		gl_translationMatrix = glm::mat4(1.0);

		gl_scaleMatrix = glm::mat4(1.0f);
		gl_rotationMatrix = glm::rotate(glm::mat4(1.0f), float(frameCount*.06), glm::vec3(0, 1, 0));
		gl_translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(tubules.at(i).getPosition().x, tubules.at(i).getPosition().y, tubules.at(i).getPosition().z-.75f));

		gl_viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		gl_modelMatrix = gl_translationMatrix * gl_rotationMatrix * gl_scaleMatrix;
		gl_modelViewMatrix = gl_viewMatrix*gl_modelMatrix;
		gl_modelViewProjectionMatrix = gl_projectionMatrix * gl_modelViewMatrix;

		// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
		// update normals
		gl_normalMatrix = glm::transpose(glm::inverse(glm::mat3(gl_modelViewMatrix)));


		// connect Uniforms to GLSL
		// modelView matrix
		//GLuint gl_modelViewMatrixLocation = glGetUniformLocation(shader.getID(), "modelViewMatrix");
		if (gl_modelViewMatrixLocation >= 0){
			glUniformMatrix4fv(gl_modelViewMatrixLocation, 1, GL_FALSE, &gl_modelViewMatrix[0][0]);
		}

		// modelViewProjection matrix
		//GLuint gl_modelViewProjectionMatrixLocation = glGetUniformLocation(shader.getID(), "modelViewProjectionMatrix");
		if (gl_modelViewProjectionMatrixLocation >= 0){
			glUniformMatrix4fv(gl_modelViewProjectionMatrixLocation, 1, GL_FALSE, &gl_modelViewProjectionMatrix[0][0]);
		}

		// normal matrix
		//GLuint gl_normalMatrixLocation = glGetUniformLocation(shader.getID(), "normalMatrix");
		if (gl_normalMatrixLocation >= 0){
			glUniformMatrix3fv(gl_normalMatrixLocation, 1, GL_FALSE, &gl_normalMatrix[0][0]);
		}

		//scale(1.3, 1.3, 1.3);
		tubules.at(i).display(WIREFRAME);
		tubulesWraps.at(i).display();

	}



	//for (int i = 0; i < beings; ++i){
	//	//GLuint gl_textureLocation = glGetUniformLocation(shader.getID(), "vertexTextureCoords");
	//	gl_scaleMatrix = glm::mat4(1.0);
	//	gl_rotationMatrix = glm::mat4(1.0);
	//	gl_translationMatrix = glm::mat4(1.0);

	//	gl_scaleMatrix = glm::mat4(1.0f);
	//	gl_rotationMatrix = glm::rotate(glm::mat4(1.0f), float(frameCount*.0006), glm::vec3(0, 1, 0));
	//	gl_translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(locs.at(i).x, locs.at(i).y, locs.at(i).z));

	//	gl_viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	//	gl_modelMatrix = gl_translationMatrix * gl_rotationMatrix * gl_scaleMatrix;
	//	gl_modelViewMatrix = gl_viewMatrix*gl_modelMatrix;
	//	gl_modelViewProjectionMatrix = gl_projectionMatrix * gl_modelViewMatrix;

	//	// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
	//	// update normals
	//	gl_normalMatrix = glm::transpose(glm::inverse(glm::mat3(gl_modelViewMatrix)));


	//	// connect Uniforms to GLSL
	//	// modelView matrix
	//	GLuint gl_modelViewMatrixLocation = glGetUniformLocation(shader.getID(), "modelViewMatrix");
	//	if (gl_modelViewMatrixLocation >= 0){
	//		glUniformMatrix4fv(gl_modelViewMatrixLocation, 1, GL_FALSE, &gl_modelViewMatrix[0][0]);
	//	}

	//	// modelViewProjection matrix
	//	GLuint gl_modelViewProjectionMatrixLocation = glGetUniformLocation(shader.getID(), "modelViewProjectionMatrix");
	//	if (gl_modelViewProjectionMatrixLocation >= 0){
	//		glUniformMatrix4fv(gl_modelViewProjectionMatrixLocation, 1, GL_FALSE, &gl_modelViewProjectionMatrix[0][0]);
	//	}

	//	// normal matrix
	//	GLuint gl_normalMatrixLocation = glGetUniformLocation(shader.getID(), "normalMatrix");
	//	if (gl_normalMatrixLocation >= 0){
	//		glUniformMatrix3fv(gl_normalMatrixLocation, 1, GL_FALSE, &gl_normalMatrix[0][0]);
	//	}



	//	//scale(1.3, 1.3, 1.3);
	//	//tubule.display();
	//	tubulesWrap.display();

	//}
}


void ProtoJuncusEffusus01::save(std::string name, int scaleFactor){


#if defined (_WIN32) || defined(_WIN64)
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
#else // os x uses localtime instead of localtime_s
	time_t now = time(0);
	tm* ltm = localtime(&now);
#endif

	// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
	std::stringstream stream;
	stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;



	std::string url = ProtoUtility::getPathToOutput();
	std::string directory = url + "ProtoJuncusEffusus01_" + stream.str();
	CreateDirectory(directory.c_str(), 0);


	for (int i = 0; i < scaleFactor; ++i){
		for (int j = 0; j < scaleFactor; ++j){
				//trace("in drawToFrameBuffer");
				glClearColor(0, 0, 0, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				//From: http://stackoverflow.com/questions/12157646/how-to-render-offscreen-on-opengl

				glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
				render();

				//after drawing
				std::vector<uint8_t> data(width * height * 3);
				glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);



#if defined (_WIN32) || defined(_WIN64)
                time_t now = time(0);
				tm ltm;
				localtime_s(&ltm, &now);
#else // os x uses localtime instead of localtime_s
                time_t now = time(0);
				tm* ltm = localtime(&now);
#endif
                

				// FROM http://stackoverflow.com/questions/5844858/how-to-take-screenshot-in-opengl
				// Convert to FreeImage format & save to file
				FIBITMAP* image = FreeImage_ConvertFromRawBits(&data[0], width, height, 3 * width, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);


				// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
				//std::stringstream stream;
#if defined (_WIN32) || defined(_WIN64)
               // stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
				// c++ 11 conversion form num to string
				//std::string url = "\\Users\\Ira\\Desktop\\ProtoJucnusEffusus01_stills\\" + name + "_" + std::to_string(i*scaleFactor+j) + ".jpg";
				
				// ensure no single digit nums, for easy sorting
				std::string imgNum;

				if (i*scaleFactor + j<10){
					imgNum = "00" + std::to_string(i*scaleFactor + j);
				} else if (i*scaleFactor + j<100){
					imgNum =  "0" + std::to_string(i*scaleFactor + j);
				}
				else {
					imgNum = std::to_string(i*scaleFactor + j);
				}
				
				std::string tileURL = directory + "\\" + name + "_" + imgNum + ".jpg";
#else
               // stream << (ltm->tm_year + 1900) << "_" << (ltm->tm_mon + 1) << "_" << ltm->tm_mday << "_" << ltm->tm_hour << "_" << ltm->tm_min << "_" << ltm->tm_sec;
				// c++ 11 conversion form num to string
				std::string url = "/Users/33993405/Desktop/ProtoJucnusEffusus01_stills/" + namme + "_" + std::to_string(i*scaleFactor+j) + ".jpg";
#endif
                
				FreeImage_Save(FIF_JPEG, image, tileURL.c_str(), 0);

				// Free resources
				FreeImage_Unload(image);


				// Return to onscreen rendering:
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			}
		}
	//trace("ProtoUtility::getPath() =", ProtoUtility::getPath());
	bool isOk = stitchTiles(directory, scaleFactor);
}

bool ProtoJuncusEffusus01::stitchTiles(std::string url, int tiles){
	trace(" url =", url);
	url += "\\"; 
	std::vector<std::string> fileNames = ProtoUtility::getFileNames(url);
	for (size_t i = 0; i < fileNames.size(); ++i){
		//trace(fileNames.at(i));
	}
	// composite image creation
	// procedure
	// 1. grab all file names in directory and store in store in vector
	// 2. sort by name
	// 3. grab images by names
	// 4. copy and paste tiles into compostie image
	// 5. save image back to disk.

	FIBITMAP *compositeImg = FreeImage_Allocate(width*tiles, height*tiles, 24, 0xFF0000, 0x00FF00, 0x0000FF);
	//FreeImage_Allo
	



	for (int i = 0; i < tiles; ++i){
		for (int j = 0; j < tiles; ++j){

			int id = i*tiles + j;

			//image format
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			//pointer to the image, once loaded
			FIBITMAP *img(0);
			//pointer to the image data
			BYTE* imageData(0);
			//image width and height
			unsigned int width(0), height(0);
			//OpenGL's image ID to map to
			GLuint gl_texID;

			//check the file signature and deduce its format

			std::string path = url + fileNames.at(id);
			const char* fileURL = path.c_str();
			fif = FreeImage_GetFileType(fileURL, 0);
			//if still unknown, try to guess the file format from the file extension
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(fileURL);
			//if still unkown, return failure
			if (fif == FIF_UNKNOWN)
				return false;

			//check that the plugin has reading capabilities and load the file
			if (FreeImage_FIFSupportsReading(fif))
				img = FreeImage_Load(fif, fileURL);
			//if the image failed to load, return failure
			if (!img)
				return false;

			//retrieve the image data
			imageData = FreeImage_GetBits(img);
			//get the image width and height
			width = FreeImage_GetWidth(img);
			height = FreeImage_GetHeight(img);
			//std::cout << "image width = " << width << std::endl;
			//std::cout << "image height = " << height << std::endl;
			//if this somehow one of these failed (they shouldn't), return failure
			if ((imageData == 0) || (width == 0) || (height == 0))
				return false;

			// copy and paste bits
			FIBITMAP * piece = FreeImage_Copy(img, 0, height, width, 0);
			FreeImage_Paste(compositeImg, piece, width*i, (height*(tiles-1))-height*j, 255);


			//Free FreeImage's copy of the data
			FreeImage_Unload(img);
		}
	}

	// cleanup Memory
	if (compositeImg) {
		// bitmap successfully created!

//#if defined (_WIN32) || defined(_WIN64)
//		time_t now = time(0);
//		tm ltm;
//		localtime_s(&ltm, &now);
//#else // os x uses localtime instead of localtime_s
//		time_t now = time(0);
//		tm* ltm = localtime(&now);
//#endif
//
//		// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
//		std::stringstream stream;
//		stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
//
//
//
//		std::string folder = url + "ProtoJuncusEffusus01_" + stream.str();
//		CreateDirectory(folder.c_str(), 0);
		std::string compositeName = url + "\\ProtoJuncusEffusus01.jpg";
		FreeImage_Save(FIF_JPEG, compositeImg, compositeName.c_str(), 0);
		FreeImage_Unload(compositeImg);
	}
	
	
	return true;
}

bool ProtoJuncusEffusus01::initShadowMap(){
	

	// Depth texture for Frame Buffer. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTexture);


	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName); 
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false; 
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	return true;
}

