//
//  ProtoBaseApp.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/26/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//


#include "ProtoBaseApp.h"

using namespace ijg;


ProtoBaseApp* ProtoBaseApp::baseApp = 0;

// NOTE: called before GL context created
ProtoBaseApp::ProtoBaseApp() {

	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());

	ProtoBaseApp::baseApp = this;
}

ProtoBaseApp::ProtoBaseApp(const ProtoOSC& listener) :
listener(listener){

	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());

	ProtoBaseApp::baseApp = this;
}

ProtoBaseApp* ProtoBaseApp::getBaseApp() {
	return ProtoBaseApp::baseApp;
}


void ProtoBaseApp::_init(){
	//trace(ProtoBaseApp::baseApp);
	//areShadowsEnabled = true;
	//shader = ProtoShader("shader1.vert", "shader1.frag");
	//shader = ProtoShader("protoShader.vert", "protoShader.frag");
	//shader2D = ProtoShader("colorOnlyShader.vert.glsl", "colorOnlyShader.frag.glsl");
	shader3D = ProtoShader("bumpmapping.vs.glsl", "bumpmapping.fs.glsl");



	// default global ambient
	globalAmbient = Col3f(.02f, .02f, .02f);

	// camera at 11
	// default inital light
	//light0.setPosition(Vec3f(-1.9, .9, 8));
	light0.setPosition(Vec3f(0, 0, .1));
	//light0.setPosition(Vec3f(-14.2, 2.5, 8));
	light0.setIntensity(Vec3f(1, 1, 1));

	light1.setPosition(Vec3f(0, 0, 1));
	light1.setIntensity(Vec3f(0, 0, 0));

	light2.setPosition(Vec3f(0, 0, 1));
	light2.setIntensity(Vec3f(0, 0, 0));

	light3.setPosition(Vec3f(0, 0, 1));
	light3.setIntensity(Vec3f(0, 0, 0));

	light4.setPosition(Vec3f(0, 0, 1));
	light4.setIntensity(Vec3f(0, 0, 0));

	light5.setPosition(Vec3f(0, 0, 1));
	light6.setIntensity(Vec3f(0, 0, 0));

	light6.setPosition(Vec3f(0, 0, 1));
	light6.setIntensity(Vec3f(0, 0, 0));

	light7.setPosition(Vec3f(0, 0, 1));
	light7.setIntensity(Vec3f(0, 0, 0));

	// mouse
	mouseX = mouseY = mouseLastFrameX = mouseLastFrameY = 0;
	//arcball
	arcballRotX = arcballRotY = arcballRotXLast, arcballRotYLast = mouseXIn = mouseYIn = 0;
	//isArcballOn = false;

	glViewport(0, 0, width, height);

	// START standard transformation matrices: ModelView / Projection / Normal
	M = glm::mat4(1.0f); // set to identity
	V = glm::lookAt(glm::vec3(0.0, 0.0, 60), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	MV = V * M;
	N = glm::transpose(glm::inverse(glm::mat3(MV)));

	// projection matrix and MVP Matrix
	// perspective
	viewAngle = 75.0f;
	aspect = float(width) / float(height);
	// ortho
	//trace("width = ", width);
	//trace("height =", height);
	left = -width / 2;
	right = width / 2;
	bottom = -height / 2;
	top = height / 2;

	nearDist = .1f;
	farDist = 1500.0f;

	P = glm::perspective(viewAngle, aspect, nearDist, farDist);
	MVP = P * MV;
	// END Model / View / Projection data

	// tranformation matricies
	T = glm::mat4(1.0f);
	R = glm::mat4(1.0f);
	S = glm::mat4(1.0f);

	//glm::vec3 lightInvDir = glm::vec3(0.5f, 2, 2);

	//// Compute the MVP matrix from the light's point of view
	//glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	//glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//glm::mat4 depthModelMatrix = glm::mat4(1.0);
	//glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;



	// START Shadow Map Matrices
	L_MV = glm::lookAt(glm::vec3(light0.getPosition().x, light0.getPosition().y, light0.getPosition().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//L_P = glm::perspective(45.0f, 1.0f, .10f, 1000.0f);

	L_P = glm::frustum(-.1f, .1f, -.1f, .1f, .1f, 2000.0f);


	//L_P = glm::perspective(50.0f, 1.0f, .10f, 325.0f);
	//L_B = glm::scale(glm::translate(glm::mat4(1), glm::vec3(.5, .5, .5)), glm::vec3(.5, .5, .5));

	//L_B = glm::mat4(1.0);

	float ratio = getWidth() / getHeight();
	//L_B = glm::mat4(
	//	glm::vec4(.35, 0.0f, 0.0f, 0.0f),
	//	glm::vec4(0.0f, .35, 0.0f, 0.0f),
	//	glm::vec4(0.0f, 0.0f, 1, 0.0f),
	//	glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
	//);

	L_B = glm::mat4(
		glm::vec4(.5, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, .5, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, .5, 0.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
		);


	L_BP = L_B*L_P;
	L_MVBP = L_BP*L_MV;
	// END Shadow Matrices

	createShadowMap();

	// for 2D rendering - enables/disables lighting effects
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 0.0);

	// default 2D style states
	fillColor = Col4f(1, 1, 1, 1);
	strokeColor = Col4f(1, 1, 1, 1);

	// default number of points around ellipse
	ellipseDetail = 36;

	// drawing methods path
	isPathRecording = false;

	// create base primitives
	_createRect();
	_createEllipse();


	shader3D.bind();
	_initUniforms(&shader3D);

	init();

}

// create default buffers for rect function
void ProtoBaseApp::_createRect(){

	// interleaved float[] (x, y, 0, r, g, b, a) 7*4 pts
	float prims[] = {
		0, 0, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a,
		0, 0 - 1, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a,
		0 + 1, 0 - 1, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a,
		0 + 1, 0, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a
	};
	for (int i = 0; i < 28; ++i){
		rectPrims[i] = prims[i];
	}

	int inds[] = { 0, 1, 2, 0, 2, 3 };

	// vert data
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoRectID); // Create VAO
	glBindVertexArray(vaoRectID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	//GLuint vboID;
	glGenBuffers(1, &vboRectID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboRectID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof (GLfloat)* 28;
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &rectPrims[0]); // upload the data

	// indices data
	GLuint indexVboID;
	glGenBuffers(1, &indexVboID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID); // Bind element buffer

	int indsDataSize = 6 * sizeof(GL_UNSIGNED_INT);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STREAM_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &inds[0]); // upload data

	// fill state is true - need to create this
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	// draw rect
	glBindBuffer(GL_ARRAY_BUFFER, vboRectID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID);

	glEnableVertexAttribArray(0); // vertices
	glEnableVertexAttribArray(2); // color
	// stride is 6: pos(2) + col(4)
	// (x, y, r, g, b, a)
	int stride = 7;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof (GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride * sizeof (GLfloat), BUFFER_OFFSET(12)); // col

	//glDisable(GL_LIGHTING);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Disable VAO
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

// create default buffers for ellipse function
void ProtoBaseApp::_createEllipse() {
	ellipsePrims.push_back(0);
	ellipsePrims.push_back(0);
	ellipsePrims.push_back(0);
	ellipsePrims.push_back(fillColor.r);
	ellipsePrims.push_back(fillColor.g);
	ellipsePrims.push_back(fillColor.b);
	ellipsePrims.push_back(fillColor.a);

	float theta = 0.0;
	for (int i = 7; i <= ellipseDetail * 7; i += 7){
		ellipsePrims.push_back(0 + cos(theta)*1 / 2.0);
		ellipsePrims.push_back(0 + sin(theta)*1 / 2.0);
		ellipsePrims.push_back(0);
		ellipsePrims.push_back(fillColor.r);
		ellipsePrims.push_back(fillColor.g);
		ellipsePrims.push_back(fillColor.b);
		ellipsePrims.push_back(fillColor.a);
		theta += TWO_PI / ellipseDetail;
	}
	for (int i = 0, j = 1; i < ellipseDetail * 3; ++j, i += 3){
		ellipseInds.push_back(j);
		ellipseInds.push_back(0);
		if (i < ellipseDetail * 3 - 3){
			ellipseInds.push_back(j + 1);
		}
		else {
			ellipseInds.push_back(1);
		}
	}


	// vert data
	// 1. Create and bind VAO
	//GLuint vaoID;
	glGenVertexArrays(1, &vaoEllipseID); // Create VAO
	glBindVertexArray(vaoEllipseID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	//GLuint vboID;
	glGenBuffers(1, &vboEllipseID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboEllipseID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof (GLfloat)* ellipsePrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STATIC_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &ellipsePrims[0]); // upload the data

	// indices data
	//GLuint indexVboID;
	glGenBuffers(1, &indexVboEllipseID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboEllipseID); // Bind element buffer

	int indsDataSize = ellipseDetail * 3 * sizeof(GL_UNSIGNED_INT);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &ellipseInds[0]); // upload data

	// fill state is true - need to create this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// draw rect
	glBindBuffer(GL_ARRAY_BUFFER, vboEllipseID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboEllipseID);

	glEnableVertexAttribArray(0); // vertices
	glEnableVertexAttribArray(2); // color
	// stride is 6: pos(2) + col(4)
	// (x, y, r, g, b, a)
	int stride = 7;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof (GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride * sizeof (GLfloat), BUFFER_OFFSET(12)); // col

	//glDisable(GL_LIGHTING);
	//glDrawElements(GL_TRIANGLES, ellipseDetail * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Disable VAO
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	ellipsePrims.clear();
	ellipseInds.clear();
}

bool ProtoBaseApp::createShadowMap(){

	//set up shadow texture object
	glGenTextures(1, &shadowTextureID);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, shadowTextureID);
	GLfloat border[] = { 1.0f, .0f, .0f, .0f };
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	// set up FBO
	glGenFramebuffers(1, &shadowBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowBufferID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTextureID, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
		// unbind fbo
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}
	else {
		// unbind fbo
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	return false;
}

void ProtoBaseApp::_initUniforms(ProtoShader* shader_ptr){
	//shader = _shader;
	//bind shaders
	//shader_ptr->bind();

	// get shader location for default 8 lights
	for (int i = 0; i < 8; ++i){
		std::string pos = "lights[" + std::to_string(i) + "].position";
		lights_U[i].position = glGetUniformLocation(shader_ptr->getID(), pos.c_str());

		std::string inten = "lights[" + std::to_string(i) + "].intensity";
		lights_U[i].intensity = glGetUniformLocation(shader_ptr->getID(), inten.c_str());

		// eventually get rid of these probably
		std::string diff = "lights[" + std::to_string(i) + "].diffuse";
		lights_U[i].diffuse = glGetUniformLocation(shader_ptr->getID(), diff.c_str());

		std::string amb = "lights[" + std::to_string(i) + "].ambient";
		lights_U[i].ambient = glGetUniformLocation(shader_ptr->getID(), amb.c_str());

		std::string spec = "lights[" + std::to_string(i) + "].specular";
		lights_U[i].specular = glGetUniformLocation(shader_ptr->getID(), spec.c_str());
	}

	// global ambient light
	globalAmbient_U = glGetUniformLocation(shader_ptr->getID(), "globalAmbientLight");

	// transformation matrices
	M_U = glGetUniformLocation(shader_ptr->getID(), "modelMatrix");
	MV_U = glGetUniformLocation(shader_ptr->getID(), "modelViewMatrix");
	MVP_U = glGetUniformLocation(shader_ptr->getID(), "modelViewProjectionMatrix");
	N_U = glGetUniformLocation(shader_ptr->getID(), "normalMatrix");

	// shadow map and light transformation matrix for shadowmapping
	shadowMap_U = glGetUniformLocation(shader_ptr->getID(), "shadowMap");
	L_MVBP_U = glGetUniformLocation(shader_ptr->getID(), "shadowModelViewBiasProjectionMatrix");

	// pass shadow map texture to shader
	shaderPassFlag_U = glGetUniformLocation(shader_ptr->getID(), "shadowPassFlag");
	glUniform1i(shaderPassFlag_U, 1); // controls render pass in shader
	glUniform1i(shadowMap_U, 5);

	// enable/disable lighting factors for 2D rendering
	// default is all on
	lightRenderingFactors_U = glGetUniformLocation(shader_ptr->getID(), "lightRenderingFactors");
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);


	//shader_ptr->unbind();
}

void ProtoBaseApp::_run(const Vec2f& mousePos/*, int mouseBtn, int key*/){

	// reset state
	fillColor = Col4f(1, 1, 1, 1); // white fill
	strokeColor = Col4f(0, 0, 0, 1); // black stroke


	mouseX = mousePos.x;
	mouseY = mousePos.y;
	// mouse is moving/dragging
	if (Vec2(mouseX, mouseY) - Vec2(mouseLastFrameX, mouseLastFrameY) != Vec2(0, 0)){
		if (isMousePressed){

			// arcball
			//if (isArcballOn){
			arcballRotY = mouseX - mouseXIn + arcballRotYLast;
			arcballRotX = mouseY - mouseYIn + arcballRotXLast;
			//}

			mouseDragged();
		}
		else {
			mouseMoved();
		}
	}

	//global ambient
	glUniform3fv(globalAmbient_U, 1, &globalAmbient.r);

	// update all 8 lights in shaders
	for (int i = 0; i < 8; ++i){
		glUniform3fv(lights_U[i].position, 1, &lights[i].getPosition().x);
		glUniform3fv(lights_U[i].intensity, 1, &lights[i].getIntensity().x);
		glUniform4fv(lights_U[i].diffuse, 1, &lights[i].getDiffuse().r);
		glUniform4fv(lights_U[i].ambient, 1, &lights[i].getAmbient().r);
		glUniform4fv(lights_U[i].specular, 1, &lights[i].getSpecular().r);
	}

	// I thought I needed this to reset matrix each frame?
	M = glm::mat4(1.0f);
	// was 18
	V = glm::lookAt(glm::vec3(0.0, 0.0, 500.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	//M = T * R * S;
	MV = V * M;
	MVP = P * MV;
	//trace("light pos =", light0.getPosition());
	// update shadow map texture matrix should light(s) changes position
	L_MV = glm::lookAt(glm::vec3(light0.getPosition().x, light0.getPosition().y, light0.getPosition().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	L_MVBP = L_BP*L_MV;
	//glUniformMatrix4fv(L_MVBP_U, 1, GL_FALSE, &L_MVBP[0][0]);

	glm::mat4 shaderMat = L_MVBP*M; // new  // include mult by Model mat
	glUniformMatrix4fv(L_MVBP_U, 1, GL_FALSE, &shaderMat[0][0]);


	// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
	// update normals

	N = glm::transpose(glm::inverse(glm::mat3(MV)));
	glUniformMatrix4fv(M_U, 1, GL_FALSE, &M[0][0]);
	glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);

	// enable  /disable lighting effects ofr 2D rendering
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);


	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glViewport(0, 0, width, height);

	//if (isArcballOn){
	//push();
	//rotate(arcballRotX, 1, 0, 0);
	//rotate(arcballRotY, 0, 1, 0);
	//}

	run();
	push();
	display();
	pop();
	render();

	//ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 0.0);
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	//if (isArcballOn){
	//pop();
	//}


	//// if shadowing is enabled do double pass with shadow map framebuffer
	//if (areShadowsEnabled){
	//	//trace("shadows enabled");
	//	// bind shadow map framebuffer
	//	glBindFramebuffer(GL_FRAMEBUFFER, shadowBufferID);
	//	//clear depth buffer
	//	glClear(GL_DEPTH_BUFFER_BIT);
	//	//set viewport to the shadow map view size
	//	//glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
	//	glViewport(0, 0, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);
	//	//glViewport(-2 * SHADOWMAP_WIDTH, -2 * SHADOWMAP_WIDTH, 6 * SHADOWMAP_WIDTH, 6 * SHADOWMAP_HEIGHT);

	//	// enable front face culling for shadowing
	//	glCullFace(GL_FRONT);

	//	// enables shadow blending in fragment shader
	//	glUniform1i(shaderPassFlag_U, 1); // controls render pass in shader
	//	
	//	// render shadow in firdt pass
	//	run();
	//	
	//	// reset default framebuffer
	//	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//	// not sure what this does
	//	glDrawBuffer(GL_BACK_LEFT);
	//	
	//	// reset default view
	//	////glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
	//	glViewport(0, 0, getWidth(), getHeight());
	//	//glViewport(-2 * width, -2 * height, 6 * width, 6 * height);

	//	// rest backface culling
	//	glCullFace(GL_BACK);
	//	//glDisable(GL_CULL_FACE);

	//	// disable shadoing blending in fragment shader
	//	glUniform1i(shaderPassFlag_U, 0); // controls render pass in shader
	//	//glUniform1i(shadowMap_U, 0);

	//	// render scene in second pass
	//	run();
	//}
	//else {
	//	//trace("shadows not enabled");
	//	//glClear(GL_DEPTH_BUFFER_BIT); 
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glUniform1i(shaderPassFlag_U, 0); // controls render pass in shader
	//	
	//	// no shadowing use default run
	//	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//	// not sure what this does
	//	//glDrawBuffer(GL_BACK_LEFT);

	//	// reset default view
	//	////glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
	//	glViewport(0, 0, getWidth(), getHeight());
	//	//glViewport(-2 * width, -2 * height, 6 * width, 6 * height);

	//	// rest backface culling
	//	glCullFace(GL_BACK);
	//	//glDisable(GL_CULL_FACE);

	//	// disable shadoing blending in fragment shader
	//	//glUniform1i(shaderPassFlag_U, 0); // controls render pass in shader
	//	//glUniform1i(shadowMap_U, 0);

	//	// render scene in second pass
	//	run();
	//}
	mouseLastFrameX = mouseX;
	mouseLastFrameY = mouseY;
}

void ProtoBaseApp::render(int x, int y, int scaleFactor) {
	// if shadowing is enabled do double pass with shadow map framebuffer
	if (areShadowsEnabled){
		//glEnable(GL_CULL_FACE);
		//trace("shadows enabled");
		// bind shadow map framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, shadowBufferID);
		//clear depth buffer
		glClear(GL_DEPTH_BUFFER_BIT);
		//set viewport to the shadow map view size
		//glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
		//glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
		glViewport(0, 0, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);
		//glViewport(x*SHADOWMAP_WIDTH, y*SHADOWMAP_HEIGHT, scaleFactor * SHADOWMAP_WIDTH, scaleFactor *  SHADOWMAP_HEIGHT);
		//glViewport(-2 * SHADOWMAP_WIDTH, -2 * SHADOWMAP_WIDTH, 6 * SHADOWMAP_WIDTH, 6 * SHADOWMAP_HEIGHT);

		// enable front face culling for shadowing
		glCullFace(GL_FRONT);

		// enables shadow blending in fragment shader
		glUniform1i(shaderPassFlag_U, 1); // controls render pass in shader

		// render shadow in firdt pass
		display();

		// rest backface culling
		//glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		//glDisable(GL_CULL_FACE);

		// reset default framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// not sure what this does
		glDrawBuffer(GL_BACK_LEFT);

		// reset default view
		////glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
		glViewport(x*width, y*height, scaleFactor * width, scaleFactor * height);



		// disable shadowing blending in fragment shader
		glUniform1i(shaderPassFlag_U, 0); // controls render pass in shader
		//glUniform1i(shadowMap_U, 0);

		// render scene in second pass
		display();
	}
	else {
		//trace("shadows not enabled");
		//glClear(GL_DEPTH_BUFFER_BIT); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUniform1i(shaderPassFlag_U, 0); // controls render pass in shader

		// no shadowing use default run
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// not sure what this does
		//glDrawBuffer(GL_BACK_LEFT);

		// reset default view
		////glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
		//glViewport(0, 0, getWidth(), getHeight());
		glViewport(x*width, y*height, scaleFactor * width, scaleFactor * height);
		//glViewport(-2 * width, -2 * height, 6 * width, 6 * height);

		// rest backface culling
		glCullFace(GL_BACK);
		//

		// disable shadoing blending in fragment shader
		glUniform1i(shaderPassFlag_U, 0); // controls render pass in shader
		//glUniform1i(shadowMap_U, 0);

		// render scene in single pass
		display();
	}

}

// event behavior
void ProtoBaseApp::setMouseButton(int mouseAction, int mouseButton, int mouseMods){
	if (mouseAction == 1){
		isMousePressed = true;

		// arcball
		mouseXIn = mouseX;
		mouseYIn = mouseY;

		mousePressed();
	}
	else if (mouseAction == 0){
		isMousePressed = false;

		// arcball
		arcballRotXLast = arcballRotX;
		arcballRotYLast = arcballRotY;


		mouseReleased();
	}
	/*this->mouseButton = mouseButton;
	trace("LEFT mouse button pressed");*/
}

//arcball
void ProtoBaseApp::arcballBegin(){
	//isArcballOn = true;
	push();
	rotate(arcballRotX, 1, 0, 0);
	rotate(arcballRotY, 0, 1, 0);
}

void ProtoBaseApp::arcballEnd(){
	//isArcballOn = false;
	pop();
}

// gen funcs
// overloaded background
void ProtoBaseApp::setBackground(float r, float g, float b){
	bgColor.setR(r);
	bgColor.setG(g);
	bgColor.setB(b);
	glClearColor(r, g, b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void ProtoBaseApp::setBackground(float c){
	setBackground(c, c, c);
}

void ProtoBaseApp::setBackground(const Col3f& col){
	setBackground(col.getR(), col.getG(), col.getB());
}

void ProtoBaseApp::setBackground(const Col4f& col){
	setBackground(col.getR(), col.getG(), col.getB());
}

// END background

//LIGHTS
void ProtoBaseApp::lightsOn(){
	//	glEnable(GL_LIGHTING);

}
void ProtoBaseApp::lightsOff(){
	//	glDisable(GL_LIGHTING);
}
//END LIGHTS

// window details
void ProtoBaseApp::setWidth(int canvasWidth){
	this->canvasWidth = canvasWidth;
	width = canvasWidth;
}

void ProtoBaseApp::setHeight(int canvasHeight){
	this->canvasHeight = canvasHeight;
	height = canvasHeight;
}

void ProtoBaseApp::setSize(const Dim2i& canvasSize){
	this->canvasSize = canvasSize;
}


int ProtoBaseApp::getWidth() const{
	return width;
}

int ProtoBaseApp::getHeight() const{
	return height;
}

Dim2i ProtoBaseApp::getSize()const {
	return canvasSize;
}

// Load Image
void ProtoBaseApp::loadImage(std::string imageName){
	// START for relative resource loading
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		std::cout << "error loading from relative directory" << std::endl;
		//return errno;
	}
	// NOTE - workspace project relative instead of using default derivedData path in Library
	cCurrentPath[sizeof(cCurrentPath)-1] = '\0'; /* not really required */
	std::string cp = cCurrentPath; //cast char[] to string
	std::cout << "current path = " << cp << std::endl;
	std::string pathExtension = "/resources/imgs";
	std::string imgName = "/" + imageName;
	std::string url = cp + pathExtension + imgName;
	//    sf::Texture texture;
	//    if (!texture.loadFromFile(url))
	//    {
	//        // error...
	//    }
}

// END window details

// Note: need to update to GLSL
//void ProtoBaseApp::printMatrix(){
//
//	std::cout << M[0][0] << " | " << matrix[4] << " | " << matrix[8] << " | " << matrix[12] << "\n";
//	std::cout << matrix[1] << " | " << matrix[5] << " | " << matrix[9] << " | " << matrix[13] << "\n";
//	std::cout << matrix[2] << " | " << matrix[6] << " | " << matrix[10] << " | " << matrix[14] << "\n";
//	std::cout << matrix[3] << " | " << matrix[7] << " | " << matrix[11] << " | " << matrix[15] << std::endl;
//}

// 2D api 




void ProtoBaseApp::GLSLInfo(ProtoShader* shader){
	// START get all uniform shaders
	GLint nUniforms, maxLen;
	glGetProgramiv(shader->getID(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv(shader->getID(), GL_ACTIVE_UNIFORMS, &nUniforms);

	GLchar* name = (GLchar*)malloc(maxLen);

	GLint size, location;
	GLsizei written;
	GLenum type;
	printf("\n Location | Name\n");
	printf("--------------------------------------------------\n");
	for (int i = 0; i < nUniforms; ++i){
		glGetActiveUniform(shader->getID(), i, maxLen, &written, &size, &type, name);
		location = glGetUniformLocation(shader->getID(), name);
		printf(" %-8d | %s\n", location, name);
	}
	free(name);
	// END get all uniform shaders

	// get info about renderers
	trace("renderer =", glGetString(GL_RENDERER));
	trace("vendor =", glGetString(GL_VENDOR));
	trace(" version =", glGetString(GL_VERSION));
	trace("glslVersion =", glGetString(GL_SHADING_LANGUAGE_VERSION));

	trace("vertexPosition Location =", glGetAttribLocation(shader->getID(), "vertexPosition"));
	trace("vertexNormal Location =", glGetAttribLocation(shader->getID(), "vertexNormal"));
	trace("vertexColor Location =", glGetAttribLocation(shader->getID(), "vertexColor"));
	trace("vertexTexture Location =", glGetAttribLocation(shader->getID(), "vertexTexture"));
}


/***********BEGIN************
2D Automatic Procedural API
***************************/

// flag  enable/disable 2D lighting
void ProtoBaseApp::enable2DRendering() {
	ltRenderingFactors = Vec4f(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);
}
void ProtoBaseApp::disable2DRendering(){
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 0.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);
}


// Styles API
void ProtoBaseApp::fill(const Col4f& col) {
	fillColor = col;
	ltRenderingFactors = Vec4f(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);
}
void ProtoBaseApp::fill(float gray) {
	fillColor = Col4f(gray, gray, gray, 1);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);
}
void ProtoBaseApp::fill(float gray, float a) {
	fillColor = Col4f(gray, gray, gray, a);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);
}
void ProtoBaseApp::fill(float r, float g, float b) {
	fillColor = Col4f(r, g, b, 1);
	ltRenderingFactors = Vec4f(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);
}
void ProtoBaseApp::fill(float r, float g, float b, float a) {
	fillColor = Col4f(r, g, b, a);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);
}
void ProtoBaseApp::noFill() {
	fillColor = Col4f(0, 0, 0, 0);

}
// begin STROKE
void ProtoBaseApp::stroke(const Col4f& col) {
	strokeColor = col;
}
void ProtoBaseApp::stroke(float gray) {
	strokeColor = Col4f(gray, gray, gray, 1);
}
void ProtoBaseApp::stroke(float gray, float a) {
	strokeColor = Col4f(gray, gray, gray, a);
}
void ProtoBaseApp::stroke(float r, float g, float b) {
	strokeColor = Col4f(r, g, b, 1);
}
void ProtoBaseApp::stroke(float r, float g, float b, float a) {
	strokeColor = Col4f(r, g, b, a);
}
void ProtoBaseApp::noStroke() {
	strokeColor = Col4f(0, 0, 0, 0);
}
void ProtoBaseApp::strokeWeight() {
}

//PRIMITIVES
void ProtoBaseApp::rect(float x, float y, float w, float h, Registration reg){

	float _x = 0, _y = 0; 
	
	switch (reg){
	case CENTER:
		_x = x - w / 2;
		_y = y + h / 2;
		break;
	case CORNER:
		_x = x;
		_y = y;
		break;
	case CORNER_TR:
		_x = x - w;
		_y = y;
		break;
	case CORNER_BR:
		_x = x - w;
		_y = y + h;
		break;
	case CORNER_BL:
		_x = x;
		_y = y + h;
		break;
	case RANDOM:
		// to do
		break;

	}

	rectPrims[0] = _x;
	rectPrims[1] = _y;
	//rectPrims[2] = 0;
	rectPrims[3] = fillColor.r;
	rectPrims[4] = fillColor.g;
	rectPrims[5] = fillColor.b;
	rectPrims[6] = fillColor.a;
	rectPrims[7] = _x;
	rectPrims[8] = _y - h;
	//rectPrims[9] = 0;
	rectPrims[10] = fillColor.r;
	rectPrims[11] = fillColor.g;
	rectPrims[12] = fillColor.b;
	rectPrims[13] = fillColor.a;
	rectPrims[14] = _x + w;
	rectPrims[15] = _y - h;
	//rectPrims[16] = 0;
	rectPrims[17] = fillColor.r;
	rectPrims[18] = fillColor.g;
	rectPrims[19] = fillColor.b;
	rectPrims[20] = fillColor.a;
	rectPrims[21] = _x + w;
	rectPrims[22] = _y;
	//rectPrims[23] = 0;
	rectPrims[24] = fillColor.r;
	rectPrims[25] = fillColor.g;
	rectPrims[26] = fillColor.b;
	rectPrims[27] = fillColor.a;


	glBindBuffer(GL_ARRAY_BUFFER, vboRectID); 
	int vertsDataSize = sizeof (GLfloat)* 28;
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &rectPrims[0]); // upload the data
	
	enable2DRendering();
	glBindVertexArray(vaoRectID);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	disable2DRendering();
	
	// Disable VAO
	glBindVertexArray(0); 
	
}

void ProtoBaseApp::rect(const Vec2& pt0, const Vec2& pt1, Registration reg) {
	rect(pt0.x, pt0.y, pt1.x - pt0.x, pt1.y - pt0.y, reg);
}
void ProtoBaseApp::rect(float radius1, float radius2, Registration reg) {
	rect(0, 0, radius1, radius2, reg);
}
void ProtoBaseApp::ellipse(float x, float y, float w, float h, Registration reg) {
float _x = 0, _y = 0;

	/* CENTER,
	CORNER, // assumed top left
	CORNER_TR,
	CORNER_BR,
	CORNER_BL,
	RANDOM
	*/

	switch (reg){
	case CENTER:
		_x = x;
		_y = y;
		break;
	case CORNER: // TL
		_x = x + w / 2;
		_y = y - h / 2;
		break;
	case CORNER_TR:
		_x = x - w / 2;
		_y = y - h / 2;
		break;
	case CORNER_BR:
		_x = x - w / 2;
		_y = y + h / 2;
		break;
	case CORNER_BL:
		_x = x + w / 2;
		_y = y + h / 2;
		break;
	case RANDOM:
		// to do
		break;

	}
	ellipsePrims.push_back(_x);
	ellipsePrims.push_back(_y);
	ellipsePrims.push_back(0);
	ellipsePrims.push_back(fillColor.r);
	ellipsePrims.push_back(fillColor.g);
	ellipsePrims.push_back(fillColor.b);
	ellipsePrims.push_back(fillColor.a);

	float theta = 0.0;
	for (int i = 7; i <= ellipseDetail*7; i += 7){
		ellipsePrims.push_back(_x + cos(theta)*w / 2.0);
		ellipsePrims.push_back(_y + sin(theta)*h / 2.0);
		ellipsePrims.push_back(0);
		ellipsePrims.push_back(fillColor.r);
		ellipsePrims.push_back(fillColor.g);
		ellipsePrims.push_back(fillColor.b);
		ellipsePrims.push_back(fillColor.a);
		theta += TWO_PI / ellipseDetail;
	}
	for (int i = 0, j = 1; i < ellipseDetail*3; ++j, i+=3){
		ellipseInds.push_back(j);
		ellipseInds.push_back(0);
		if (i < ellipseDetail*3 - 3){
			ellipseInds.push_back(j + 1);
		}
		else {
			ellipseInds.push_back(1);
		}
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, vboEllipseID);
	int vertsDataSize = sizeof (GLfloat)* ellipsePrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &ellipsePrims[0]); // upload the data

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboEllipseID);
	int indsDataSize = sizeof (int)* ellipseInds.size();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &ellipseInds[0]); // upload the data

	enable2DRendering();
	glBindVertexArray(vaoEllipseID);
	glDrawElements(GL_TRIANGLES, ellipseInds.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	disable2DRendering();

	// Disable VAO
	glBindVertexArray(0);

	// reenable 3D lighting
	disable2DRendering();

	// clean up vectors between each frame
	ellipsePrims.clear();
	ellipseInds.clear();
}
void ProtoBaseApp::ellipse(float r, Registration reg) {
	ellipse(0, 0, r, r, reg);
}
void ProtoBaseApp::ellipse(float r0, float r1, Registration reg) {
	ellipse(0, 0, r0, r1, reg);
}
void ProtoBaseApp::ellipse(float x, float y, float r, Registration reg) {
	ellipse(x, y, r, r, reg);
}
void ProtoBaseApp::triangle(const Vec2& pt0, const Vec2& pt1, const Vec2& pt2) {
}
void ProtoBaseApp::triangle(float x0, float y0, float x1, float y1, float x2, float y2) {
}
void ProtoBaseApp::poly(int sides, float radius) {
}
void ProtoBaseApp::poly(int sides, float radius1, float radius2) {
}
void ProtoBaseApp::star(int sides, float innerRadius, float outerRadius) {
}
void ProtoBaseApp::star(int sides, const Vec2& radiusAndRatio) {
}

