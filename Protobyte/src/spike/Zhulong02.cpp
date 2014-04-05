#include "Zhulong02.h"





void Zhulong02::init() {

	setBackground(.18f, .1f, .085);

	// light0
	light0->setPosition(Vec3f(0, 0, 20));
	light0->setDiffuse(Col4f(1, 1, 1, 1.0));
	light0->setAmbient(Col4f(.3, .2, .2, 1.0));
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



	toroid = new ProtoToroid(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(60, 60, 60), Col4f(.4f, .5f, .75f, 1),
		37, 50, .8f, .02f, "metal_grate.jpg");
	toroid->setTextureScale(.35); // still need to implement
	toroid->textureOn();

	//ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, 
	//const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, 
	//const ProtoTransformFunction& transFuncObj, bool isClosed, const std::string& textureImageURL);

	//   ProtoSpline3(const std::vector<Vec3f>& controlPts, int interpDetail, bool isCurveClosed, float smoothness);
	Spline3 path();


	//std::vector<Vec3f> poses;
	// wind CCW around center

	/*
	const static int TUBULE_COUNT = 17;
	const static int TUBULE_RINGS = 3;
	int tubuleRingsIndices[TUBULE_RINGS];
	// 3 rings[1][6][10]
	Tube tubules[TUBULE_COUNT];
	*/
	tubuleRingsIndices[0] = 1;
	tubuleRingsIndices[1] = 6;
	tubuleRingsIndices[2] = 10;
	tubuleRingsIndices[3] = 12;
	tubuleRingsIndices[4] = 18;
	tubuleRingsIndices[5] = 25;

	float theta = 0.0f;
	float tubuleRadius = .13f;
	float tubuleLen = 2.875;
	int tubuleSegs = 12;
	float tubuleStep = tubuleLen / tubuleSegs;
	int tubuleInterpDetail = 6;
	int tubuleCounter = 0;
	int tubuleDetail = 18;


	// 1-6
	int editableRingCount = 1;
	//editableRingCount = TUBULE_RINGS;
	for (int i = 0; i < editableRingCount; ++i) { // rings
		theta = 0;
		for (int j = 0; j < tubuleRingsIndices[i]; ++j) { // tubules in ring
			std::vector<Vec3f> cps;
			Vec3 pos = Vec3f(sin(theta)*tubuleRadius*i*1.1, tubuleLen / 2 + random(-.3, .3), cos(theta)*tubuleRadius*i*1.1);
			for (int k = 0; k < tubuleSegs; ++k){
				if (k<3){
					cps.push_back(Vec3f(pos.x + random(-.12, .12), pos.y - tubuleStep*k, pos.z + random(-.12, .12)));
				}
				else {
					cps.push_back(Vec3f(pos.x + random(-.06, .06), pos.y - tubuleStep*k, pos.z + random(-.06, .06)));
				}
			} 
			// tapered
            tubules.push_back(Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .22), tubuleDetail, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(.93, .11), 1),true, "reptile3.jpg"));
            
            // straight
//            tubules.push_back(Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.03, .15), tubuleDetail,true));
            tubules.at(tubules.size() - 1).textureOn();
            tubules.at(tubules.size() - 1).setTextureScale(4.0);
            tubules.at(tubules.size() - 1).setColor(Col4f(.1f, .1f+random(.1f, .3f), .085f, 1));

			theta += TWO_PI / tubuleRingsIndices[i];
		}
	}



	std::vector<Vec3f> pts;
	float ht = 1.72f;
	int segs = 325;
	float step = ht/segs;
	theta = 0;
	float phi = 0;
	float radius = tubuleRadius*editableRingCount*.99f;
	for(int i = 0; i < segs; ++i){
		radius = tubuleRadius*editableRingCount*random(.98f, 1.01);
		//pts.push_back(Vec3f(sin(theta)*(radius + random(.02f, .04f)), -tubuleLen*.245 + step*.175f*i + cos(phi)*random(.05f, .175f), cos(theta)*(radius + random(.02f, .04f))));
		pts.push_back(Vec3f(sin(theta)*(radius + random(.02f, .04f)), -tubuleLen*.265 + step*.5375f*i + cos(phi)*random(.05f, .175f), cos(theta)*(radius + random(.02f, .04f))));
        
//        pts.push_back(Vec3f(random(-sin(theta)*(radius + random(.02f, .04f)), sin(theta)*(radius + random(.02f, .04f))), -tubuleLen*.265 + step*.5375f*i + cos(phi)*random(.05f, .175f), random(-cos(theta)*(radius + random(.02f, .04f)), cos(theta)*(radius + random(.02f, .04f)))));
        
        
		theta += PI/segs*random(60, 100);
		phi += PI / random(3, 6);
	}
	Spline3 s(pts, 4, false, 1);
	//tubulesWrap = Tube(s, .165, 4, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(.095, .19), 40), true);
	tubulesWrap = Tube(s, .7165, 18, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(.015, .04), 40), true, "leather2.jpg");
	tubulesWrap.setColor(Col4f(.03f, .025f, .02f, 1));
}


void Zhulong02::run() {
	pushMatrix();
	translate(0, 0, -50);
	rotate(frameCount*.02, 0, 1, 0);
	//glScalef(3, 3, 3);
	//toroid->display();
	//tube.display();
	popMatrix();

	pushMatrix();
	translate(0, -.03, -5.75);
	rotate(frameCount*.06, 0, .5, 0);
	//toroid->display();



	for (int i = 0; i <tubules.size(); ++i){
		tubules[i].display();
	}
	tubulesWrap.display();


	//for (int i = 0; i <spines.size(); ++i){
	//	spines[i].display();
	//}



	popMatrix();

	//sp3.display();
	//sp3.displayControlPts();
	//sp3.displayInterpPts();
}