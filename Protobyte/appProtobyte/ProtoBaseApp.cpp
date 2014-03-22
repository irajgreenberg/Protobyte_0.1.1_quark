//
//  ProtoBaseApp.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/26/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "ProtoBaseApp.h"

using namespace ijg;


// NOTE: called before GL context created
ProtoBaseApp::ProtoBaseApp() {
    // std::cout << "in base class cstr" << std::endl;
	
	//    //instantiate lights w/o world
	    //light0 = std::shared_ptr<ProtoLight>(new ProtoLight());
	    //light1 = std::shared_ptr<ProtoLight>(new ProtoLight());
	    //light2 = std::shared_ptr<ProtoLight>(new ProtoLight());
	    //light3 = std::shared_ptr<ProtoLight>(new ProtoLight());
	    //light4 = std::shared_ptr<ProtoLight>(new ProtoLight());
	    //light5 = std::shared_ptr<ProtoLight>(new ProtoLight());
	    //light6 = std::shared_ptr<ProtoLight>(new ProtoLight());
	    //light7 = std::shared_ptr<ProtoLight>(new ProtoLight());

	glLights[0] = GL_LIGHT0;
	glLights[1] = GL_LIGHT1;
	glLights[2] = GL_LIGHT2;
	glLights[3] = GL_LIGHT3;
	glLights[4] = GL_LIGHT4;
	glLights[5] = GL_LIGHT5;
	glLights[6] = GL_LIGHT6;
	glLights[7] = GL_LIGHT7; 
	
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
}


// Get handle to world and init BaseApp
// Note: this function does some work of cstr because
// it is called after GL context has been created.
//void ProtoBaseApp::setWorld(std::unique_ptr<ProtoWorld> world){
//    this->world = std::move(world);
//    
//    //instantiate lights
//    light0 = std::shared_ptr<ProtoLight>(new ProtoLight());
//    light1 = std::shared_ptr<ProtoLight>(new ProtoLight());
//    light2 = std::shared_ptr<ProtoLight>(new ProtoLight());
//    light3 = std::shared_ptr<ProtoLight>(new ProtoLight());
//    light4 = std::shared_ptr<ProtoLight>(new ProtoLight());
//    light5 = std::shared_ptr<ProtoLight>(new ProtoLight());
//    light6 = std::shared_ptr<ProtoLight>(new ProtoLight());
//    light7 = std::shared_ptr<ProtoLight>(new ProtoLight());
//    
//    
//    
//    this->world->add(light0);
//    this->world->add(light1);
//    this->world->add(light2);
//    this->world->add(light3);
//    this->world->add(light4);
//    this->world->add(light5);
//    this->world->add(light6);
//    this->world->add(light7);
//    
//    // set default light on
//    // light0->on();
//    
//    
//}

// start World rendering loop
//void ProtoBaseApp::runWorld() {
//    world->run();
//}


//void ProtoBaseApp::add(std::unique_ptr<ProtoGeom3> geom){
//    world->add(std::move(geom));
//}
//
////void ProtoBaseApp::add(std::unique_ptr<ProtoLight> lt){
////     world->add(std::move(lt));
////}
//
//void ProtoBaseApp::add(std::unique_ptr<ProtoCamera> cam){
//    world->add(std::move(cam));
//}

// gen funcs
// overloaded background
void ProtoBaseApp::setBackground(float r, float g, float b){
    bgColor.setR(r);
    bgColor.setG(r);
    bgColor.setB(r);
   // world->setBackgroundColor(Col3f(r, g, b));
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
    glEnable(GL_LIGHTING);
    
}
void ProtoBaseApp::lightsOff(){
    glDisable(GL_LIGHTING);
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
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    std::string cp = cCurrentPath; //cast char[] to string
    std::cout << "current path = " << cp << std::endl;
    std::string pathExtension = "/resources/imgs";
    std::string imgName = "/"+ imageName;
    std::string url = cp+pathExtension+imgName;
//    sf::Texture texture;
//    if (!texture.loadFromFile(url))
//    {
//        // error...
//    }
}