// PATH
void ProtoBaseApp::beginPath() {
	isPathRecording = true;
}
void ProtoBaseApp::endPath(bool isClosed) {
	isPathRecording = false;

	// now draw geometry
}
void ProtoBaseApp::vertex(const Vec2f& vec) {
	vertex(vec.x, vec.y, 0);
}
void ProtoBaseApp::vertex(const Vec3f& vec) {
	vertex(vec.x, vec.y, vec.z);
}
void ProtoBaseApp::vertex(float x, float y) {
	vertex(x, y, 0);
}
void ProtoBaseApp::vertex(float x, float y, float z) {
	if (isPathRecording){
		ellipsePrims.push_back(x);
		ellipsePrims.push_back(y);
		ellipsePrims.push_back(z);
	}
	else {
		trace("Path Recording Failure: You must precede vertex() calls with beginPath()");
	}
}
/****END 2D API****/



//void ProtoBaseApp::render(int scaleFactor){}; // "should be" overridden in derived classes



void ProtoBaseApp::export(std::vector<Tup4v> vs, Format type){
#if defined (_WIN32) || defined(_WIN64)
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
#else // os x uses localtime instead of localtime_s
	time_t now = time(0);
	tm* ltm = localtime(&now);
#endif

	//trace("geomData.size() =", faces.size());

	std::stringstream stream;
	stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;

	std::string url = ProtoUtility::getPathToOutput();
	std::string directory = url + "data" + "_" + stream.str();
	CreateDirectory(directory.c_str(), 0);

	std::ofstream myfile;
	myfile.open(directory + "/geomdata" + stream.str() + ".stl");

	myfile << "solid protobyte\n";
	for (int i = 0; i < vs.size() - 4; i++) {
		//trace("allFaces.at(i).v0_p->pos =", allFaces.at(i).getVert0_ptr()->pos);
		myfile << "\tfacet normal " <<
			vs.at(i).elem0.x << " " << vs.at(i).elem0.y << " " << vs.at(i).elem0.z << "\n" <<
			"\t\touter loop\n" <<
			"\t\t\tvertex " << vs.at(i).elem1.x << " " << vs.at(i).elem1.y << " " << vs.at(i).elem1.z << "\n" <<
			"\t\t\tvertex " << vs.at(i).elem2.x << " " << vs.at(i).elem2.y << " " << vs.at(i).elem2.z << "\n" <<
			"\t\t\tvertex " << vs.at(i).elem3.x << " " << vs.at(i).elem3.y << " " << vs.at(i).elem3.z << "\n" <<
			"\t\tendloop\n" <<
			"\tendfacet\n";
	}
	myfile << "endsolid protobyte\n";

	myfile.close();
	std::cout << "stl file successfully written" << std::endl;
}

