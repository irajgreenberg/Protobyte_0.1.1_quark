/*!  \brief  ProtoJuncusEffusus02.h: Single wrapped starnd study
 ProtoJuncusEffusus02.h
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

#include "ProtoJuncusEffusus02.h"
static int id = 0, ring = 0;
static float freq = 0.0f, force = 0.0;

ProtoJuncusEffusus02::ProtoJuncusEffusus02(){
}
//	
//
ProtoJuncusEffusus02::ProtoJuncusEffusus02(const ProtoOSC& listener) :
ProtoBaseApp(listener){
}

void ProtoJuncusEffusus02::init() {

	setBackground(0);
	//glClearColor(1, .985f, .985f, 1);
	glClearColor(1, .8, .8, 1);
	globalAmbient = ProtoLight(Col4f(.25f, .19f, .27f, 1)); // slight violet color

	// light0
	light0.setPosition(Vec3f(0, -.2, 1));
	light0.setDiffuse(Col4f(1, 1, 1, 1.0f));
	light0.setAmbient(Col4f(.4, .4, .4, 1.0));
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

	Dim2f arrayDim(4.5, 20.5);
	int rows = 4;
	int columns = 2;
	float rowH = arrayDim.h / (rows - 1);
	float colW = arrayDim.w / (columns - 1);
	tubuleCount = rows*columns;

	// Note: counters int r, int c
	for (int r = 0; r < rows; ++r){
		for (int c = 0; c < columns; ++c){
			int ind = r*columns + c;
			juncs.push_back(ProtoJuncusEffusus(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(1, 1, 1), Col4f(1, 1, 1, 1), "pink_folds.jpg", "white5.jpg"));

			// l-r and f-b
			if (columns == 1){
				juncs.at(ind).setPosition(Vec3f(colW*c, 0, -rowH*r));
			}
			else {
				juncs.at(ind).setPosition(Vec3f(-arrayDim.w / 2.0f + colW*c, 0, -rowH*r));
			}
		}
	}



	ground = GroundPlane(Vec3f(0, 0/*tubules.at(0).getPosition().y*/, 0), Vec3f(), Dim2f(170, 13490), Col4f(1, 1, 1, 1), 1, 1, "white_tile.jpg", .02f);
	//ground = GroundPlane(Vec3f(0, 0/*tubules.at(0).getPosition().y*/, 0), Vec3f(), Dim2f(170, 60), Col4f(.5, .3, .4, 1), 1, 1);
	ground.setTextureScale(.2f);
	ground.textureOn();


	//shader = ProtoShader("shadowMap.vert", "shadowMap.frag");
	shader = ProtoShader("shader1.vert", "shader1.frag");

	// START standard transformation matrices: ModelView / Projection / Normal
	M = glm::mat4(1.0f); // set to identity
	V = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	MV = V * M;
	N = glm::transpose(glm::inverse(glm::mat3(MV)));

	// projection matrix and MVP Matrix
	float viewAngle = 65.0f;
	float aspect = width / height;
	float nearDist = .1f;
	float farDist = 2000.0f;

	P = glm::perspective(viewAngle, aspect, nearDist, farDist);
	MVP = P * MV;
	// END Model / View / Projection data

	// tranformation matricies
	T = glm::mat4(1.0f);
	R = glm::mat4(1.0f);
	S = glm::mat4(1.0f);

	/**************************************
	Start FrameBuffer Object for Shadow Map
	**************************************/
	initUniforms();
	// END

	/**************************************
	Start FrameBuffer Object for Shadow Map
	**************************************/
	initShadowMap();
	// END

	//GLSLInfo(&shadowMapShader);
	//GLSLInfo(&shader);


}



void ProtoJuncusEffusus02::initUniforms(){
	// lighting
	shader.bind();
	lightPos0_U = glGetUniformLocation(shader.getID(), "light0Position");
	lightDiffuse0_U = glGetUniformLocation(shader.getID(), "light0Diffuse");
	lightAmbient0_U = glGetUniformLocation(shader.getID(), "light0Ambient");
	lightSpecular0_U = glGetUniformLocation(shader.getID(), "light0Specular");

	//matrices
	MV_U = glGetUniformLocation(shader.getID(), "modelViewMatrix");
	MVP_U = glGetUniformLocation(shader.getID(), "modelViewProjectionMatrix");
	N_U = glGetUniformLocation(shader.getID(), "normalMatrix");

	// shadow map
	shadowMapTex = glGetUniformLocation(shader.getID(), "shaderMapTexture");
	L_MVP_U = glGetUniformLocation(shader.getID(), "lightModelViewProjectionMatrix");

	//shader.unbind();
}

