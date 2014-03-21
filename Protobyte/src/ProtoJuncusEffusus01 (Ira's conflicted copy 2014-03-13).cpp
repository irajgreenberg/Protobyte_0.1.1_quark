/*!  \brief  ProtoJuncusEffusus01.h: Single wrapped starnd study
 ProtoJuncusEffusus01.h
 Protobyte Library v02

 Created by Ira on 3/3/14.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.

 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.

 This notice must be retained any source distribution.

 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */

#include "ProtoJuncusEffusus01.h"


using namespace ijg;


void ProtoJuncusEffusus01::init() {



	setBackground(.25f);

	// light0
	light0->setPosition(Vec3f(-5, 0, 20));
	light0->setDiffuse(Col4f(.3f, .1f, .1f, 1.0f));
	light0->setAmbient(Col4f(.3, .1, .1, 1.0));
	light0->setSpecular(Col4f(1, 1, 1, 1.0));
	light0->on();


	// light1
	light1->setPosition(Vec3f(0, -27, 20));
	light1->setDiffuse(Col4f(1, 0, 1, 1.0));
	light1->setAmbient(Col4f(.55, .55, .75, 1.0));
	light1->setSpecular(Col4f(1, .6, .8, 1.0));
	light1->on();

	light2->setPosition(Vec3f(50, -12, -30));
	light2->setDiffuse(Col4f(.7, .3, .6, 1.0));
	light2->setAmbient(Col4f(.5, .2, .2, 1.0));
	light2->setSpecular(Col4f(1, 1, 1, 1.0));
	light2->on();


	//   ProtoSpline3(const std::vector<Vec3f>& controlPts, int interpDetail, bool isCurveClosed, float smoothness);
	//Spline3 path();

	float theta = 0.0f;
	float tubuleRadius = 2.5;//8.73f;
	float tubuleLen = 2.875;
	int tubuleSegs = 9;
	float tubuleStep = tubuleLen / tubuleSegs;
	int tubuleInterpDetail = 2;//6;
	int tubuleDetail = 18;//18;



	std::vector<Vec3f> cps;

	Vec3 pos = Vec3f(0, tubuleLen / 2 + random(-.3, .3), 0);
	for (int k = 0; k < tubuleSegs; ++k){
		if (k < 3){
			cps.push_back(Vec3f(pos.x + random(-.22, .22), pos.y - tubuleStep*k, pos.z + random(-.22, .22)));
		}
		else {
			cps.push_back(Vec3f(pos.x + random(-.06, .06), pos.y - tubuleStep*k, pos.z + random(-.06, .06)));
		}
	}
	// tapered
	//            tubule = Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .08), tubuleDetail, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(tubuleRadius, .21), 1),true, "reptile3.jpg");

	// curvey
	tubule = Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .08), tubuleDetail, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleRadius, .21), 6), true, "reptile3.jpg");

	tubule.textureOn();
	tubule.setTextureScale(4.0);
	tubule.setShininess(104);
	tubule.setColor(Col4f(.1f, .1f + random(.1f, .3f), .085f, 1));




	//    
	std::vector<Vec3f> pts;
	float ht = 2.1f;
	int segs = 125;//325;
	float step = ht / segs;
	theta = 0;
	float phi = 0;
	float radius = .125f;
	float tubuleBuldgeMin = .55f, tubuleBuldgeMax = 1.95f;
	for (int i = 0; i < segs; ++i){
		//radius = tubuleRadius*random(.98f, 1.01);
		//pts.push_back(Vec3f(sin(theta)*(radius + random(.02f, .04f)), -tubuleLen*.245 + step*.175f*i + cos(phi)*random(.05f, .175f), cos(theta)*(radius + random(.02f, .04f))));
		//pts.push_back(Vec3f(sin(theta)*(radius), -tubuleLen*.5 + step*.8375f*i + cos(phi)*random(.05f, .175f), cos(theta)*(radius )));

		//        pts.push_back(Vec3f(random(-sin(theta)*(radius + random(.02f, .04f)), sin(theta)*(radius + random(.02f, .04f))), -tubuleLen*.265 + step*.5375f*i + cos(phi)*random(.05f, .175f), random(-cos(theta)*(radius + random(.02f, .04f)), cos(theta)*(radius + random(.02f, .04f)))));


		theta += PI / segs*random(60, 100);
		phi += PI / random(3, 6);
	}

	//trace("tubule.getVertices().size() =", tubule.getVertices().size());
	for (int i = 0; i < tubule.getVertices().size() - 2; ++i){
		// trace("tubule.getVertices() =", tubule.getVertices().at(i).pos);
		pts.push_back(tubule.getVertices().at(i).pos);
	}


	for (int i = 0; i < tubule.getInterleavedPrims().size(); i += 12){
		// trace("tubule.getVertices() =", tubule.getVertices().at(i).pos);
		float x = tubule.getInterleavedPrims().at(i);
		float y = tubule.getInterleavedPrims().at(i + 1);
		float z = tubule.getInterleavedPrims().at(i + 2);
		// pts.push_back(Vec3(x, y, z));
	}


	Spline3 s(pts, 2, false, .5);
	//tubulesWrap = Tube(s, .165, 4, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(.095, .19), 40), true);
	tubulesWrap = Tube(s, .03, 6/*12*/, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleBuldgeMin, tubuleBuldgeMax/*2.1*/), 40), true, "leather2.jpg");
	tubulesWrap.setColor(Col4f(.03f, .025f, .02f, 1));
	tubulesWrap.textureOn();


	shader = ProtoShader("phong.vert", "phong.frag");


}