//template<typename First, typename ... Rest>
//void ProtoBaseApp::export(Format type, First first, Rest ... rest) {
//#if defined (_WIN32) || defined(_WIN64)
//	time_t now = time(0);
//	tm ltm;
//	localtime_s(&ltm, &now);
//#else // os x uses localtime instead of localtime_s
//	time_t now = time(0);
//	tm* ltm = localtime(&now);
//#endif
//
//	//trace("geomData.size() =", faces.size());
//
//	std::stringstream stream;
//	stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
//
//	std::string url = ProtoUtility::getPathToOutput();
//	std::string directory = url + "data" + "_" + stream.str();
//	CreateDirectory(directory.c_str(), 0);
//
//	std::ofstream myfile;
//	myfile.open(directory + "/geomdata" + stream.str() + ".stl");
//
//	myfile << "solid protobyte\n";
//	for (int i = 0; i < vs.size() - 4; i++) {
//		//trace("allFaces.at(i).v0_p->pos =", allFaces.at(i).getVert0_ptr()->pos);
//		myfile << "\tfacet normal " <<
//			vs.at(i).elem0.x << " " << vs.at(i).elem0.y << " " << vs.at(i).elem0.z << "\n" <<
//			"\t\touter loop\n" <<
//			"\t\t\tvertex " << vs.at(i).elem1.x << " " << vs.at(i).elem1.y << " " << vs.at(i).elem1.z << "\n" <<
//			"\t\t\tvertex " << vs.at(i).elem2.x << " " << vs.at(i).elem2.y << " " << vs.at(i).elem2.z << "\n" <<
//			"\t\t\tvertex " << vs.at(i).elem3.x << " " << vs.at(i).elem3.y << " " << vs.at(i).elem3.z << "\n" <<
//			"\t\tendloop\n" <<
//			"\tendfacet\n";
//	}
//	myfile << "endsolid protobyte\n";
//
//	myfile.close();
//	std::cout << "stl file successfully written" << std::endl;
//
//}

