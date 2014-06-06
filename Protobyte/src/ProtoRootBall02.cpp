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
	globalAmbient = Col3f(.25f, .19f, .47f); // slight violet color

	// light0
	light0.setPosition(Vec3f(0, 0, .1));
	light0.setIntensity(Vec3f(.85f, .85f, .85f));

	//light0.setDiffuse(Col4f(1, 1, 1, 1.0f));
	//light0.setAmbient(Col4f(.1, .1, .1, 1.0));
	//light0.setSpecular(Col4f(.1, .1, .1, 1.0));
	//light0.on();

	//light1.setPosition(Vec3f(-1, 0, 1));
	//light1.setDiffuse(Col4f(.2, .5, .65, 1.0f));
	//light1.setAmbient(Col4f(.3, .3, .3, 1.0));
	//light1.setSpecular(Col4f(1, 1, 1, 1.0));
	//light1.on();

	//170, 150
	// set Materials for composite objects - or setup as multiple inheritance/interface
	rootBallCore = RootBall(Vec3f(), Vec3f(), Dim3f(2.55f), Col4f(.9f), 1, 30, .2, Tup2f(.5, 2.25), "leather2.jpg", 8);
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

	plane = GroundPlane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 1, 1), 1, 1, "brown_tile.jpg", .5);
	//plane.textureOn();
	plane.setBumpMap("brown_tile.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	plane.setTextureScale(.9);
	//plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	plane.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	plane.setShininess(50);
	//trace("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS =", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

	toroid = Toroid(Vec3f(), Vec3f(), Dim3f(3, 3, 3), Col4f(.5, .5, .5, 1), 24, 24, 3, 1.2, "pebbles.jpg", 2.5);
	toroid.setTextureScale(3.9);
	//toroid.setShininess(1);
	////toroid.loadBumpMapTexture("pebbles_normal.jpg");
	toroid.setBumpMap("pebbles.jpg");

	//createShadowMap();

	
}


bool ProtoRootBall02::createShadowMap(){
	// shadow map
	GLfloat border[] = {1.0f, .0f, .0f, .0f};
	

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTexture);


	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName); 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	GLenum drawBuffers[] = { GL_NONE };
	glDrawBuffers(1, drawBuffers); // No color buffer is drawn to.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
}








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
	scale(6.3);
	rotate(55, 1, 0, 0);
	plane.display();
	pop();

	push();
	{
		scale(.6);
		rotate(-getFrameCount()*.75, .65, 1, .425);
		toroid.display();
		//push();
		//{
		//	scale(7.6);
		//	rotate(getFrameCount()*1.75, .25, .35, .425);
		//	rootBallCore.display();
		//}
		//pop();
	}
	pop();

}


