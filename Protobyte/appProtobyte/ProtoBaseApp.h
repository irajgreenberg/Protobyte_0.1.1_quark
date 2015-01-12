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

#include <thread>
#include <mutex>
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
#include "libProtobyte/ProtoPlane.h"
#include "libProtobyte/ProtoGroundPlane.h"
#include "libProtobyte/ProtoTransformFunction.h"
#include "libProtobyte/ProtoShader.h"
#include "libProtobyte/ProtoWorld.h"
#include "libProtobyte/ProtoColor3.h"
#include "libProtobyte/ProtoColor4.h"
#include "libProtobyte/ProtoBlock.h"
#include "libProtobyte/ProtoMath.h"
#include "libProtobyte/ProtoVector2.h"
#include "libProtobyte/ProtoVector3.h"
#include "libProtobyte/ProtoCylinder.h"
#include "libProtobyte/ProtoToroid.h"
#include "libProtobyte/ProtoSpline3.h"
#include "libProtobyte/ProtoSphere.h"
#include "libProtobyte/ProtoTube.h"
#include "libProtobyte/ProtoLight.h"
#include "libProtobyte/ProtoCore.h"
#include "libProtobyte/ProtoTuple4.h"
#include "libProtobyte/ProtoEllipse.h"
#include "libProtobyte/ProtoPath3.h"
#include "libProtobyte/ProtoTessellator.h"
#include "libProtobyte/ProtoPath2.h"


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


// for offset into the FBO interleaved buffer (ugly I know!)
#define BUFFER_OFFSET(i) ((void*)(i))

#include <iostream>
#include <stack>


// for triangle.c tessellation
#ifdef SINGLE
#define REAL float
#else /* not SINGLE */
#define REAL double
#endif /* not SINGLE */
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include "triangle.h"

//extern "C" void triangulate(char *, struct triangulateio *, struct triangulateio *,
//struct triangulateio *);

namespace ijg {
	
	
	
	// non-member functions

	// forward declares
	class Protoplasm; 

	class ProtoBaseApp {

		// enable private access
		friend class ProtoPlasm;
		friend class ProtoPath2;

	public:
		ProtoBaseApp();
		ProtoBaseApp(const ProtoOSC& listener);
		// void setAppWindowDetails(int appWidth, int appHeight, std::string appTitle);

		// GLFW Mouse events
		void setMouseButton(int mouseAction, int mouseButton, int mouseMods);
		
		// GLFW window events
		void setWindowFrameSize(const Dim2i& windowFrameSize);


		static ProtoBaseApp* baseApp;
		static ProtoBaseApp* getBaseApp();

	private:
		// only needed to be called by ProtoPlasm class - a friend
		void setWorld(std::unique_ptr<ProtoWorld> world);
		void runWorld();
		// don't let users touch this after context is created
		void setWidth(int canvasWidth);
		void setHeight(int canvasHeight);
		void setSize(const Dim2i& canvasSize);

		void _init();
		//void _initUniforms();
		//void _run(const Vec2f& mousePos/*, int mouseBtn, int key*/);
		void _run(const Vec2f& mousePos, const Vec4i& windowCoords = Vec4i(0, 0, 1, 1)/*, int mouseBtn, int key*/);
		//void setViewport(int width, int height);
		// void concat(); moved down for testing

		//void pathTessellate(struct triangulateio *io, int markers, int reporttriangles, int reportneighbors, int reportsegments,
		//	int reportedges, int reportnorms);

		

	protected:
		void _initUniforms(ProtoShader* shader_ptr); // temporarily here. put back in private eventually
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
		Dim2i windowFrameSize;

		int frameCount;
		float frameRate;

		// background color
		Col3f bgColor;

		// mouse fields
		float mouseX, mouseY, mouseLastFrameX, mouseLastFrameY;
		// 1, 2, or 3
		int mouseButton;
		int mouseAction;
		int mouseMods;
		bool isMousePressed;

		// for arcball
		float arcballRotX, arcballRotY;
		float arcballRotXLast, arcballRotYLast;
		float mouseXIn, mouseYIn;
		//bool isArcballOn;
			
			
			// CAMERAS
		// 5 cameras (for now) accessible in world
		ProtoCamera camera0, camera1, camera2, camera3, camera4;