void ProtoBaseApp::save(std::string name, int scaleFactor){
	if (getFrameCount() < 1){

		//ProtoBaseApp pba;
		//std::thread t(&ProtoBaseApp::threadSave, &pba, name, scaleFactor);
		//t.join();



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
		std::string directory = url + name + "_" + stream.str();
		CreateDirectory(directory.c_str(), 0);


		/*trace("width =", width);
		trace("height =", height);*/
		for (int i = 0; i < scaleFactor; ++i){
			for (int j = 0; j < scaleFactor; ++j){
				//trace("in drawToFrameBuffer");
				//glClearColor(0, 0, 0, 1.0f);
				//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				//From: http://stackoverflow.com/questions/12157646/how-to-render-offscreen-on-opengl

				//glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
				//if (i == 0) trace("scaleFactor =", scaleFactor);
				render(-i, -j, scaleFactor);
				//trace(" in loop, in save");
				/*glReadPixels(0, 0, WIDTH, HEIGHT, GL_BGR, GL_BYTE, pixels);
				FIBITMAP Image = FreeImage_ConvertFromRawBits(pixels, WIDTH, HEIGHT, 3WIDTH, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
				FreeImage_Save(FIF_BMP, Image, "test.bmp", 0)*/


				//after drawing
				std::vector<uint8_t> data(width * height * 3);
				glReadBuffer(GL_BACK);
				glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);

				//std::vector<std::uint8_t> data(width*height * 4);
				//glReadBuffer(GL_BACK);
				//glReadPixels(0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, &data[0]);



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
				FIBITMAP* image = FreeImage_ConvertFromRawBits(&data[0], width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
				// FreeImage_ConvertFromRawBits(pixels, WIDTH, HEIGHT, 3WIDTH, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);


				// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
				//std::stringstream stream;
#if defined (_WIN32) || defined(_WIN64)
				// stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
				// c++ 11 conversion form num to string
				//std::string url = "\\Users\\Ira\\Desktop\\ProtoJucnusEffusus01_stills\\" + name + "_" + std::to_string(i*scaleFactor+j) + ".jpg";

				// ensure no single digit nums, for easy sorting
				std::string imgNum;

				if (i*scaleFactor + j < 10){
					imgNum = "00" + std::to_string(i*scaleFactor + j);
				}
				else if (i*scaleFactor + j < 100){
					imgNum = "0" + std::to_string(i*scaleFactor + j);
				}
				else {
					imgNum = std::to_string(i*scaleFactor + j);
				}

				std::string tileURL = directory + "\\" + name + "_" + imgNum + ".jpg";
#else
				// stream << (ltm->tm_year + 1900) << "_" << (ltm->tm_mon + 1) << "_" << ltm->tm_mday << "_" << ltm->tm_hour << "_" << ltm->tm_min << "_" << ltm->tm_sec;
				// c++ 11 conversion form num to string
				std::string url = "/Users/33993405/Desktop/ProtoJucnusEffusus01_stills/" + namme + "_" + std::to_string(i*scaleFactor + j) + ".jpg";
#endif

				FreeImage_Save(FIF_JPEG, image, tileURL.c_str(), JPEG_QUALITYSUPERB);
				//trace("-i = ", -i, "-j =", -j);

				// Free resources
				FreeImage_Unload(image);


				// Return to onscreen rendering:
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			}
		}
		//trace("ProtoUtility::getPath() =", ProtoUtility::getPath());
		bool isOk = stitchTiles(directory, scaleFactor);
	}
}

