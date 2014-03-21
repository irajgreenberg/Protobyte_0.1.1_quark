//
//  ProtoVerletCube.cpp
//  Protobyte_dev
//
//  Created by Ira on 11/11/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "ProtoVerletCube.h"

using namespace ijg;

// deafult
ProtoVerletCube::ProtoVerletCube(){}

// 1 subdivision, 1 texture, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTension, const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode):
ProtoShape3(pos, rot, size, col4), subdivision(subdivision), springTension(springTension), textureImageURL(textureImageURL), anchorMode(anchorMode)
{
    Vec3f facePos, faceRot;
    for(int i=0; i<6; ++i) {
        switch(i){
            case 0: // FRONT
                facePos = Vec3f(0, 0, size.d/2);
                faceRot = Vec3f(0, 0, 0);
                break;
            case 1: // LEFT
                facePos = Vec3f(-size.w/2, 0, 0);
                faceRot = Vec3f(0, -HALF_PI, 0);
                break;
            case 2: // BACK
                facePos = Vec3f(0, 0, -size.d/2);
                faceRot = Vec3f(0, PI, 0);
                break;
            case 3: // RIGHT
                facePos = Vec3f(size.w/2, 0, 0);
                faceRot = Vec3f(0, HALF_PI, 0);
                break;
            case 4: // TOP
                facePos = Vec3f(0, size.h/2, 0);
                faceRot = Vec3f(-HALF_PI, 0, 0);
                break;
            case 5: // BOTTOM
                facePos = Vec3f(0, -size.h/2, 0);
                faceRot = Vec3f(HALF_PI, 0, 0);
                break;
        }
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(facePos, faceRot, size, col4, textureImageURL, subdivision.elem0, subdivision.elem1, springTension, anchorMode));
        verletSurfs[i]->setShininess(35);
    }
     init();
}

// 6 subdivisions, 1 texture, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTension, const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivisions[i].elem0, subdivisions[i].elem1, springTension, anchorMode));
    }
    init();
}

// 1 subdivisions, 6 textures, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTension, const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    Vec3f facePos, faceRot;
    for(int i=0; i<6; ++i) {
        switch(i){
            case 0: // FRONT
                facePos = Vec3f(0, 0, size.d/2);
                faceRot = Vec3f(0, 0, 0);
                break;
            case 1: // LEFT
                facePos = Vec3f(-size.w/2, 0, 0);
                faceRot = Vec3f(0, -HALF_PI, 0);
                break;
            case 2: // BACK
                facePos = Vec3f(0, 0, -size.d/2);
                faceRot = Vec3f(0, PI, 0);
                break;
            case 3: // RIGHT
                facePos = Vec3f(size.w/2, 0, 0);
                faceRot = Vec3f(0, HALF_PI, 0);
                break;
            case 4: // TOP
                facePos = Vec3f(0, size.h/2, 0);
                faceRot = Vec3f(-HALF_PI, 0, 0);
                break;
            case 5: // BOTTOM
                facePos = Vec3f(0, -size.h/2, 0);
                faceRot = Vec3f(HALF_PI, 0, 0);
                break;
        }
        
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(facePos, faceRot, size, col4, textureImageURLs[i], subdivision.elem0, subdivision.elem1, springTension, anchorMode));
        verletSurfs[i]->setShininess(75);
    }
    init();
}

// 6 subdivisions, 6 textures, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTension, const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivisions[i].elem0, subdivisions[i].elem1, springTension, anchorMode));
    }
    init();
}

// 1 subdivision, 1 texture, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTensions[6], const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivision.elem0, subdivision.elem1, springTensions[i], anchorMode));
    }
    init();
}

// 6 subdivisions, 1 texture, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTensions[6], const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivisions[i].elem0, subdivisions[i].elem1, springTensions[i], anchorMode));
    }
    init();
}

// 1 subdivisions, 6 textures, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTensions[6], const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivision.elem0, subdivision.elem1, springTensions[i], anchorMode));
    }
    init();
    
}

// 6 subdivisions, 6 textures, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTensions[6], const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivisions[i].elem0, subdivisions[i].elem1, springTensions[i], anchorMode));
    }
    init();
}

void ProtoVerletCube::init(){
    // ensure textures are off
    for(int i=0; i<6; ++i) {
        verletSurfs[i]->textureOff();
    }
}


void ProtoVerletCube::pulse(float amp, float freq){
    verletSurfs[0]->pulse(ProtoVerletSurface::FRONT, amp, freq);
    verletSurfs[1]->pulse(ProtoVerletSurface::LEFT, amp, freq);
    verletSurfs[2]->pulse(ProtoVerletSurface::BACK, amp, freq);
    verletSurfs[3]->pulse(ProtoVerletSurface::RIGHT, amp, freq);
    verletSurfs[4]->pulse(ProtoVerletSurface::TOP, amp, freq);
    verletSurfs[5]->pulse(ProtoVerletSurface::BOTTOM, amp, freq);
}

void ProtoVerletCube::pulse(float amps[6], float freq[6]){
    for(int i=0; i<6; ++i) {
        verletSurfs[i]->pulse();
    }
    
}



void ProtoVerletCube::display(RenderMode mode, float pointSize){
    for(int i=0; i<6; ++i) {
        verletSurfs[i]->display(mode, pointSize);
    }
}

void ProtoVerletCube::display(RenderMode mode0, RenderMode mode1, RenderMode mode2, RenderMode mode3, RenderMode mode4, RenderMode mode5, float pointSize){
    verletSurfs[0]->display(mode0, pointSize);
    verletSurfs[1]->display(mode1, pointSize);
    verletSurfs[2]->display(mode2, pointSize);
    verletSurfs[3]->display(mode3, pointSize);
    verletSurfs[4]->display(mode4, pointSize);
    verletSurfs[5]->display(mode5, pointSize);
}

void ProtoVerletCube::display(RenderMode modes[6], float pointSize){
    for(int i=0; i<6; ++i) {
        verletSurfs[i]->display(modes[i], pointSize);
    }
}

void ProtoVerletCube::display(RenderMode modes[6], float pointSizes[6]){
    for(int i=0; i<6; ++i) {
        verletSurfs[i]->display(modes[i], pointSizes[i]);
    }
}



void ProtoVerletCube::textureOn(){
    for(int i=0; i<6; ++i) {
        verletSurfs[i]->textureOn();
    }
}

void ProtoVerletCube::textureOff(){
    for(int i=0; i<6; ++i) {
        verletSurfs[i]->textureOff();
    }
}
