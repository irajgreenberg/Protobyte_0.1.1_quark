//
//  ProtoPlasm.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "ProtoPlasm.h"

using namespace ijg;


ProtoPlasm::ProtoPlasm(ProtoBaseApp* baseApp):
baseApp(baseApp), appWidth(1920), appHeight(1080), appTitle("Protobyte App")
{
    // instantiate world
    //world = std::unique_ptr<ProtoWorld>(new ProtoWorld(appWidth, appHeight));
    
    // init app and call init() and run() to activate functions in user defined BaseApp derived class
    initSFMLInit();
    initSFMLRun();
}

ProtoPlasm:: ProtoPlasm(int appWidth, int appHeight, std::string appTitle, ProtoBaseApp* baseApp):
appWidth(appWidth), appHeight(appHeight), appTitle(appTitle), baseApp(baseApp){
    // this->baseApp = baseApp;
    baseApp->setWidth(appWidth);
    baseApp->setHeight(appHeight);
    baseApp->setSize(Dim2i(appWidth, appHeight));    
    
    // Create GL context and call init() and run() to activate functions in user defined BaseApp derived class
    initSFMLInit();
    initSFMLRun();
}


void ProtoPlasm::initSFMLInit(){

//#if defined(_WIN32) || defined (_WIN64) 
//	glewExperimental = TRUE;
//	GLenum err = glewInit();
//	if (err != GLEW_OK)
//	{
//		//Problem: glewInit failed, something is seriously wrong.
//		std::cout << "glewInit failed, aborting." << std::endl;
//	}
//#endif
   
	
	
	baseApp->setFrameCount(0);
	baseApp->setFrameRate(60.0f);

	// Start GLFW setup  // NOTE: DO I need this??
	// for modern context handling
	//glfwInit();

  srand (static_cast <unsigned> (time(0)));
    
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    // uncomment for 3.2+ context (OS X)
    // need to check this on WIN
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    
    // anti-aliasing
    glfwWindowHint(GLFW_SAMPLES, 8);
    
    window = glfwCreateWindow(appWidth, appHeight, appTitle.c_str(), /*glfwGetPrimaryMonitor()*/NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
   
    // end GLFW setup
    
    
    // set gl states
    glClearColor(0, 0, 0, 1.0f);
    glShadeModel(GL_SMOOTH);
    // enable specualrity on textures
    glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
    glEnable(GL_LIGHTING);
    glFrontFace(GL_CCW); // default
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glDisable(GL_CULL_FACE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glShadeModel(GL_FLAT); // option
    glEnable(GL_COLOR_MATERIAL); // incorporates per vertex color with lights
    
    // global ambient unrelated to lights
    float globalAmbient[4] = {.3, .3, .3, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,  globalAmbient);
    
    // let glColor control diffues and ambient material values
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    
    //
    glEnable(GL_BLEND);
    //glBlendFunc(GL_DST_COLOR,GL_ZERO);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_DST_COLOR,GL_ZERO);
    //glBlendFunc (GL_ONE, GL_ONE);
    
    //glEnable(GL_ALPHA_TEST);
    //glAlphaFunc(GL_GREATER,0.0f);
    
    // for best antialiasing
    // http://bankslab.berkeley.edu/members/chris/AntiAliasing/AntiAliasingInOpenGL.html
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE); //  good for uniform scaling
    
    
    glClearStencil(0); // clear stencil buffer
    glClearDepth(1.0f); // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
    
    
    
    // World manages lighting and views (cameras)
    // instantiate singleton world
   // world = std::unique_ptr<ProtoWorld>(new ProtoWorld(appWidth, appHeight));
    
    // set default single world view
//world->setWorldView(ProtoWorld::SINGLE_VIEW);
    
  //  world->setWorldRotSpeed(Vec3f(1.3, 0, 0));
    
    std::unique_ptr<ijg::ProtoCamera> camera1(new ijg::ProtoCamera(Vec3f(0, 0, 4.9), Vec3f(0, 0, 0), ProtoBoundsf(0, 0,appWidth, appHeight)));
    std::unique_ptr<ijg::ProtoCamera> camera2(new ijg::ProtoCamera(Vec3f(0, 0, 4.9), Vec3f(0, 180, 0), ProtoBoundsf(0, 0,appWidth, appHeight)));
    std::unique_ptr<ijg::ProtoCamera> camera3(new ijg::ProtoCamera(Vec3f(0, 0, 4.9), Vec3f(-50, 30, 30), ProtoBoundsf(0, 0,appWidth, appHeight)));
    std::unique_ptr<ijg::ProtoCamera> camera4(new ijg::ProtoCamera(Vec3f(0, 0, 4.9), Vec3f(0, 124, 0), ProtoBoundsf(0, 0,appWidth, appHeight)));
    
    // Camera
    camera1->setProjection(75.0f, appWidth/appHeight, .1, 1000);
    camera2->setProjection(60.0f, appWidth/appHeight, .1, 1000);
    camera3->setProjection(110.0f, appWidth/appHeight, .1, 1000);
    camera4->setProjection(60.0f, appWidth/appHeight, .1, 1000);
    
    //camera1->setViewPort(0, 0, window.getSize().x/2, window.getSize().y/2);
    //    camera2->setViewPort(0, window.getSize().y/2, window.getSize().x/2, window.getSize().y/2);
    //    camera3->setViewPort(window.getSize().x/2, window.getSize().y/2, window.getSize().x/2, window.getSize().y/2);
    //    camera4->setViewPort(window.getSize().x/2, 0, window.getSize().x/2, window.getSize().y/2);
    //
   // world->add(std::move(camera1));
    //    world->add(std::move(camera2));
    //    world->add(std::move(camera3));
    //    world->add(std::move(camera4));
    
    // camera1->setViewPort(0, 0, appWidth, appHeight);
    // world->add(std::move(camera1));
    
    // Lights
    // Light 1
    //    std::unique_ptr<ijg::ProtoLight> lt0_ptr = std::unique_ptr<ijg::ProtoLight>(new ProtoLight());
    //    lt0_ptr->setShininess(128.0);
    //    lt0_ptr->setDiffuse(ProtoColor4f(1.0, .5, 0, 1.0));
    //    lt0_ptr->setSpecular(ProtoColor4f(1.0, 1.0, 1.0, 1.0));
    //    lt0_ptr->setAmbient(ProtoColor4f(.4, .4, .4, 1.0));
    //    lt0_ptr->setPosition(Vec3f(0, 0, -2.0));
    //    world->add(std::move(lt0_ptr));
    //
    //    // Light 2
    //    std::unique_ptr<ijg::ProtoLight> lt1_ptr = std::unique_ptr<ijg::ProtoLight>(new ProtoLight());
    //    lt1_ptr->setShininess(128.0);
    //    lt1_ptr->setDiffuse(ProtoColor4f(1.0, .5, 0, 1.0));
    //    lt1_ptr->setSpecular(ProtoColor4f(1.0, 1.0, 1.0, 1.0));
    //    lt1_ptr->setAmbient(ProtoColor4f(.4, .4, .4, 1.0));
    //    lt1_ptr->setPosition(Vec3f(-2, 2, 2.0));
    //    world->add(std::move(lt1_ptr));
    //
    //
    //    world->setLights();
    
    // fog starting settings thanks to: http://nehe.gamedev.net/tutorial/cool_looking_fog/19001/, http://user.xmission.com/~nate/tutors/fog.png
    
    // won't work with shaders
	GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };   // Storage For Three Types Of Fog
    GLuint fogfilter= 2;                    // Which Fog To Use
    GLfloat fogColor[4]= {0, 0, 0, 1.0f};      // Fog Color
    
    glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
    glFogf(GL_FOG_DENSITY, 0.3f);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
    glFogf(GL_FOG_START, -20);             // Fog Start Depth
    // was 70
    glFogf(GL_FOG_END, 110.0f);               // Fog End Depth
    glEnable(GL_FOG);                   // Enables GL_FOG
    
    // map geometry to window size
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glViewport(0, 0, appWidth, appHeight);
	//glMatrixMode(GL_MODELVIEW);
    
    // pass world to baseApp enabling user defined BaseApp derived class access
    // setWorld also initializes some baseApp states
    //std::cout << "world->fovAngle = " << world->fovAngle << std::endl;
    
    int w = 0;
    int h = 0;
    glfwGetFramebufferSize(window, &w, &h);
    std::cout << "Framewbuffer: w = " << w <<std::endl;
    std::cout << "FrameBuffer h = " << h <<std::endl;
    
                             
                             
    //baseApp->setWorld(std::move(world));
    // std::cout << "baseApp->world->fovAngle = " << baseApp->world->fovAngle << std::endl;
    
    // Activate init function in user derived class.n.
    baseApp->init();
}

// activate animation thread and run() function in user defined BaseApp derived class
void ProtoPlasm::initSFMLRun(){
    
    // Activate derived user class implementations of events:
    /*
     • run
     • mouse
     • keyboard
     */
    
    // clear screen
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    while (!glfwWindowShouldClose(window))
    {
        /*
         TO DO – fix timing issues with control for users:
         From: http://stackoverflow.com/questions/2182675/how-do-you-make-sure-the-speed-of-opengl-animation-is-consistent-on-different-ma
*/
        
        
        
        
        // Activate derived user class implementation.
		baseApp->setFrameCount(frameCount);
		//baseApp->runWorld();
        baseApp->run();

        
        // handle GLFW events
        
        // clear the buffers
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        // end the current frame (internally swaps the front and back buffers)
        //window->display();
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        frameCount++;
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