//void ProtoBaseApp::threadSave(std::string name, int scaleFactor){
//	//mtx.lock();
//#if defined (_WIN32) || defined(_WIN64)
//	time_t now = time(0);
//	tm ltm;
//	localtime_s(&ltm, &now);
//#else // os x uses localtime instead of localtime_s
//	time_t now = time(0);
//	tm* ltm = localtime(&now);
//#endif
//
//	// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
//	std::stringstream stream;
//	stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
//
//
//
//	std::string url = ProtoUtility::getPathToOutput();
//	std::string directory = url + name + "_" + stream.str();
//	CreateDirectory(directory.c_str(), 0);
//
//
//	for (int i = 0; i < scaleFactor; ++i){
//		for (int j = 0; j < scaleFactor; ++j){
//			
//			//trace("in drawToFrameBuffer");
//			//glClearColor(0, 0, 0, 1.0f);
//			trace("width = ", width);
//			trace("height = ", height);
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//			//From: http://stackoverflow.com/questions/12157646/how-to-render-offscreen-on-opengl
//
//			glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
//			//this->render();
//			render();
//
//			//after drawing
//			std::vector<uint8_t> data(width * height * 3);
//			mtx.lock(); 
//			glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);
//			mtx.unlock();
//
//
//
//#if defined (_WIN32) || defined(_WIN64)
//			time_t now = time(0);
//			tm ltm;
//			localtime_s(&ltm, &now);
//#else // os x uses localtime instead of localtime_s
//			time_t now = time(0);
//			tm* ltm = localtime(&now);
//#endif
//
//
//			// FROM http://stackoverflow.com/questions/5844858/how-to-take-screenshot-in-opengl
//			// Convert to FreeImage format & save to file
//			FIBITMAP* image = FreeImage_ConvertFromRawBits(&data[0], width, height, 3 * width, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
//
//
//			// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
//			//std::stringstream stream;
//#if defined (_WIN32) || defined(_WIN64)
//			// stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
//			// c++ 11 conversion form num to string
//			//std::string url = "\\Users\\Ira\\Desktop\\ProtoJucnusEffusus01_stills\\" + name + "_" + std::to_string(i*scaleFactor+j) + ".jpg";
//
//			// ensure no single digit nums, for easy sorting
//			std::string imgNum;
//
//			if (i*scaleFactor + j < 10){
//				imgNum = "00" + std::to_string(i*scaleFactor + j);
//			}
//			else if (i*scaleFactor + j < 100){
//				imgNum = "0" + std::to_string(i*scaleFactor + j);
//			}
//			else {
//				imgNum = std::to_string(i*scaleFactor + j);
//			}
//
//			std::string tileURL = directory + "\\" + name + "_" + imgNum + ".jpg";
//#else
//			// stream << (ltm->tm_year + 1900) << "_" << (ltm->tm_mon + 1) << "_" << ltm->tm_mday << "_" << ltm->tm_hour << "_" << ltm->tm_min << "_" << ltm->tm_sec;
//			// c++ 11 conversion form num to string
//			std::string url = "/Users/33993405/Desktop/ProtoJucnusEffusus01_stills/" + namme + "_" + std::to_string(i*scaleFactor + j) + ".jpg";
//#endif
//
//			FreeImage_Save(FIF_JPEG, image, tileURL.c_str(), 0);
//
//			// Free resources
//			FreeImage_Unload(image);
//
//
//			// Return to onscreen rendering:
//			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
//			
//		}
//	}
//
//	//trace("ProtoUtility::getPath() =", ProtoUtility::getPath());
//	bool isOk = stitchTiles(directory, scaleFactor);
//
//	//mtx.unlock();
//}

