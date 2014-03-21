/*!  \brief  ProtoVerletDome.h: Verlet surface implementation
 Protobyte Library v02
 
 Created by Ira on 11/20/13.
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


#ifndef PROTO_VERLETDOME_H
#define	PROTO_VERLETDOME_H

#include "ProtoGeom3.h"
#include "ProtoImage.h"
#include "ProtoVerletStick.h"
#include "ProtoTexture.h"

namespace ijg {

class ProtoVerletDome : public ProtoGeom3 {
    
public:
    
    enum AnchorModeEnum {
        ALL_CORNERS,
        ALL_EDGES,
        TOP_CORNER_LEFT,
        TOP_CORNER_RIGHT,
        BOTTOM_CORNER_LEFT,
        BOTTOM_CORNER_RIGHT,
        TOP_EDGE,
        BOTTOM_EDGE,
        LEFT_EDGE,
        RIGHT_RIGHT,
        NO_ANCHORS
    };
    
    enum Orientation {
        FRONT,
        LEFT,
        BACK,
        RIGHT,
        TOP,
        BOTTOM
    };
    
    
    
    
    // cstrs
    ProtoVerletDome();
    ProtoVerletDome(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, int rings, int spines, float tension, AnchorModeEnum anchorMode=ALL_CORNERS);
    
    ProtoVerletDome(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, const std::string& textureImageURL, int rings, int spines, float tension, AnchorModeEnum anchorMode=ALL_CORNERS);
    
    
    
    void nudge(int index);
    
    
    // setters/getters (inline below)
    void setRingCount(int ringCount);
    int getRingCount() const;
    
    void setSpineCount(int spineCount);
    int getSpineCount() const;
    
    void setTension(float tension);
    float getTension() const;
    
    // TEST
    void pulse(Orientation face=FRONT, float amp=1, float freq = Math::PI/180.0);
    void setMeshColor(const Col4f& meshCol);
    
private:
    
    Vec3f posOld;
    int ringCount, spineCount;
    float tension;
    
    int centroidIndex;
    float pulseTheta;
    
    std::string textureImageURL;
    
    /* vector of balls (1d will store 2d data)
     shared_ptrs because balls are
     connected to multiple lines */
    std::vector< std::shared_ptr<ProtoVerletBall> >  balls;
    
    // vector of sticks
    std::vector< std::unique_ptr<ProtoVerletStick> >  sticks;
    
    void calcVerts(); // overrides virtual method in base class
    void calcInds(); // overrides virtual method in base class
    
    ProtoTexture texture;
    ProtoImage textureImage;
    Col4f meshColor;
    
    AnchorModeEnum anchorMode;
    
};
    
    // inline implementation
    
    inline void ProtoVerletDome::setRingCount(int ringCount){
        this->ringCount = ringCount;
    }
    inline int ProtoVerletDome::getRingCount() const{
        return ringCount;
    }
    
    inline void ProtoVerletDome::setSpineCount(int spineCount){
        this->spineCount = spineCount;
    }
    inline int ProtoVerletDome::getSpineCount() const{
        return spineCount;
    }
    
    inline void ProtoVerletDome::setTension(float tension){
        this->tension = tension;
    }
    inline float ProtoVerletDome::getTension() const{
        return tension;
    }
    
    
    
#define ALL_EDGES ProtoVerletDome::ALL_EDGES
#define ALL_CORNERS ProtoVerletDome::ALL_CORNERS
#define TOP_EDGE ProtoVerletDome::TOP_EDGE
#define BOTTOM_EDGE ProtoVerletDome::BOTTOM_EDGE
    
}

#endif	/* PROTO_VERLETDOME_H */