// END window details

void ProtoBaseApp::printMatrix(Matrix m){
    GLfloat matrix[16];
    if(m==MODEL_VIEW) {
        glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
        std::cout << "\nGL ModelView Matrix" << std::endl;
    } else {
        glGetFloatv (GL_PROJECTION_MATRIX, matrix);
        std::cout << "\nGL Projection Matrix" << std::endl;
    }
    std::cout << matrix[0] << " | " << matrix[4] << " | " << matrix[8] << " | "  << matrix[12] << "\n";
    std::cout << matrix[1] << " | " << matrix[5] << " | " << matrix[9] << " | " << matrix[13] << "\n";
    std::cout << matrix[2] << " | " << matrix[6] << " | " << matrix[10] << " | "  << matrix[14] << "\n";
    std::cout << matrix[3] << " | " << matrix[7] << " | " << matrix[11] << " | "  << matrix[15] << std::endl;
}

// 2D api
void ProtoBaseApp::rect(float x, float y, float w, float h, Registration reg){
    float _x = 0, _y = 0;
    // initialize glew for Windows
#if defined(_WIN32) || defined(__linux__)
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
#endif
    
    /* CENTER,
     CORNER, // assumed top left
     CORNER_TR,
     CORNER_BR,
     CORNER_BL,
     RANDOM
     */
    
    switch(reg){
        case CENTER:
            _x = x-w/2;
            _y = y+h/2;
            break;
        case CORNER:
            _x = x;
            _y = y;
            break;
        case CORNER_TR:
            _x = x-w;
            _y = y;
            break;
        case CORNER_BR:
            _x = x-w;
            _y = y+h;
            break;
        case CORNER_BL:
            _x = x;
            _y = y+h;
            break;
        case RANDOM:
            // to do
            break;
        
    }
    
    
    float vecs[] = {_x, _y, _x, _y-h, _x+w, _y-h, _x+w, _y};
    int inds[] = {0, 1, 2, 0, 2, 3};
	
    // vert data
    GLuint vboID;
    glGenBuffers(1, &vboID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof (GLfloat) * 8;
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STATIC_DRAW); // allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &vecs[0]); // upload the data
    
    // indices data
    GLuint indexVboID;
    glGenBuffers(1, &indexVboID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID); // Bind the element array buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*6, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GL_UNSIGNED_INT)*6, &inds[0]); // upload the data
    
    
    // fill state is true - need to create this
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    
    // draw rect
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 2*sizeof(GLfloat), BUFFER_OFFSET(0));
  
    
    glDisable(GL_LIGHTING);

    pushMatrix();
    translatef(0, 0, -500); // set camera to -500 default to get close to pixel accurate coords
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    popMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    // reenable lighting
    glEnable(GL_LIGHTING);
}

void ProtoBaseApp::initUniforms(){
	// currenlty implemented in derived classes (need to think on this a bit)
}




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

void ProtoBaseApp::rect(Vec2 pt0, Vec2 pt1, Registration reg){
    rect(pt0.x, pt0.y, pt1.x-pt0.x, pt1.y-pt0.y, reg);
}

void ProtoBaseApp::ellipse(float x, float y, float w, float h, Registration reg){
    
}

void ProtoBaseApp::ellipse(Vec2 pt0, Vec2 pt1, Registration reg){
    
}

void ProtoBaseApp::ellipse(float x, float y, float r, Registration reg){
    
}



// EVENTS
void ProtoBaseApp::keyPressed(){}
void ProtoBaseApp::mousePressed(){}
void ProtoBaseApp::mouseRightPressed(){}
void ProtoBaseApp::mouseReleased(){}
void ProtoBaseApp::mouseRightReleased(){}
void ProtoBaseApp::mouseMoved(int mx, int my){}
void ProtoBaseApp::mouseDragged(){}

// window events
void ProtoBaseApp::onResized(){}
void ProtoBaseApp::onClosed(){}




