/*!  \brief  ProtoRootBall02.h:
Root ball study
Protobyte Library v02

Created by Ira on 4/30/14.
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

#include "ProtoRootBall02.h"

#include <thread>


void ProtoRootBall02::init() {

	//170, 150
	// set Materials for composite objects - or setup as multiple inheritance/interface
	rootBallCore = RootBall(Vec3f(), Vec3f(), Dim3f(2.55f), Col4f(.9f), 1, 30, .2, Tup2f(.5, 2.25), "shipPlate_yellow.jpg", 8);
	TransformFunction t1 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.2f, .75f), 3); // local, so can't be sent as reference
	rootBallCore.setTransformFunction(t1);


	//rootBall = RootBall(Vec3f(), Vec3f(), Dim3f(1.345f), Col4f(.9f), 1, 40, .2, Tup2f(.2, 3), "vascular3.jpg", 1);
	TransformFunction t2 = TransformFunction(TransformFunction::SINUSOIDAL, Tup2f(.14f, .22f), 80); // local, so can't be sent as reference
	//rootBall.setTransformFunction(t2);
	//std::vector<Tup4v> vs = rootBall.getGeomData();

	// export geometry data to 
	//std::vector<Tup4v> vs;
	//std::vector<Tup4v> temp = rootBallCore.getGeomData();
	//vs.insert(vs.end(), temp.begin(), temp.end());
	//std::vector<Tup4v> temp2 = rootBall.getGeomData();
	//vs.insert(vs.end(), temp2.begin(), temp2.end());
	//export(vs, STL);

	plane = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 1, 1), 1, 1, "leather2.jpg", .5);
	//plane.textureOn();
	plane.setBumpMap("leather2.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	plane.setTextureScale(1.9);
	//plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	plane.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	plane.setShininess(100);
	//trace("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS =", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);


	std::string texs[] = { "pebbles.jpg", "gold_foil2.jpg", "vascular.jpg", "greenCrocSkin.jpg", "pink2.jpg", "metal_screwHeads.jpg", "woodPlank.jpg", "metal_blue.jpg", "shipPlate_yellow.jpg", "reptile2_invert.jpg", "corroded_metal.jpg", "giraffe.jpg", "shipPlate.jpg", "metal_grate.jpg" };

	for (int i = 0; i < W*H; ++i){
		int sub = int(random(14));
		toroids[i] = Toroid(Vec3f(), Vec3f(random(45), random(45), random(45)), Dim3f(3, 3, 3), Col4f(.5, .5, .5, 1), 24, 24, 3, 1.2, texs[sub], 2.5);
		toroids[i].setBumpMap(texs[sub]);
		//toroids[i].setBumpMap("grime.jpg");
		toroids[i].setDiffuseMaterial(Col4f(.65, .75, 1, 1.0));
		toroids[i].setSpecularMaterial(Col4f(1, .5, .5, 1.0));
		toroids[i].setTextureScale(random(.25, 8.5));
		toroids[i].setShininess(int(random(5, 10)));
	}


	createShadowMap();


}


//bool ProtoRootBall02::createShadowMap(){
//	// shadow map
//	GLfloat border[] = { 1.0f, .0f, .0f, .0f };
//
//
//	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader 
//	glGenFramebuffers(1, &shadowBuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);
//
//	glGenTextures(1, &shadowTexture);
//	glBindTexture(GL_TEXTURE_2D, shadowTexture);
//	const int DEPTH_TEX_WIDTH = 1024;
//	const int DEPTH_TEX_HEIGHT = 1024;
//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32, DEPTH_TEX_WIDTH, DEPTH_TEX_HEIGHT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//
//	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowTexture, 0);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	
//	
//	//glActiveTexture(GL_TEXTURE0);
//	//glBindTexture(GL_TEXTURE_2D, depthTexture);
//
//
//	//// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
//	//GLuint FramebufferName = 0;
//	//glGenFramebuffers(1, &FramebufferName);
//	//glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
//	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
//
//	//GLenum drawBuffers[] = { GL_NONE };
//	//glDrawBuffers(1, drawBuffers); // No color buffer is drawn to.
//	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	// Always check that our framebuffer is ok
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		return false;
//}








void ProtoRootBall02::run() {

	// render shadowmap
	GLuint depthMatrixID = glGetUniformLocation(ProtoShader::getID_2(), "renderedTexture");

	glm::vec3 lightInvDir = glm::vec3(light0.getPosition().x, light0.getPosition().y, light0.getPosition().z);

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);
	// end rendershadow map


	setBackground(0);

	// save high resolution rendering
	// currently only works with max 999 tiles
	//
	//std::thread t(&ProtoBaseApp::render);
	//t.join();
	render();

	static int frameCounter = 0;
	if (frameCounter++ < 1){
		//save("roots", 13);
		/*std::thread t(&this->save, "roots", 13);
		t.join();*/
	}



}


void ProtoRootBall02::render(int scaleFactor){


	push();
	translate(0, -3, -30);
	scale(14.3);
	rotate(55, 1, 0, 0);
	plane.display();
	pop();

	push();
	{
		scale(.6);
		rotate(-getFrameCount()*.75, .65, 1, .425);
		//toroid.display();
		//push();
		//{
		//	scale(7.6);
		//	rotate(getFrameCount()*1.75, .25, .35, .425);
		//	rootBallCore.display();
		//}
		//pop();
	}
	pop();

	float width = 8;
	float height = 5;
	float colSpan = width / (W - 1);
	float rowSpan = height / (H - 1);
	for (int i = 0; i < W; ++i){
		for (int j = 0; j < H; ++j){
			push();
			translate(colSpan*i - width / 2, rowSpan*j - height / 2, 0);
			scale(.2);
			rotate(-getFrameCount()*.75, toroids[i*H + j].getRotation().x, toroids[i*H + j].getRotation().y, toroids[i*H + j].getRotation().z);
			toroids[i*H + j].display();
			pop();
		}
	}

}


