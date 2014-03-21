/*!  \brief  ProtoCylinder.cpp: (add brief description)
 ProtoCylinder.cpp
 Protobyte Library v02
 
 Created by Ira on 12/23/13.
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

#include "ProtoCylinder.h"

using namespace ijg;

// default cstr
ProtoCylinder::ProtoCylinder() {
    
}

ProtoCylinder::ProtoCylinder(const Vec3f& pos, const Vec3f& rot, const Dim3f& size, const ProtoColor4f& col4, int sides, Registration registration):
ProtoGeom3(pos, rot,size, col4), sides(sides), registration(registration)
{
    init();
}


ProtoCylinder::ProtoCylinder(const Vec3f& pos, const Vec3f& rot, const Dim3f& size, const ProtoColor4f& col4, int sides, const Dim3f& size2, Registration registration):ProtoGeom3(pos, rot,size, col4), sides(sides), size2(size2), registration(registration)
{
    init();
}


void ProtoCylinder::calcVerts() {
    // pack terminals up front in 0, 1 positions
    
    float theta = 0;
    float x = 0;
    float y = 0;
    float z = 0;
    switch (registration) {
        case LEFT:
            // terminals
            verts.push_back(ProtoVertex3(Vec3f(0, 0, 0),
                                        ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
            verts.push_back(ProtoVertex3(Vec3f(0, size.h, 0),
                                        ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
            for(int i=0; i<sides; ++i){
                z = cos(theta)*size.d;
                x = sin(theta)*size.w;
                verts.push_back( ProtoVertex3(Vec3f(x, y, z),
                                              ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
                
                verts.push_back( ProtoVertex3(Vec3f(x, size.h, z),
                                              ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0,0)));
                theta += TWO_PI/sides;
            }
            break;
        case CENTER:
            //terminals
            verts.push_back(ProtoVertex3(Vec3f(-size.w/2, 0, 0),
                                        ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
            verts.push_back(ProtoVertex3(Vec3f(size.w/2, 0, 0),
                                        ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
            for(int i=0; i<sides; ++i){
                y = cos(theta)*size.h;
                z = sin(theta)*size.d;
                verts.push_back( ProtoVertex3(Vec3f(-size.w/2, y, z),
                                              ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
                
                verts.push_back( ProtoVertex3(Vec3f(x+size.w/2, y, z),
                                              ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0,0)));
                theta += TWO_PI/sides;
            }
            break;
        case RIGHT:
            //terminals
            verts.push_back(ProtoVertex3(Vec3f(0, 0, 0),
                                        ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
            verts.push_back(ProtoVertex3(Vec3f(-size.w, 0, 0),
                                        ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
            for(int i=0; i<sides; ++i){
                y = cos(theta)*size.h;
                z = sin(theta)*size.d;
                verts.push_back( ProtoVertex3(Vec3f(0, y, z),
                                              ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
                
                verts.push_back( ProtoVertex3(Vec3f(-size.w, y, z),
                                              ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0,0)));
                theta += TWO_PI/sides;
            }
            
            break;
            
        default:
            break;
    }
    
}


void ProtoCylinder::calcInds() {
    // caps
    for(int i=0; i<sides; ++i) {
        int j = 2+i*2;
        int k = 2+i*2+1;
        
        // left cap
        if(i<sides-1){
            inds.push_back(ProtoTuple3i(0, j, j+2));
        } else {
            inds.push_back(ProtoTuple3i(0, j, 2));
        }
        
        // right cap
        if(i<sides-1){
            inds.push_back(ProtoTuple3i(1, k, k+2));
        } else {
            inds.push_back(ProtoTuple3i(1, k, 3));
        }
        
        // sides
        if(i<sides-1){
            inds.push_back(ProtoTuple3i(j, k, k+2));
            inds.push_back(ProtoTuple3i(j, k+2, j+2));
        } else {
            inds.push_back(ProtoTuple3i(j, k, 3));
            inds.push_back(ProtoTuple3i(j, 3, 2));
        }

    }
}

// dstr
ProtoCylinder::~ProtoCylinder() {
    
}
