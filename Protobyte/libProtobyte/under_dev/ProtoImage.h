/* 
 * File:   Image.h
 * Author: 33993405
 *
 * Created on April 14, 2013, 9:30 PM
 */

#ifndef PROTOIMAGE_H
#define	PROTOIMAGE_H

#include <string>
#include <vector>
#include "ProtoColor3.h"
#include "ProtoColor4.h"


namespace ijg {

    class ProtoImage {
    public:
        ProtoImage();
        ProtoImage(int w, int h);

        void load(const std::string& url);
        


    private:
        std::vector< Col3b > pixels3;
        std::vector< Col4b > pixels4;

    };

}

#endif	/* PROTOIMAGE_H */

