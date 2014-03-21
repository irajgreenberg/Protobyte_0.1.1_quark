#ifndef _PROTO_BASEAPP_H_
#define _PROTO_BASEAPP_H_

#if defined (_WIN32) || defined(_WIN64)
#include <GL/glew.h>
#include <Windows.h>
#include <stdio.h>
#endif


#if defined(__APPLE__)
// eventually remove for GL core >3.2 
#include <OpenGL/glu.h>
#endif



//

#include <memory>

// include GLM
#include "glm/gtc/type_ptr.hpp" // matrix copying
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"


//#include <iostream>
//#include "ProtoPlasm.h"

#include "libProtobyte/ProtoDimension2.h"
#include "libProtobyte/ProtoDimension3.h"
#include "libProtobyte/ProtoGroundPlane.h"
#include "libProtobyte/ProtoShader.h"
#include "libProtobyte/ProtoWorld.h"
#include "libProtobyte/ProtoColor3.h"
#include "libProtobyte/ProtoColor4.h"
#include "libProtobyte/ProtoMath.h"
#include "libProtobyte/ProtoVector2.h"
#include "libProtobyte/ProtoVector3.h"
#include "libProtobyte/ProtoToroid.h"
#include "libProtobyte/ProtoSpline3.h"
#include "libProtobyte/ProtoSphere.h"
#include "libProtobyte/ProtoTube.h"
#include "libProtobyte/ProtoLight.h"
#include "libProtobyte/ProtoCore.h"

// preproc dir for relative resource loading
// from http://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
// http://www.daniweb.com/software-development/cpp/threads/202937/ifdef-with-boolean-and-or
#include <stdio.h>  /* defines FILENAME_MAX */
#if defined (_WIN32) || defined (_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
// end relative loading proproc dir


#define BUFFER_OFFSET(i) ((void*)(i))
#include <iostream>

namespace ijg {
	class Protoplasm; // forward declare
	class ProtoBaseApp {

		// enable Protoplasm private access
		friend class ProtoPlasm;

	public:
		ProtoBaseApp();
		// void setAppWindowDetails(int appWidth, int appHeight, std::string appTitle);

	private:
		// only needed to be called by ProtoPlasm class - a friend
		void setWorld(std::unique_ptr<ProtoWorld> world);
		void runWorld();
		// don't let users touch this after context is created
		void setWidth(int canvasWidth);
		void setHeight(int canvasHeight);
		void setSize(const Dim2i& canvasSize);

	protected:
		/************************************
		 **********     FIELDS     **********
		 ***********************************/
		std::unique_ptr<ProtoWorld> world;
		int appWidth;
		int appHeight;
		std::string appTitle;
		int canvasWidth;
		int canvasHeight;
		int width, height;
		Dim2i canvasSize;

		int frameCount;
		float frameRate;

		// background color
		Col3f bgColor;

		// CAMERAS
		// 5 cameras (for now) accessible in world
		ProtoCamera camera0, camera1, camera2, camera3, camera4;

		// LIGHTS
		// per GL limits 8 lights accessible in world
		// light0 enabled by default
		//std::shared_ptr<ProtoLight> light0, light1, light2, light3, light4, light5, light6, light7;

		GLint glLights[8];

		enum Light {
			LIGHT_0,
			LIGHT_1,
			LIGHT_2,
			LIGHT_3,
			LIGHT_4,
			LIGHT_5,
			LIGHT_6,
			LIGHT_7
		};

		//ProtoLight light0, light1, light2, light3, light4, light5, light6, light7;
		//std::shared_ptr<ProtoLight> lights[8];

		std::vector<ProtoLight> lights;
		enum Matrix {
			MODEL_VIEW,
			PROJECTION
		};

		/***********************************
		*         GLM|GLSL MATRICES        *
		***********************************/
		// Camera Matrices
		glm::mat4 gl_viewMatrix, gl_modelMatrix, gl_modelViewMatrix, gl_projectionMatrix, gl_modelViewProjectionMatrix;
		glm::mat3 gl_normalMatrix;

