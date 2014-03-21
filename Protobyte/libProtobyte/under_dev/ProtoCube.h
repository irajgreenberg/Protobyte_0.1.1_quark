/*!  \brief  ProtoCube.h: non-regular cube implementation
 ProtoCube.h
 Protobyte Library v02
 
 Created by Ira on 10/26/13. (Happy Anniversary Bel!)
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

#ifndef PROTO_CUBE_H
#define	PROTO_CUBE_H

#include "ProtoGeom3.h"

namespace ijg {
    
    class ProtoCube : public ProtoGeom3 {
    public:
        ProtoCube();
        ProtoCube(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
                    const ProtoColor4f col4);
        
        ProtoCube(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
                    const ProtoColor4f col4, float textureScale);
        
        //        void init(); // temp override
        void calcVerts();
        void calcInds();
        
        // for testing only
        void calcVerts2();
        void calcInds2();
        
    private:

        
    };
}

#endif	// PROTO_CUBE_H

