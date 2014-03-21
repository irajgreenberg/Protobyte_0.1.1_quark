/*!  \brief  ProtoVerletSurface.h: Verlet surface implementation
 Protobyte Library v02
 
 Created by Ira on 6/5/13.
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


#ifndef PROTO_VERLETSURFACE_H
#define	PROTO_VERLETSURFACE_H

#include "ProtoGeom3.h"
#include "ProtoImage.h"
#include "ProtoVerletStick.h"
#include "ProtoTexture.h"

namespace ijg {
    
    
    // forward declare & create namespace safe shortname
    class ProtoVerletSurface;
    typedef ProtoVerletSurface VerletSurface;
    
    class ProtoVerletSurface : public ProtoGeom3 {
        
        
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
        ProtoVerletSurface();
        ProtoVerletSurface(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, int rowCount, int columnCount, float tension, AnchorModeEnum anchorMode=ALL_CORNERS);
        
        ProtoVerletSurface(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, const std::string& textureImageURL, int rowCount, int columnCount, float tension, AnchorModeEnum anchorMode=ALL_CORNERS);
        
        
        
        void nudge(int index);
    
        
        // setters/getters (inline below)
        void setRowCount(int rowCount);
        int getRowCount() const;
        
        void setColumnCount(int columnCount);
        int getColumnCount() const;
        
        void setTension(float tension);
        float getTension() const;
        
        // TEST
        void pulse(Orientation face=FRONT, float amp=1, float freq = PI/180.0);
        void setMeshColor(const Col4f& meshCol);
        
    private:
        
        Vec3f posOld;
        int rowCount, columnCount;
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
    
    inline void ProtoVerletSurface::setRowCount(int rowCount){
        this->rowCount = rowCount;
    }
    inline int ProtoVerletSurface::getRowCount() const{
        return rowCount;
    }
    
    inline void ProtoVerletSurface::setColumnCount(int columnCount){
        this->columnCount = columnCount;
    }
    inline int ProtoVerletSurface::getColumnCount() const{
        return columnCount;
    }
    
    inline void ProtoVerletSurface::setTension(float tension){
        this->tension = tension;
    }
    inline float ProtoVerletSurface::getTension() const{
        return tension;
    }



    #define ALL_EDGES ProtoVerletSurface::ALL_EDGES
    #define ALL_CORNERS ProtoVerletSurface::ALL_CORNERS
    #define TOP_EDGE ProtoVerletSurface::TOP_EDGE
    #define BOTTOM_EDGE ProtoVerletSurface::BOTTOM_EDGE

}

#endif	/* PROTO_VERLETSURFACE_H */

