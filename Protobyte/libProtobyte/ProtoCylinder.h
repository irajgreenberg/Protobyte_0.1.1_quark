/*!  \brief  ProtoCylinder.h: (add brief description)
 ProtoCylinder.h
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

#ifndef Protobyte_dev_ProtoCylinder_cpp
#define Protobyte_dev_ProtoCylinder_cpp

#include <iostream>
#include "ProtoGeom3.h"

namespace ijg {
    
    class ProtoCylinder: public ProtoGeom3 {
    
    public:
        
        enum Registration {
            LEFT,
            CENTER,
            RIGHT
        };
        
        ProtoCylinder();
        ProtoCylinder(const Vec3f& pos, const Vec3f& rot, const Dim3f& size, const ProtoColor4f& col4, int sides, Registration registration = CENTER);
        ProtoCylinder(const Vec3f& pos, const Vec3f& rot, const Dim3f& size, const ProtoColor4f& col4, int sides, const Dim3f& size2, Registration registration = CENTER);
        ~ProtoCylinder();
        
        void setSides(int sides);
        int getSides() const;
        
        void setSize2(const Dim3f& size2);
        Dim3f getSize2() const;
        
    private:
        // fields
        int sides;
        Dim3f size2;
        Registration registration;
        
        // methods
        void calcVerts(); // overrides virtual method in base class
        void calcInds(); // overrides virtual method in base class
    };
    
    //implement getters/setters inline
    inline void ProtoCylinder::setSides(int sides){
        this->sides = sides;
    }
    
    inline int ProtoCylinder::getSides() const{
        return sides;
    }
    
    inline void ProtoCylinder::setSize2(const Dim3f& size2){
        this->size2 = size2;
    }
    
    inline Dim3f ProtoCylinder::getSize2() const{
        return size2;
    }
}

#endif // Protobyte_dev_ProtoCylinder_cpp