		// LIGHTS
		// per GL limits 8 lights accessible in world
		// light0 enabled by default
		//std::shared_ptr<ProtoLight> light0, light1, light2, light3, light4, light5, light6, light7;

		Col3f globalAmbient;

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
		ProtoShader shader3D, shader2D;

		//ProtoLight light0, light1, light2, light3, light4, light5, light6, light7;
		//std::shared_ptr<ProtoLight> lights[8];

		std::vector<ProtoLight> lights;
		enum Matrix {
			MODEL_VIEW,
			PROJECTION
		};

		float viewAngle, aspect, nearDist, farDist;

		void setViewAngle(float viewAngle);
		void setAspect(float aspect);
		void setNearDist(float nearDist);
		void setFarDist(float farDist);

		float left, right, bottom, top;

		void setLeft(float left);
		void setRight(float right);
		void setBottom(float bottom);
		void setTop(float top);

		enum ProjectionType {
			PERSPECTIVE,
			ORTHOGONAL
		};
		void setProjection(ProjectionType projType = PERSPECTIVE);

		/***********************************
		*           path plotting  
		*beginPath(), endPath(), closePath()
		***********************************/
		std::vector<Vec3f> path;

		// new approach
		//ProtoPath2 path;

		/***************END****************/

		/***********************************
		*           GLSL UNIFORMS          *
		***********************************/
		// using initials ONLY for matrices
		// Uniform Camera Matrices
		glm::mat4 M, V, MV, P, MVP;

		// Uniform Transformation Matrices
		glm::mat4 T, R, S;

		// Uniform Shadow Map Matrices
		glm::mat4 L_V, L_MV, L_P, L_B, L_BP, L_MVBP;

		//glm::mat4 L_MVS[8];
		//glm::mat4 shadM[8];

		// Uniform Normal Matrix
		glm::mat3 N;

		// flags for shader locations
		GLuint M_U, V_U, MV_U, P_U, MVP_U, N_U;
		GLuint T_U, R_U, S_U;
		GLuint L_MVBP_U; // only for Light perspective
		GLuint shaderPassFlag_U;

		// Uniform Shadow Map
		GLuint shadowMap_U;

		// Uniform Lighting factors
		// enable/disable lighting factors for 2D rendering
		Vec4f ltRenderingFactors;
		GLuint lightRenderingFactors_U;

		// color flags/fields for immediate mode drawing
		bool isStroke, isFill;
		Col4f fillColor, strokeColor;
		float lineWidth;


		// shadow mapping texture id's
		GLuint shadowBufferID, shadowTextureID;

		// flag for shadowing
		bool areShadowsEnabled;

		const int SHADOWMAP_WIDTH = 4096, SHADOWMAP_HEIGHT = 4096;

		std::stack <glm::mat4> matrixStack;



		// Uniform Lighting location vars
		struct Light_U {
			GLuint position;
			GLuint intensity;
			GLuint diffuse;
			GLuint ambient;
			GLuint specular;;
		};
		Light_U lights_U[8];

		GLuint globalAmbient_U;



		// OSC obj 
		ProtoOSC listener;


		/************************************
		 **********   FUNCTIONS   ***********
		 ***********************************/
		// pure virtual funcs require override
		virtual void init() = 0;
		virtual void run() = 0;
		virtual void display() = 0;

		// switched from pure virtual above to enable thread to call member functions
		/*	virtual void init(){}
			virtual void run(){}*/

		virtual bool ProtoBaseApp::createShadowMap();

		// mouse/key events
		virtual void keyPressed();
		virtual void mousePressed();
		virtual void mouseRightPressed();
		virtual void mouseReleased();
		virtual void mouseRightReleased();
		virtual void mouseMoved();
		virtual void mouseDragged();

		// window events
		virtual void onResized();
		virtual void onClosed();

		//arcball
		void arcballBegin();
		void arcballEnd();


		// frame values
		void setFrameRate(float frameRate);
		float getFrameRate() const;
		void setFrameCount(float frameCount);
		int getFrameCount() const;

		// Add content to world
		// NOT USED - REMOVE
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

		bool areShadowsOn;
		void setShadowsOn(bool areShadowsOn);
		void shadowsOn();
		void shadowOff();

		// get window properties **READ ONLY**
		int getWidth()const;
		int getHeight()const;
		Dim2i getSize()const;

