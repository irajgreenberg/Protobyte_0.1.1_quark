/*!  \brief  ProtoWorld2.h: (add brief description)
 ProtoWorld2.h
 Protobyte Library v02
 
 Created by Ira on 3/4/14.
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

#ifndef Protobyte_dev_OSX_2_ProtoWorld2_cpp
#define Protobyte_dev_OSX_2_ProtoWorld2_cpp

#include <iostream>
#include "ProtoGeom3.h"

namespace ijg {
    
    class ProtoWorld2 {
    
    public:
        ProtoWorld2();
        ~ProtoWorld2();
        
        void add(ProtoGeom3& obj);
        void remove();
        
        // only render objs if flagged renderable
        void display();
        
    private:
        
        std::vector<ProtoGeom3> objs;
        
    };
}

#endif // Protobyte_dev_OSX_2_ProtoWorld2_cpp
