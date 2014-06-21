// shadowTest

#include "shadowTest.h"


void shadowTest::init() {
	plane = Plane(Vec3(), Vec3(), Dim2f(8, 7), Col4f(1, 1, 1, 1), 1, 1, "paper.jpg", 1);
	//plane.textureOn();
	plane.setBumpMap("paper.jpg");
	//plane.loadBumpMapTexture("shipPlate_normal.jpg");
	plane.setTextureScale(1);
	//plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	plane.setSpecularMaterial(Col4f(.70, .7, .7, 1.0));
	plane.setShininess(90);
	//trace("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS =", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

	toroid = Toroid(Vec3f(), Vec3f(random(45), random(45), random(45)), Dim3f(3, 3, 3), Col4f(.5, .5, .5, 1), 24, 24, 3, 1.2, "redFire.jpg", 2.5);
	toroid.setBumpMap("shipPlate.jpg");
	//toroids[i].setBumpMap("grime.jpg");
	toroid.setDiffuseMaterial(Col4f(.65, .75, 1, 1.0));
	toroid.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	toroid.setTextureScale(1);
	toroid.setShininess(int(random(15, 40)));
}




void shadowTest::run() {

	//// render shadowmap
	//GLuint depthMatrixID = glGetUniformLocation(ProtoShader::getID_2(), "renderedTexture");

	//glm::vec3 lightInvDir = glm::vec3(light0.getPosition().x, light0.getPosition().y, light0.getPosition().z);

	//// Compute the MVP matrix from the light's point of view
	//glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	//glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//glm::mat4 depthModelMatrix = glm::mat4(1.0);
	//glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	//// Send our transformation to the currently bound shader,
	//// in the "MVP" uniform
	//glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);
	//// end rendershadow map

	setBackground(0);

	render();



}


void shadowTest::render(int scaleFactor){

	


	glBindFramebuffer(GL_FRAMEBUFFER, shadowBufferID);
	//clear depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);
	//reset viewport to the shadow map texture size
	glViewport(0, 0, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);

	// enable front face culling for shadowing
	glCullFace(GL_FRONT);

	glUniform1i(shaderPassFlag_U, 1); // controls render pass in shader

	//glUniform1i(shadowMap_U, 5);

	push();
	translate(0, 0, -10);
	
	scale(20,16, 1);
	//rotate(90, 1, 0, 0);
	plane.display();
	pop();


	push();

	scale(.4);

	rotate(-getFrameCount()*.75, toroid.getRotation().x, toroid.getRotation().y, toroid.getRotation().z);
	pop();

	//renable back face culling
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDrawBuffer(GL_BACK_LEFT);
	glViewport(0, 0, getWidth(), getHeight());

	glCullFace(GL_BACK);

	glUniform1i(shaderPassFlag_U, 0); // controls render pass in shader
	//concat();
	//glUniform1i(shadowMap_U, 0);

	push();
	translate(0, 0, -10);
	scale(20,16, 1);
	plane.display();
	pop();


	push();
	scale(.4);
	rotate(-getFrameCount()*.75, toroid.getRotation().x, toroid.getRotation().y, toroid.getRotation().z);
	toroid.display();
	pop();


	

}