void ProtoJuncusEffusus01::run() {
	setBackground(.25f);
	glClearColor(.25f, .25f, .25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//trace("In CONTROLLER RUN()");

	//    glFrustum(	GLdouble  	left,
	//     GLdouble  	right,
	//     GLdouble  	bottom,
	//     GLdouble  	top,
	//     GLdouble  	nearVal,
	//     GLdouble  	farVal);


	//shift and save to offscreen buffer
	//glViewport(0, 0, width, height);
	glViewport(0, 0, width, height);

	// test for tiling image output
	float nearClipPlane = .1f, farClipPlane = 500.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = (float)width / (float)height;

	gluPerspective(75, aspect, nearClipPlane, farClipPlane);
	//glFrustum(-0.1f, 0.1f, -.1f*aspect, .1f*aspect, .1, 300);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0, 0, 10, 0, 0, 0, 0, -1, 0);

	trace("frameCount =", frameCount);
    
    
    // this works as expected in Windows - begins at frame 0
    
    // apple implementation must use seperate thread
    if (frameCount == 40){
		drawToFrameBuffer();
	}

	shader.bind();
	//pushMatrix();
	translate(0, 0, -3);
	//rotate(frameCount*.06, 0, .5, 0);
	scale(1.3, 1.3, 1.3);
	tubule.display();

	tubulesWrap.display();
	shader.unbind();
}

void ProtoJuncusEffusus01::drawToFrameBuffer(){
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				trace("in drawToFrameBuffer");
				glClearColor(.25f, .25f, .25f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				//From: http://stackoverflow.com/questions/12157646/how-to-render-offscreen-on-opengl

				glViewport(-i*width, -j*height, 4 * width, 4 * height);

				shader.bind();
				pushMatrix();
				translate(0, 0, -6);
				//rotate(frameCount*.006, 0, .5, 0);
				scale(1.2, 1.2, 1.2);
				tubule.display();
				shader.unbind();
				tubulesWrap.display();
				popMatrix();

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
				std::stringstream stream;
#if defined (_WIN32) || defined(_WIN64)
                stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
				// c++ 11 conversion form num to string
				std::string url = "\\Users\\Ira\\Desktop\\ProtoJucnusEffusus01_stills\\capture_" + stream.str() + "_" + std::to_string(i*4+j) + "_.jpg";
#else
                stream << (ltm->tm_year + 1900) << "_" << (ltm->tm_mon + 1) << "_" << ltm->tm_mday << "_" << ltm->tm_hour << "_" << ltm->tm_min << "_" << ltm->tm_sec;
				// c++ 11 conversion form num to string
				std::string url = "/Users/33993405/Desktop/ProtoJucnusEffusus01_stills/capture_" + stream.str() + "_" + std::to_string(i*4+j) + "_.jpg";
                trace("url =", url);
#endif
                
				FreeImage_Save(FIF_JPEG, image, url.c_str(), 0);

				// Free resources
				FreeImage_Unload(image);


				// Return to onscreen rendering:
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			}
		}
}


void ProtoJuncusEffusus01::saveTiles(int rows, int columns){
//	// always based on width and height of winndow (for now)
//	// FROM http://stackoverflow.com/questions/5844858/how-to-take-screenshot-in-opengl
//
//	float cellW = width / columns;
//	float cellH = height / rows;
//	float total = width*columns;
//	float totalImageWidth = width*columns;
//	float totalImageHeight = height*rows;
//	float x = 0;// -totalImageWidth;
//	float y = 0;// totalImageHeight;
//
//	//using namespace std;
//	for (int i = 0; i < rows; ++i){
//		for (int j = 0; j < columns; ++j){
//			//glViewport(x + width*j, y + height*i, width, height);
//			time_t now = time(0);
//			tm ltm;
//			localtime_s(&ltm, &now);
//
//			// Make the BYTE array, factor of 3 because it's RBG.
//			unsigned char* pixels = new unsigned char[3 * width * height];
//
//			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//			glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, pixels);
//
//			// Convert to FreeImage format & save to file
//			FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
//
//
//			// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
//			std::stringstream stream;
//			stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
//			std::string url;
//#if defined(_WIN32) || defined (_WIN64)
//			url = "\\Users\\Ira\\Desktop\\ProtoJucnusEffusus01_stills\\capture_" + stream.str() + ".jpg";
//#else
//			url = "/Users/ira/Desktop/ProtoJucnusEffusus01_stills/capture_" + stream.str() + ".jpg";
//#endif
//
//			FreeImage_Save(FIF_JPEG, image, url.c_str(), 0);
//
//			// Free resources
//			FreeImage_Unload(image);
//			delete[] pixels;
//		}
//	}
}