		// image loading using SFML
		// IS THIS STILL BEING USED?? - NO MORE SFML
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
		void export(std::vector<Tup4v> vs, Format type); // bucket of Vecs

		// not using export option below yet
		void export(std::vector<Shape3> shapes, Format type); // ProtoShapes
		void export(std::vector<Geom3> geoms, Format type); // ProtoGeoms
		void export(std::vector<Geom3> geoms, std::vector<Shape3> shapes, Format type); // geoms & shapes
		void export(std::vector<Shape3> shapes, std::vector<Geom3> geoms, Format type); // shapes & geoms

		template<typename T, typename U>
		void export(T objType1, U objType2, Format type);

		// pass multiple objs
		//template<typename First, typename ... Rest>
		//void export(Format type, First first, Rest ... rest);

		// CAMERAS

		// WORLD
		void printMatrix(Matrix m = MODEL_VIEW);

		/***********BEGIN************
		 2D Automatic Procedural API
		 ***************************/
		enum Registration{
			CENTER,
			CORNER, // assumed top left
			CORNER_TR,
			CORNER_BR,
			CORNER_BL,
			RANDOM
		};

		// functions that flag  enable/disable 2D lighting
		void enable2DRendering();
		void disable2DRendering();

		void calculate2DBuffers(float prims[], int inds[], int primsCount, int indsCount);

		// Styles API
		void fill(const Col4f& col);
		void fill(float gray);
		void fill(float gray, float a);
		void fill(float r, float g, float b);
		void fill(float r, float g, float b, float a);
		void noFill();

		void stroke(const Col4f& col);
		void stroke(float gray);
		void stroke(float gray, float a);
		void stroke(float r, float g, float b);
		void stroke(float r, float g, float b, float a);
		void noStroke();
		void strokeWeight(float lineWidth = 1.0);
		
		// points around ellipse
		int ellipseDetail;

		
		// Primitives API
		// Precalculating buffers for 2D primitives for efficiency
		// updated with glBufferSubData and binding vbo/vao
		
		// rect buffer ids
		float rectPrims[28];
		GLuint vaoRectID, vboRectID;
		void _createRect();

		// quad buffer ids
		float quadPrims[28];
		GLuint vaoQuadID, vboQuadID;
		void _createQuad();

		// ellipse buffer ids
		std::vector<float> ellipsePrims;
		std::vector<int> ellipseInds;
		GLuint vaoEllipseID, vboEllipseID, indexVboEllipseID;
		void _createEllipse();

		// star buffer ids
		std::vector<float> starPrims;
		GLuint vaoStarID, vboStarID;
		void _createStar();

		// path buffer ids (for begin(), vertex(), end())
		bool isPathRecording;
		//ProtoTessellator tess;
		std::vector<float> pathPrims;
		std::vector<GLdouble> tessellatedPrims;
		std::vector<std::vector<GLdouble>> pathPrimsForTessellator;
		std::vector<int> pathInds;
		GLuint vaoPathID, vboPathID, indexVboPathID; 
		void _createPath();
		enum PathRenderMode {
			POLYGON, TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN, LINES, LINE_STRIP, LINE_LOOP
		} pathRenderMode;

		//3D
		// box buffer ids
		// (x, y, z, nx, ny, nz, r, g, b, a, u, v, tx, ty, tz)
		Vec2f textureScale;
		const static int boxPrimCount = 24*15;
		float boxPrims[boxPrimCount];
		int boxInds[24]; // 6 faces
		GLuint vaoBoxID, vboBoxID, indexVboBoxID;
		void _createBox();

		// primitive funcs
		void rect(float x, float y, float w, float h, Registration reg = CORNER);
		void rect(const Vec2& pt0, const Vec2& pt1, Registration reg = CORNER);
		void rect(float radius1, float radius2, Registration reg = CENTER);
		void quad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, Registration reg = CENTER);
		void quad(const Vec2& pt0, const Vec2& pt1, const Vec2& pt2, const Vec2& pt3, Registration reg = CENTER);
		void ellipse(float x, float y, float w, float h, Registration reg = CENTER);
		void ellipse(float r0, float r1, Registration reg = CENTER);
		void ellipse(float r, Registration reg = CENTER);
		void ellipse(float x, float y, float r, Registration reg = CENTER);
		void triangle(const Vec2& pt0, const Vec2& pt1, const Vec2& pt2);
		void triangle(float x0, float y0, float x1, float y1, float x2, float y2);
		void poly(int sides, float radius);
		void poly(int sides, float radius1, float radius2);
		void star(int sides, float innerRadius, float outerRadius);
		void star(int sides, const Vec2& radiusAndRatio);
		
