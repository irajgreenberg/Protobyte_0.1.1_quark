/*!  \brief  ProtoJuncusEffusus05.h:
Form study 3 for Zhulong Sattellite Exhibition: 4/2014
Protobyte Library v02

Created by Ira on 3/26/14.
Copyright (c) 2014 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.
Some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#include "ProtoJuncusEffusus05.h"

void ProtoJuncusEffusus05::init() {

	setBackground(0);
	//glClearColor(1, .985f, .985f, 1);
	glClearColor(1, .88, .88, 1);
	globalAmbient = ProtoLight(Col4f(.25f, .19f, .27f, 1)); // slight violet color

	// light0
	light0.setPosition(Vec3f(0, 0, 1));
	light0.setDiffuse(Col4f(1, 1, 1, 1.0f));
	light0.setAmbient(Col4f(.3, .3, .3, 1.0));
	light0.setSpecular(Col4f(1, 1, 1, 1.0));
	light0.on();

	shader = ProtoShader("shader1.vert", "shader1.frag");

	// START standard transformation matrices: ModelView / Projection / Normal
	M = glm::mat4(1.0f); // set to identity
	V = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	MV = V * M;
	N = glm::transpose(glm::inverse(glm::mat3(MV)));

	// projection matrix and MVP Matrix
	float viewAngle = 45.0f;
	
	//float aspect = getWidth()/getHeight();
	float aspect = float(width) / float(height);
	//float aspect = 800/1500;
	float nearDist = .1f;
	float farDist = 600.0f;

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
	//ProtoJuncusEffusus(const ProtoColor4f& col4, const std::string& textureImageURL1, const std::string& textureImageURL2, const std::vector<Vec3f>& cps) 

	juncsCount = 16;// 9;// 36;
	float ht = 2.25;
	int segs = 8;
	float step = ht / segs;
	float theta = 0;
	float radius = .107;
	float x, y, z;
	float chi = 0;
	
	// thanks to gamblin colors
	for (int i = 0; i < juncsCount; ++i){
		theta = TWO_PI / juncsCount * i;
		y = -ht / 2;
		std::vector <Vec3> cps;
		radius = .14;
		chi = 0;
		for (int j = 0; j < segs; ++j){
			z = (cos(theta + sin(chi)*random(j))*radius + random(-.08, .08)*j) * (random(1, 3.5) / (j + 1));
			y += step;
			x = (sin(theta + sin(chi)*random(j))*radius + random(-.08, .08)*j) * (random(1, 3.5) / (j + 1));
			cps.push_back(Vec3(x, y, z));
			theta += TWO_PI / segs;
			radius += .085;
			chi += PI / 2;
		}
		std::string skin;
		int dice = int(random(12));
		if (dice == 0)
		{
			skin = "white1.jpg";
		}
		else if (dice == 1){
			skin = "white2.jpg";
		}
		else if (dice == 2){
			skin = "pink2.jpg";
		}
		else if (dice == 3){
			skin = "white4.jpg";
		}
		else if (dice == 4){
			skin = "white5.jpg";
		}
		else if (dice == 5){
			skin = "white6.jpg";
		}
		else if (dice == 6){
			skin = "pink2.jpg";
		}
		else if (dice == 7){
			skin = "white8.jpg";
		}
		else if (dice == 8){
			skin = "white9.jpg";
		}
		else if (dice == 9){
			skin = "pink2.jpg";
		}else if (dice == 10){
			skin = "white3.jpg";
		}
		else if (dice == 11){
			skin = "white4.jpg";
		}
		else {
			skin = "pink2.jpg";
		}
		juncs.push_back(ProtoJuncusEffusus(Col4f(.7, .7, .6, 1), skin, "pink2.jpg", cps, ProtoJuncusEffusus::MEDIUM));
	}
	
	
	
	
	// For exporting geometry to STL
	std::vector<Tup4v> vs;
	for (int i = 0; i < juncs.size(); ++i){
		bool isTubule = false;
		if (i % 4 == 0)isTubule = false; else isTubule = true;
		std::vector<Tup4v> temp = juncs.at(i).getGeomData(isTubule, true);
		vs.insert(vs.end(), temp.begin(), temp.end());
	}
	
	// export geometry data to STL
	export(vs, STL);


	// Locations for page placement
	float arrayW = 9*.37;
	float arrayH = 13*.39;
	float gapX = arrayW / (COLUMNS - 1);
	float gapY = arrayH / (ROWS - 1);
	for (int i = 0; i < ROWS; ++i){
		for (int j = 0; j < COLUMNS; ++j){
			locs[i*COLUMNS + j] = Vec3(-arrayW / 2 + gapX*(j), arrayH / 2 - gapY*(i), 0);
			thetas[i*COLUMNS + j] = random(360.0);
			juncIDCounts[i*COLUMNS + j] = static_cast<int>(random(3, 24));
		}
	}
}



void ProtoJuncusEffusus05::initUniforms(){
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

void ProtoJuncusEffusus05::run() {
	setBackground(0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glViewport(0, 0, getWidth(), getHeight());
	glViewport(0, 0, width, height);
	//glViewport(0, 0, 800,1500);
	//shader.bind();

	// Lighting 
	glUniform3fv(lightPos0_U, 1, &light0.getPosition().x);
	glUniform4fv(lightDiffuse0_U, 1, &light0.getDiffuse().r);
	glUniform4fv(lightAmbient0_U, 1, &light0.getAmbient().r);
	glUniform4fv(lightSpecular0_U, 1, &light0.getSpecular().r);


	// save high resolution rendering
	// currently only works with max 999 tiles
	static int frameCounter = 0;
	if (frameCounter++ < 1){
		// save("juncs", 13);
	}
	
	render();

}


void ProtoJuncusEffusus05::render(int scaleFactor){

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


		// 2 Draw Tendrils
		S = glm::mat4(1.0);
		R = glm::mat4(1.0);
		T = glm::mat4(1.0);

		//S = glm::scale(glm::mat4(1.0f), glm::vec3(.25, .25, .25));
		R = glm::rotate(glm::mat4(1.0f), 70.0f, glm::vec3(0, 1, 0));
		//T = glm::translate(glm::mat4(1.0f), glm::vec3(juncs.at(i).getPosition().x, juncs.at(i).getPosition().y, juncs.at(i).getPosition().z - .75f));

		V = glm::lookAt(glm::vec3(0.0, 0.0, 7.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		M = T * R * S;
		MV = V * M;
		MVP = P * MV;

		// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
		// update normals

		N = glm::transpose(glm::inverse(glm::mat3(MV)));
		glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);

		//junc01.display(SURFACE, SURFACE);

		//for (int h = 0; h < ROWS*COLUMNS; ++h){
		//	// 2 Draw Tendrils

		//	S = glm::scale(glm::mat4(1.0f), glm::vec3(.22, .22, .22));
		//	R = glm::rotate(glm::mat4(1.0f), thetas[h], glm::vec3(0, 1, 0));
		//	T = glm::translate(glm::mat4(1.0f), glm::vec3(locs[h].x, locs[h].y, locs[h].z));

		//	V = glm::lookAt(glm::vec3(0.0, 0, 9.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		//	M = T * R * S;
		//	MV = V * M;
		//	MVP = P * MV;

		//	// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
		//	// update normals

		//	N = glm::transpose(glm::inverse(glm::mat3(MV)));
		//	glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
		//	glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
		//	glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);
		//	for (int i = 0; i < juncIDCounts[h]; ++i){
		//		juncs.at(i).display(SURFACE, SURFACE, 9, 1);
		//	}
		//}
		for (int i = 0; i < juncsCount; ++i){
			if (i % 3 == 0){
				juncs.at(i).display(SURFACE, SURFACE, 2, 1);
			}
			else {
				juncs.at(i).display(SURFACE, SURFACE, 4, 1);
			}
		}

}
