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

	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());
	lights.push_back(ProtoLight());

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
}

void ProtoBaseApp::_init(){
	shader = ProtoShader("shader1.vert", "shader1.frag");

	glViewport(0, 0, width, height);

	// START standard transformation matrices: ModelView / Projection / Normal
	M = glm::mat4(1.0f); // set to identity
	V = glm::lookAt(glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	MV = V * M;
	N = glm::transpose(glm::inverse(glm::mat3(MV)));

	// projection matrix and MVP Matrix
	// perspective
	viewAngle = 45.0f;
	aspect = float(width) / float(height);
	// ortho
	//trace("width = ", width);
	//trace("height =", height);
	left = -width/2;
	right = width/2;
	bottom = -height/2;
	top = height/2;

	nearDist = .1f;
	farDist = 600.0f;

	P = glm::perspective(viewAngle, aspect, nearDist, farDist);
	MVP = P * MV;
	// END Model / View / Projection data

	// tranformation matricies
	T = glm::mat4(1.0f);
	R = glm::mat4(1.0f);
	S = glm::mat4(1.0f);

	_initUniforms();
}

void ProtoBaseApp::_initUniforms(){
	// lighting
	shader.bind();

	// get shader location for default 8 lights
	for (int i = 0; i < 8; ++i){
		std::string pos = "lights[" + std::to_string(i) + "].position";
		lights_U[i].position = glGetUniformLocation(shader.getID(), pos.c_str());

		std::string diff = "lights[" + std::to_string(i) + "].diffuse";
		lights_U[i].diffuse = glGetUniformLocation(shader.getID(), diff.c_str());

		std::string amb = "lights[" + std::to_string(i) + "].ambient";
		lights_U[i].ambient = glGetUniformLocation(shader.getID(), amb.c_str());

		std::string spec = "lights[" + std::to_string(i) + "].specular";
		lights_U[i].specular = glGetUniformLocation(shader.getID(), spec.c_str());
	}


	//matrices
	MV_U = glGetUniformLocation(shader.getID(), "modelViewMatrix");
	MVP_U = glGetUniformLocation(shader.getID(), "modelViewProjectionMatrix");
	N_U = glGetUniformLocation(shader.getID(), "normalMatrix");

	// shadow map
	shadowMapTex = glGetUniformLocation(shader.getID(), "shaderMapTexture");
	L_MVP_U = glGetUniformLocation(shader.getID(), "lightModelViewProjectionMatrix");

}

void ProtoBaseApp::_run(){
	// entry point to draw thread
	// reset trrnaformation matrix
	//T = glm::mat4(1.0f);
	//R = glm::mat4(1.0f);
	//S = glm::mat4(1.0f);
	M = glm::mat4(1.0f);

	// update all 8 lights in shaders
	for (int i = 0; i < 8; ++i){
		glUniform3fv(lights_U[i].position, 1, &lights[i].getPosition().x);
		glUniform4fv(lights_U[i].diffuse, 1, &lights[i].getDiffuse().r);
		glUniform4fv(lights_U[i].ambient, 1, &lights[i].getAmbient().r);
		glUniform4fv(lights_U[i].specular, 1, &lights[i].getSpecular().r);
	}

	V = glm::lookAt(glm::vec3(0.0, 0.0, 7.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	//M = T * R * S;
	MV = V * M;
	MVP = P * MV;

	// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
	// update normals

	N = glm::transpose(glm::inverse(glm::mat3(MV)));
	glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);
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

// 2D api  ********************NOTE: This is not really implemented!**********************
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


	float vecs[] = { _x, _y, _x, _y - h, _x + w, _y - h, _x + w, _y };
	int inds[] = { 0, 1, 2, 0, 2, 3 };

	// vert data
	GLuint vboID;
	glGenBuffers(1, &vboID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof (GLfloat)* 8;
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STATIC_DRAW); // allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &vecs[0]); // upload the data

	// indices data
	GLuint indexVboID;
	glGenBuffers(1, &indexVboID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID); // Bind the element array buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)* 6, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GL_UNSIGNED_INT)* 6, &inds[0]); // upload the data


	// fill state is true - need to create this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// draw rect
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));


	glDisable(GL_LIGHTING);

	//pushMatrix();
	//translatef(0, 0, -500); // set camera to -500 default to get close to pixel accurate coords
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	//popMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// reenable lighting
	//glEnable(GL_LIGHTING);
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
	rect(pt0.x, pt0.y, pt1.x - pt0.x, pt1.y - pt0.y, reg);
}

void ProtoBaseApp::ellipse(float x, float y, float w, float h, Registration reg){

}

void ProtoBaseApp::ellipse(Vec2 pt0, Vec2 pt1, Registration reg){

}

void ProtoBaseApp::ellipse(float x, float y, float r, Registration reg){

}




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

void ProtoBaseApp::save(std::string name, int scaleFactor){


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


	for (int i = 0; i < scaleFactor; ++i){
		for (int j = 0; j < scaleFactor; ++j){
			//trace("in drawToFrameBuffer");
			//glClearColor(0, 0, 0, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			//From: http://stackoverflow.com/questions/12157646/how-to-render-offscreen-on-opengl

			glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
			this->render();

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

bool ProtoBaseApp::stitchTiles(std::string url, int tiles){
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
	MV = V * M;
	N = glm::transpose(glm::inverse(glm::mat3(MV)));
	MVP = P * MV;
	glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);
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
void ProtoBaseApp::mouseMoved(int mx, int my){}
void ProtoBaseApp::mouseDragged(){}

// window events
void ProtoBaseApp::onResized(){}
void ProtoBaseApp::onClosed(){}




