/*!  \brief  ProtoToroid.cpp: Toroid implementation
 ProtoToroid.h
 Protobyte Library v02
 
 Created by Ira on 7/23/13.
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

#include "ProtoToroid.h"


using namespace ijg;

ProtoToroid::ProtoToroid() {}

ProtoToroid::ProtoToroid(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, int ringCount, int ringDetail, float ringRadius, float ringThickness):
ProtoGeom3(pos, rot, size, col4), ringCount(ringCount), ringDetail(ringDetail), ringRadius(ringRadius), ringThickness(ringThickness) {
    
    init();
}

ProtoToroid::ProtoToroid(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4,
            int ringCount, int ringDetail, float ringRadius, float ringThickness, const std::string& textureImageURL):
ProtoGeom3(pos, rot, size, col4, textureImageURL), ringCount(ringCount), ringDetail(ringDetail), ringRadius(ringRadius), ringThickness(ringThickness) {
    init();
}



void ProtoToroid::calcVerts() {
   // std::cout << "tex2 = " << tex2 << std::endl;
    // vertices
    float x, y, z/*, u, v*/;
    float phi = 0; // ring rotations
    for (int i = 0/*, k=0*/; i < ringCount; i++) {
        float theta = 0;
        // START CALCULATE VERTICES
        for (int j = 0; j < ringDetail; j++) {
            // 1.  Z rotation for inital ring
            x = float(ringRadius + (cos(theta) - sin(theta)) * ringThickness)*size.w/2;
            y = float((sin(theta) + cos(theta)) * ringThickness)*size.h/2;
            z = 0;

            // 2.  y rotation to place rings
            float x2 = float(z * cos(phi) - x * sin(phi));
            float z2 = float(z * sin(phi) + x * cos(phi));


//            toroid calc (**TO DO**)
//            http://www.siggraph.org/education/materials/HyperGraph/mapping/torustx.htm
//            [Note: p = Pi = 3.141592. Define q as the angle from the X axis (0 <= q <= 2p) and
//            f as the angle from the Z axis (0.0 <= f <= p).]
//            Then, with R as the inner radius and r as the outer radius:
//            X = (R + r cos (2 pv)) cos (2 pu)
//            Y = r sin (2 pv)
//            Z = (R + r cos (2 pv)) sin (2 pu)
//        Then:
//            // toroid uv map coord
//            v = arccos (Y/R)/2p
//            u = [arccos ((X/(R + r*cos(2 pv))]2p
            
                          
                          // fill vertices with floats
            verts.push_back( ProtoVertex3(Vec3f(x2, y, z2), 
                        ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(z2/(size.h/2), x2/(size.w/2))));
             //std::cout << "Vec3f(x2, y, z2) = " << Vec3f(x2, y, z2) << std::endl;

            theta += float(PI * 2 / ringDetail);
        }
        phi += float(PI * 2 / ringCount);
    }
    
}

void ProtoToroid::calcInds() {
    // indices
    for (int i = 0; i < ringCount; i++) {
        for (int j = 0; j < ringDetail; j++) {

            int i0 = i * ringDetail + j;
            int i1 = (i + 1) * ringDetail + j;
            int i2 = i * ringDetail + j + 1;
            int i3 = (i + 1) * ringDetail + j + 1;
            int i4 = j;
            int i5 = i*ringDetail;
            //int i6 = ringDetail + j + 1; // not used
            int i7 = (i + 1) * ringDetail;
            int i8 = j + 1;


            if (i < ringCount - 1) {
                if (j < ringDetail - 1) {
                    inds.push_back(ProtoTuple3i(i0, i2, i3));
                    inds.push_back(ProtoTuple3i(i0, i3, i1));

                } else {
                    // j+1 = 0
                    inds.push_back(ProtoTuple3i(i0, i5, i7));
                    inds.push_back(ProtoTuple3i(i0, i7, i1));
                }
            } else {
                if (j < ringDetail - 1) {
                    //i+1 = 0// HERE
                    inds.push_back(ProtoTuple3i(i0, i2, i8));
                    inds.push_back(ProtoTuple3i(i0, i8, i4));

                } else {
                    //i+1 =0, j+1 = 0
                    inds.push_back(ProtoTuple3i(i0, i5, 0));
                    inds.push_back(ProtoTuple3i(i0, 0, i4));
                }
            }
        }
    }
}


