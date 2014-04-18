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

#include "libProtobyte/ProtoOSC.h"
#include "libProtobyte/ProtoDimension2.h"
#include "libProtobyte/ProtoDimension3.h"
#include "libProtobyte/ProtoGroundPlane.h"
#include "libProtobyte/ProtoShader.h"
#include "libProtobyte/ProtoWorld.h"
#include "libProtobyte/ProtoColor3.h"
#include "libProtobyte/ProtoColor4.h"
#include "libProtobyte/ProtoBlock.h"
#include "libProtobyte/ProtoMath.h"
#include "libProtobyte/ProtoVector2.h"
#include "libProtobyte/ProtoVector3.h"
#include "libProtobyte/ProtoToroid.h"
#include "libProtobyte/ProtoSpline3.h"
#include "libProtobyte/ProtoSphere.h"
#include "libProtobyte/ProtoTube.h"
#include "libProtobyte/ProtoLight.h"
#include "libProtobyte/ProtoCore.h"
#include "libProtobyte/ProtoTuple4.h"

#include "libProtobyte/ProtoJuncusEffusus.h"
#include "libProtobyte/ProtoCephalopod.h"

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
#include <stack>

namespace ijg {
	class Protoplasm; // forward declare
	class ProtoBaseApp {

		// enable Protoplasm private access
		friend class ProtoPlasm;

	public:
		ProtoBaseApp();
		ProtoBaseApp(const ProtoOSC& listener);
		// void setAppWindowDetails(int appWidth, int appHeight, std::string appTitle);

	private:
		// only needed to be called by ProtoPlasm class - a friend
		void setWorld(std::unique_ptr<ProtoWorld> world);
		void runWorld();
		// don't let users touch this after context is created
		void setWidth(int canvasWidth);
		void setHeight(int canvasHeight);
		void setSize(const Dim2i& canvasSize);

		void _init();
		void _initUniforms();
		void _run();
		// void concat(); moved down for testing

	protected:
		void concat();
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

		enum Format {
			STL,
			TXT,
			RTF
		};

		// shader
		ProtoShader shader;
		
		//ProtoLight light0, light1, light2, light3, light4, light5, light6, light7;
		//std::shared_ptr<ProtoLight> lights[8];

		std::vector<ProtoLight> lights;
		enum Matrix {
			MODEL_VIEW,
			PROJECTION
		};

		/***********************************
		*           GLSL UNIFORMS          *
		***********************************/
		// using initials ONLY for matrices
		// Uniform Camera Matrices
		glm::mat4 M, V, MV, P, MVP;

		// Uniform Transformation Matrices
		glm::mat4 T, R, S;

		// Uniform Shadow Map Matrices
		glm::mat4 L_V, L_MV, L_P, L_B, L_BP, L_MVP;

		// Uniform Normal Matrix
		glm::mat3 N;

		// flags for shader locations
		GLuint M_U, V_U, MV_U, P_U, MVP_U, N_U;
		GLuint T_U, R_U, S_U;
		GLuint L_MVP_U; // only for Light perspective
		GLuint shadowMapTex; // id for shadermap texture

		std::stack <glm::mat4> matrixStack;


		
		// Uniform Lighting location vars - replace above
		struct Light_U {
			GLuint position;
			GLuint diffuse;
			GLuint ambient;
			GLuint specular;;
		};
		Light_U lights_U[8];
		//END

		// Shadow Map
		GLuint shadowMap_U;

		// OSC obj 
		ProtoOSC listener;


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
		void setBackground(const ProtoColor4<float>& col);

		// get window properties **READ ONLY**
		int getWidth()const;
		int getHeight()const;
		Dim2i getSize()const;

		// image loading using SFML
		void loadImage(std::string url);

		// shaders stuff
		void GLSLInfo(ProtoShader* shader);
			

		// LIGHTS
		void lightsOn();
		void lightsOff();

		//// create traditional interface for GPU controlled transforms
		void translate(float tx, float ty, float tz);
		void translate(const Vec3f& tXYZ);
		void rotate(float angle, float axisX, float axisY, float axisZ);
		void rotate(float angle, const Vec3f& rXYZ);
		void scale(float s);
		void scale(float sx, float sy, float sz);
		void scale(const Vec3f& sXYZ);
		//implements transform matrix stack
		void push();
		void pop();

		//void lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up);
		//void perspective(float viewAngle, float aspect, float nearDist, float farDist);

		// exporting
		void export(std::vector<Tup4v> vs, Format type);

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


		// saving stuff
		virtual void render(int scaleFactor = 1) = 0; // evntually maybe make pure virtual (ehhh, maybe not)
		void save(std::string name = "img", int scaleFactor = 1);
		//void saveTiles(int rows, int columns);
		bool stitchTiles(std::string url, int tiles);
		



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

// remove this old stuff
//#define pushMatrix glPushMatrix
//#define popMatrix glPopMatrix
//
//#define translatef glTranslatef
//#define rotatef glRotatef 
//#define scalef glScalef 

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