		// 3D Primitives
		void box(float sz, Registration reg = CENTER);
		void box(float w, float h, float d, Registration reg = CENTER);
		void sphere(float sz);
		void sphere(float w, float h, float d);


		// Drawing Methods API
		void beginPath(PathRenderMode pathRenderMode = POLYGON);
		void endPath(bool isClosed = 1);
		void vertex(const Vec2f& vec);
		void vertex(const Vec3f& vec);
		void vertex(float x, float y);
		void vertex(float x, float y, float z);
		/****END 2D API****/

		// Lighting and Materials
		void setSpecular(const Col4f& spec);
		void setSpecular(const Col4f& spec);
		void setDiffuseMaterial(const Col4f& diff);
		void setAmbientMaterial(const Col4f& amb);


		//ProtoPath2 protoPath2;
		
		/***********BEGIN************
		       Save/Thread/Other
		***************************/
		// saving stuff
		virtual void render(int x = 0, int y = 0, int scaleFactor = 1); // eventually maybe make pure virtual (ehhh, maybe not)
		void save(std::string name = "img", int scaleFactor = 1);
		void threadSave(std::string name, int scaleFactor); // thread safe save with mutex locking
		std::mutex mtx;
		//void saveTiles(int rows, int columns);
		bool stitchTiles(std::string url, int tiles);
		/****END Save/Thread/Other****/

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


	inline void ProtoBaseApp::setProjection(ProjectionType projType){
		if (projType == PERSPECTIVE){
			P = glm::perspective(viewAngle, aspect, nearDist, farDist);
			//P = glm::frustum(left, right, bottom, top, nearDist, farDist);
			//translate(0, 0, -600);
			concat();
		}
		else {
			//ortho (T const &left, T const &right, T const &bottom, T const &top, T const &zNear, T const &zFar)
			P = glm::ortho(left, right, bottom, top, nearDist, farDist);
			concat();
		}
	}

	// perspective projection
	inline void ProtoBaseApp::setViewAngle(float viewAngle){
		this->viewAngle = viewAngle;
	}
	inline void ProtoBaseApp::setAspect(float aspect){
		this->aspect = aspect;
	}
	inline void ProtoBaseApp::setNearDist(float nearDist){
		this->nearDist = nearDist;
	}
	inline void ProtoBaseApp::setFarDist(float farDist){
		this->farDist = farDist;
	}

	// ortho projection
	inline void  ProtoBaseApp::setLeft(float left){
		this->left = left;
	}
	inline void  ProtoBaseApp::setRight(float right){
		this->right = right;
	}
	inline void  ProtoBaseApp::setBottom(float bottom){
		this->bottom = bottom;
	}
	inline void  ProtoBaseApp::setTop(float top){
		this->top = top;
	}

	inline void ProtoBaseApp::setShadowsOn(bool areShadowsOn) { //not used I believe
		this->areShadowsOn = areShadowsOn;
	}

	inline void ProtoBaseApp::shadowsOn(){
		areShadowsEnabled = true;
	}

	inline void ProtoBaseApp::shadowOff(){
		areShadowsEnabled = false;
	}


// Rendering display() switches
#define POINTS ProtoGeom3::POINTS
#define WIREFRAME ProtoGeom3::WIREFRAME
#define SURFACE ProtoGeom3::SURFACE

// make this intuitive
#define arcBallBegin arcballBegin
#define arcBallEnd arcballEnd
#define beginArcball arcballBegin
#define endArcball arcballEnd
#define beginArcBall arcballBegin
#define endArcBall arcballEnd

// immediate mode path plotting
#define beginShape beginPath // processing style
#define endShape endPath // processing style


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

#define background setBackground

}

//inline void ProtoBaseApp::setViewport(int width, int height){
//	glViewport(0, 0, width, height);
//}

#endif /* defined(PROTO_BASEAPP_H) */