		// Transformation Matrices
		glm::mat4 gl_translationMatrix, gl_rotationMatrix, gl_scaleMatrix;

		// Shadow Map Matrices
		glm::mat4 lightViewMatrix, lightProjMatrix, biasMatrix, biasProjMatrix, LVPMatrix;

		// Uniform variables
		glm::vec4 gl_light0Position;
		glm::vec3 gl_light0ReflectionConstant, gl_light0Intensity;

		glm::vec4 uLightPos0, uLightPos1, uLightPos2, uLightPos3, uLightPos4, uLightPos5, uLightPos6, uLightPos7;
		glm::vec4 uLightDiff0, uLightDiff1, uLightDiff2, uLightDiff3, uLightDiff4, uLightDiff5, uLightDiff6, uLightDiff7;

		glm::vec4 dc;
		//END



		/************************************
		 **********   FUNCTIONS   ***********
		 ***********************************/
		// pure virtual funcs require override
		virtual void init() = 0;
		virtual void run() = 0;

		// mouse/key events
		virtual void keyPressed();
		virtual void mousePressed();
		virtual void mouseRightPressed();
		virtual void mouseReleased();
		virtual void mouseRightReleased();
		virtual void mouseMoved(int mx, int my);
		virtual void mouseDragged();

		// window events
		virtual void onResized();
		virtual void onClosed();

		// frame values
		void setFrameRate(float frameRate);
		float getFrameRate() const;
		void setFrameCount(float frameCount);
		int getFrameCount() const;

		// Add content to world
		void add(std::unique_ptr<ProtoGeom3> geom);
		//void add(std::unique_ptr<ProtoLight> lt);
		//void add(std::shared_ptr<ProtoLight> lt);
		void add(std::unique_ptr<ProtoCamera> cam);
		//void initWorld();

		// set background color
		void setBackground(float r, float g, float b);
		void setBackground(float c);
		void setBackground(const Col3f& col);
		void setBackground(const Col4f& col);

		// get window properties **READ ONLY**
		int getWidth()const;
		int getHeight()const;
		Dim2i getSize()const;

		// image loading using SFML
		void loadImage(std::string url);

		// LIGHTS
		void lightsOn();
		void lightsOff();

		// CAMERAS

		// WORLD
		void printMatrix(Matrix m = MODEL_VIEW);

		/****************************
		 2d Automatic Procedural API
		 ***************************/
		enum Registration{
			CENTER,
			CORNER, // assumed top left
			CORNER_TR,
			CORNER_BR,
			CORNER_BL,
			RANDOM
		};

		void rect(float x, float y, float w, float h, Registration reg = CORNER);
		void rect(Vec2 pt0, Vec2 pt1, Registration reg = CORNER);
		void ellipse(float x, float y, float w, float h, Registration reg = CENTER);
		void ellipse(Vec2 pt0, Vec2 pt1, Registration reg = CENTER);
		void ellipse(float x, float y, float r, Registration reg = CENTER);



	};

	// inline methods
	inline void ProtoBaseApp::setFrameRate(float frameRate){
		this->frameRate = frameRate;
	}
	inline void ProtoBaseApp::setFrameCount(float frameCount){
		this->frameCount = frameCount;
	}

	inline float ProtoBaseApp::getFrameRate() const{
		return frameRate;
	}
	inline int ProtoBaseApp::getFrameCount() const{
		return frameCount;
	}



#define POINTS ProtoGeom3::POINTS
#define WIREFRAME ProtoGeom3::WIREFRAME
#define SURFACE ProtoGeom3::SURFACE

#define pushMatrix glPushMatrix
#define popMatrix glPopMatrix

#define translatef glTranslatef
#define rotatef glRotatef 
#define scalef glScalef 

#define light0 lights.at(0)
#define light1 lights.at(1)
#define light2 lights.at(2)
#define light3 lights.at(3)
#define light4 lights.at(4)
#define light5 lights.at(5)
#define light6 lights.at(6)
#define light7 lights.at(7)

}

#endif /* defined(PROTO_BASEAPP_H) */
