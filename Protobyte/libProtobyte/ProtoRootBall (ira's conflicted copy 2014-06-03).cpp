#include "ProtoRootBall.h"
using namespace ijg;

ProtoRootBall::ProtoRootBall(){

}

// no texture
ProtoRootBall::ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const ProtoColor4f& col4, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii) :
	ProtoShape3(pos, rot, size, col4), rootCount(rootCount), rootSegments(rootSegments), turbulence(turbulence), rootRadii(rootRadii) {

	// no texture passed in: use white_tile
	for (int i = 0; i < rootCount; ++i){
		textureURLs.push_back("white_tile.jpg");
		textureScales.push_back(1);
		col4s.push_back(col4);
	}

	init();
}

// no texture, multi colors
ProtoRootBall::ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const std::vector<ProtoColor4f>& col4s, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii) :
	ProtoShape3(pos, rot, size, col4s), rootCount(rootCount), rootSegments(rootSegments), turbulence(turbulence), rootRadii(rootRadii) {

	// no texture passed in: use white_tile
	for (int i = 0; i < rootCount; ++i){
		textureURLs.push_back("white_tile.jpg");
		textureScales.push_back(1);
	}

	init();
}

// texture
ProtoRootBall::ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const ProtoColor4f& col4, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii, const std::string& textureURL, int textureScale) :
	ProtoShape3(pos, rot, size, col4), rootCount(rootCount), rootSegments(rootSegments), turbulence(turbulence), rootRadii(rootRadii) {

	// 1 texture passed in
	for (int i = 0; i < rootCount; ++i){
		if (i == 0) {
			textureURLs.push_back(textureURL);
			textureScales.push_back(textureScale);
		}
		else {
			textureURLs.push_back("white_tile.jpg");
			textureScales.push_back(1);
		}

		col4s.push_back(col4);
	}

	init();
}

// texture, multi-colors
ProtoRootBall::ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const std::vector<ProtoColor4f>& col4s, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii, const std::string& textureURL, int textureScale) :
	ProtoShape3(pos, rot, size, col4s), rootCount(rootCount), rootSegments(rootSegments), turbulence(turbulence), rootRadii(rootRadii) {

	// 1 texture passed in
	for (int i = 0; i < rootCount; ++i){
		if (i == 0) {
			textureURLs.push_back(textureURL);
			textureScales.push_back(textureScale);
		}
		else {
			textureURLs.push_back("white_tile.jpg");
			textureScales.push_back(1);
		}
	}

	init();
}

// multi-textures, multi-colors
ProtoRootBall::ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const std::vector<ProtoColor4f>& col4s, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii, const std::vector<std::string>& textureURLs, int textureScale) :
	ProtoShape3(pos, rot, size, col4s), rootCount(rootCount), rootSegments(rootSegments), turbulence(turbulence), rootRadii(rootRadii), textureURLs(textureURLs) {

	// multiple textures | single texture scale
	for (int i = 0; i < rootCount; ++i){
		if (i == 0) {
			textureScales.push_back(textureScale);
		}
		else {
			textureScales.push_back(1);
		}
	}

	init();

}

// multi-textures, multi-colors, multi-texture scales
ProtoRootBall::ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const std::vector<ProtoColor4f>& col4s, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii, const std::vector<std::string>& textureURLs, std::vector<int> textureScales) :
	ProtoShape3(pos, rot, size, col4s), rootCount(rootCount), rootSegments(rootSegments), turbulence(turbulence), rootRadii(rootRadii), textureURLs(textureURLs), textureScales(textureScales) {

	init();
}

void ProtoRootBall::init(){
	// default transform;
	transform = ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, ProtoTuple2f(random(.4, rootRadii.elem0), random(rootRadii.elem0, rootRadii.elem1)), 50);

	//float theta = 0;
	//float radius = .107;
	//Vec3f v(0, 0, 0);

	//for (int i = 0; i < rootCount; ++i){
	//	theta = 0;
	//	v = Vec3f(0, 0, 0);
	//	Vec3f spd(0, 0, 0);
	//	std::vector <Vec3> cps;
	//	cps.push_back(v);

	//	for (int j = 0; j < rootSegments; ++j){
	//		spd = Vec3(random(-turbulence*.1, turbulence*.1), random(-turbulence*.1, turbulence*.1), random(-turbulence*.1, turbulence*.1));
	//		v += spd + Vec3f(sin(theta)*random(-turbulence, turbulence), -sin(theta)*random(-turbulence, turbulence), cos(theta)*random(-turbulence, turbulence));
	//		cps.push_back(Vec3(v.x, v.y, v.z));
	//		if (v.mag() > size.w / 2.5f){
	//			float shift = (size.w / 2.5f) / v.mag();
	//			v *= shift;
	//			spd *= -(1 + random(-turbulence*.1, turbulence*.1));
	//		}

	//		theta += PI / 15.0f;
	//	}

	//	// default root spline
	//	rootSplines.push_back(Spline3(cps, 7, false, .5));
	//}

	update();
}

// called by init & after state changes
void ProtoRootBall::update(){
	// clear roots vector
	if (roots.size() > 0){
		roots.clear();
	}
	float theta = 0;
	float radius = .107;
	Vec3f v(0, 0, 0);

	for (int i = 0; i < rootCount; ++i){
		theta = 0;
		v = Vec3f(0, 0, 0);
		Vec3f spd(0, 0, 0);
		std::vector <Vec3> cps;
		cps.push_back(v);

		for (int j = 0; j < rootSegments; ++j){
			spd = Vec3(random(-turbulence*.1, turbulence*.1), random(-turbulence*.1, turbulence*.1), random(-turbulence*.1, turbulence*.1));
			v += spd + Vec3f(sin(theta)*random(-turbulence, turbulence), -sin(theta)*random(-turbulence, turbulence), cos(theta)*random(-turbulence, turbulence));
			cps.push_back(Vec3(v.x, v.y, v.z));
			if (v.mag() > size.w / 2.5f){
				float shift = (size.w / 2.5f) / v.mag();
				v *= shift;
				spd *= -(1 + random(-turbulence*.1, turbulence*.1));
			}

			theta += PI / 15.0f;
		}

		rootSplines.push_back(Spline3(cps, 7, false, .5));
		
		//const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed
		roots.push_back(ProtoTube(Vec3f(), Vec3f(), Dim3f(1), col4s.at(i), rootSplines.at(i), .09, 12, transform, false, textureURLs.at(i)));
		roots.at(i).textureOn();
		roots.at(i).setTextureScale(textureScales.at(i));
	}
}

void ProtoRootBall::display(Geom3::RenderMode render, float pointSize){
	for (int i = 0; i < rootCount; ++i){
		roots.at(i).display(render, pointSize);
	}
}