bool ProtoBaseApp::stitchTiles(std::string url, int tiles){
	//trace(" url =", url);
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
	// 4. copy and paste tiles into composite image
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
			FreeImage_Paste(compositeImg, piece, width*i, (height*(tiles - 1)) - height*j, 255);


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

// matrix transformation functions, in style of GL 1.0
void ProtoBaseApp::translate(float tx, float ty, float tz){
	M = glm::translate(M, glm::vec3(tx, ty, tz));
	concat();
}
void ProtoBaseApp::translate(const Vec3f& tXYZ){
	M = glm::translate(M, glm::vec3(tXYZ.x, tXYZ.y, tXYZ.z));
	concat();
}
void ProtoBaseApp::rotate(float angle, float axisX, float axisY, float axisZ){
	M = glm::rotate(M, angle, glm::vec3(axisX, axisY, axisZ));
	concat();
}
void ProtoBaseApp::rotate(float angle, const Vec3f& rXYZ){
	M = glm::rotate(M, angle, glm::vec3(rXYZ.x, rXYZ.y, rXYZ.z));
	concat();
}
void ProtoBaseApp::scale(float s){
	M = glm::scale(M, glm::vec3(s, s, s));
	concat();
}
void ProtoBaseApp::scale(float sx, float sy, float sz){
	M = glm::scale(M, glm::vec3(sx, sy, sz));
	concat();
}
void ProtoBaseApp::scale(const Vec3f& sXYZ){
	M = glm::scale(M, glm::vec3(sXYZ.x, sXYZ.y, sXYZ.z));
	concat();
}

// concatenate MV, N, and MVP matrices and update values on GPU
void ProtoBaseApp::concat(){
	push();
	MV = V * M;
	N = glm::transpose(glm::inverse(glm::mat3(MV)));
	MVP = P * MV;
	// update in shader
	glUniformMatrix4fv(M_U, 1, GL_FALSE, &M[0][0]);
	glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);

	glm::vec3 ltPos = glm::vec3(light0.getPosition().x, light0.getPosition().y, light0.getPosition().z);

	L_MV = glm::lookAt(ltPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	L_MVBP = L_BP*L_MV;
	//glUniformMatrix4fv(L_MVBP_U, 1, GL_FALSE, &L_MVBP[0][0]);

	glm::mat4 shaderMat = L_MVBP*M; // new 
	glUniformMatrix4fv(L_MVBP_U, 1, GL_FALSE, &shaderMat[0][0]);
	pop();
}

// implements transform matrix stack
void ProtoBaseApp::push(){
	// save current transformation matrix to stack

	matrixStack.push(M);

}

// reset transformation matrix with stored matrix on stack
void ProtoBaseApp::pop(){
	// reset current transformation matrix with matrix on top of stack
	M = matrixStack.top();

	// remove matrix on top of stack
	matrixStack.pop();
}




// EVENTS
void ProtoBaseApp::keyPressed(){}
void ProtoBaseApp::mousePressed(){}
void ProtoBaseApp::mouseRightPressed(){}
void ProtoBaseApp::mouseReleased(){}
void ProtoBaseApp::mouseRightReleased(){}
void ProtoBaseApp::mouseMoved(){}
void ProtoBaseApp::mouseDragged(){}

// window events
void ProtoBaseApp::onResized(){}
void ProtoBaseApp::onClosed(){}




