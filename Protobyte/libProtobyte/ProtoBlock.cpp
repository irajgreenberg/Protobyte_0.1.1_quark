/*!  \brief  ProtoBlock.h: 3D block implementation
 ProtoBlock.h
 Protobyte Library v02
 
 Created by Ira on 4/06/13.
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

#include "ProtoBlock.h"


namespace ijg {

    std::ostream& operator<<(std::ostream& out, const ProtoBlock& ProtoBlock) {
        out << "pos: " << ProtoBlock.pos << "\n" <<
                "rot: " << ProtoBlock.rot << "\n" <<
                "size: " << ProtoBlock.size << "\n" <<
                "col4: " << ProtoBlock.col4;
        return out;
    }
}

using namespace ijg;

ProtoBlock::ProtoBlock() {
}

ProtoBlock::ProtoBlock(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
        const Col4f& col4):
ProtoGeom3(pos, rot, size, col4) {
    textureScale = 1.0;
    init();
}

ProtoBlock::ProtoBlock(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
        const Col4f& col4, const std::string& textureImageURL, float textureScale) :
ProtoGeom3(pos, rot, size, col4, textureImageURL, textureScale) {
    init();
}

//Uses uuplicate vertices to allow proper texture mapping

void ProtoBlock::calcVerts() {

    Vec3f vs[8];
    vs[0] = Vec3f(-.5, .5, .5);
    vs[1] = Vec3f(-.5, -.5, .5);
    vs[2] = Vec3f(.5, -.5, .5);
    vs[3] = Vec3f(.5, .5, .5);
    vs[4] = Vec3f(.5, .5, -.5);
    vs[5] = Vec3f(.5, -.5, -.5);
    vs[6] = Vec3f(-.5, -.5, -.5);
    vs[7] = Vec3f(-.5, .5, -.5);


    verts.resize(36);
    // FRONT
    verts.at(0) = ProtoVertex3(vs[0], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(1) = ProtoVertex3(vs[1], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 1.0 * textureScale));
    verts.at(2) = ProtoVertex3(vs[2], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));

    verts.at(3) = ProtoVertex3(vs[0], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(4) = ProtoVertex3(vs[2], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));
    verts.at(5) = ProtoVertex3(vs[3], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 0.0));

    // RIGHT
    verts.at(6) = ProtoVertex3(vs[3], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(7) = ProtoVertex3(vs[2], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 1.0 * textureScale));
    verts.at(8) = ProtoVertex3(vs[5], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));

    verts.at(9) = ProtoVertex3(vs[3], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(10) = ProtoVertex3(vs[5], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));
    verts.at(11) = ProtoVertex3(vs[4], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 0.0));

    // BACK
    verts.at(12) = ProtoVertex3(vs[4], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(13) = ProtoVertex3(vs[5], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 1.0 * textureScale));
    verts.at(14) = ProtoVertex3(vs[6], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));

    verts.at(15) = ProtoVertex3(vs[4], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(16) = ProtoVertex3(vs[6], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));
    verts.at(17) = ProtoVertex3(vs[7], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 0.0));

    //LEFT
    verts.at(18) = ProtoVertex3(vs[7], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(19) = ProtoVertex3(vs[6], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 1.0 * textureScale));
    verts.at(20) = ProtoVertex3(vs[1], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));

    verts.at(21) = ProtoVertex3(vs[7], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(22) = ProtoVertex3(vs[1], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));
    verts.at(23) = ProtoVertex3(vs[0], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 0.0));

    // TOP 
    verts.at(24) = ProtoVertex3(vs[7], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(25) = ProtoVertex3(vs[0], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 1.0 * textureScale));
    verts.at(26) = ProtoVertex3(vs[3], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));

    verts.at(27) = ProtoVertex3(vs[7], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(28) = ProtoVertex3(vs[3], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));
    verts.at(29) = ProtoVertex3(vs[4], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 0.0));

    //BOTTOM
    verts.at(30) = ProtoVertex3(vs[1], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(31) = ProtoVertex3(vs[6], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 1.0 * textureScale));
    verts.at(32) = ProtoVertex3(vs[5], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));

    verts.at(33) = ProtoVertex3(vs[1], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(0.0, 0.0));
    verts.at(34) = ProtoVertex3(vs[5], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 1.0 * textureScale));
    verts.at(35) = ProtoVertex3(vs[2], Col4f(1.0, 0.5, 0.0, 1.0), Tup2f(1.0 * textureScale, 0.0));
}

void ProtoBlock::calcInds() {
    inds.resize(12);
    for (int i = 0, j = 0; i < inds.size(); i++, j += 3) {
        inds.at(i) = Tup3i(j, j + 1, j + 2);
    }
}