void ProtoJuncusEffusus02::run() {
	//trace("id =", id);
	//trace("ring =", ring);
	//trace("freq =", freq);
	//trace("force =", force);

	setBackground(0);
	//trace(data.elem0, ",", data.elem1, ",", data.elem2, ",", data.elem3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glViewport(0, 0, width, height);

	//shader.bind();
	//trace(test);
	// Lighting 
	glUniform3fv(lightPos0_U, 1, &light0.getPosition().x);
	glUniform4fv(lightDiffuse0_U, 1, &light0.getDiffuse().r);
	glUniform4fv(lightAmbient0_U, 1, &light0.getAmbient().r);
	glUniform4fv(lightSpecular0_U, 1, &light0.getSpecular().r);


	// save high resolution rendering
	static int frameCounter = 0;
	if (frameCounter++ == 1){
		// currently only works with max 999 tiles
		//save("juncs", 4);
	}

	render();

}

// don't really need this
void ProtoJuncusEffusus02::setShadowMapTransform(){
	// calulate matrices from light perspective
	L_V = glm::lookAt(glm::vec3(light0.getPosition().x, light0.getPosition().y, light0.getPosition().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	L_P = glm::perspective(50.0f, 1.0f, 1.0f, 25.0f); // where are these nums from???
	L_B = glm::scale(glm::translate(glm::mat4(1), glm::vec3(0.5, 0.5, 0.5)), glm::vec3(0.5, 0.5, 0.5));
	L_BP = L_B*L_P;
	L_MVP = L_BP*L_MV;

	glUniformMatrix4fv(shadowMap_U, 1, GL_FALSE, &L_MVP[0][0]);
}

void ProtoJuncusEffusus02::render(int scaleFactor){
	//setShadowMapTransform();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//  02. draw to regular buffer
	for (int i = 0; i < juncs.size(); ++i){
		// 1 Draw Ground
		R = glm::mat4(1.0);
		T = glm::mat4(1.0);
		S = glm::mat4(1.0f);
		T = glm::translate(glm::mat4(1.0f), glm::vec3(0, -3, 0));

		V = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		M = T * R * S;
		MV = V * M;
		MVP = P * MV;

		// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
		// update normals
		N = glm::transpose(glm::inverse(glm::mat3(MV)));

		glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);

		//ground.display();

		// 2 Draw Tendrils
		S = glm::mat4(1.0);
		R = glm::mat4(1.0);
		T = glm::mat4(1.0);

		S = glm::mat4(1.0f);
		//R = glm::rotate(glm::mat4(1.0f), float(frameCount*.06), glm::vec3(0, 1, 0));
		T = glm::translate(glm::mat4(1.0f), glm::vec3(juncs.at(i).getPosition().x, juncs.at(i).getPosition().y, juncs.at(i).getPosition().z - .75f));

		V = glm::lookAt(glm::vec3(0.0, .5, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		M = T * R * S;
		MV = V * M;
		MVP = P * MV;

		// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
		// update normals

		N = glm::transpose(glm::inverse(glm::mat3(MV)));
		glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);
		
		switch (id){
		case 1:
			juncs.at(0).breath(ring, freq, force);
			juncs.at(5).breath(ring, freq, -force);
			break;
		case 2:
			juncs.at(1).breath(ring, freq, force);
			juncs.at(4).breath(ring, freq, -force);
			break;
		case 3:
			juncs.at(2).breath(ring, freq, force);
			juncs.at(7).breath(ring, freq, -force);
			break;
		case 4:
			juncs.at(3).breath(ring, freq, force);
			juncs.at(6).breath(ring, freq, -force);
			break;
		//default:

		/*	for (int j = 0; j < juncs.size(); ++j){
				juncs.at(j).breath(0, 0, 0);
			}*/
		}
		static float ttt = 0;
		juncs.at(2).pulse(10, .4, abs(sin(ttt+=PI/18000.0)*2));
		juncs.at(i).display(SURFACE, SURFACE);
	}
}

bool ProtoJuncusEffusus02::initShadowMap(){
	// Depth texture for Frame Buffer. Slower than a depth buffer, but you can sample it later in your shader
	depthTextureID = 0;
	glGenTextures(1, &depthTextureID);
	glBindTexture(GL_TEXTURE_2D, depthTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTextureID);


	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	framebufferID = 0;
	glGenFramebuffers(1, &framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureID, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}


// osc stuff
void  ProtoJuncusEffusus02::ProcessMessage(const osc::ReceivedMessage& m,
	const IpEndpointName& remoteEndpoint)
{
	try{
		// example of parsing single messages. osc::OscPacketListener
		// handles the bundle traversal.
		if (strcmp(m.AddressPattern(), "/squeakData") == 0){
			// example #1 -- argument stream interface
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 a1;
			osc::int32 a2;
			float a3;
			float a4;
			args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;
			id = a1;
			ring = a2;
			freq = a3;
			force = a4;
		}
		else if (strcmp(m.AddressPattern(), "/jumpData") == 0){
			// example #1 -- argument stream interface
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 a1;
			osc::int32 a2;
			float a3;
			float a4;
			args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;

			//id = a1;
			//ring = a2;
			//freq = a3;
			//amp = a4;
		}
	}
	catch (osc::Exception& e){
		// any parsing errors such as unexpected argument types, or
		// missing arguments get thrown as exceptions.
		/*std::cout << "error while parsing message: "
		<< m.AddressPattern() << ": " << e.what() << "\n";*/
	}
}