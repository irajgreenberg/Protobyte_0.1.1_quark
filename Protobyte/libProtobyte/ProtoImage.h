/* 
 * File:   Image.h
 * Author: 33993405
 *
 * Created on April 14, 2013, 9:30 PM
 */

#ifndef PROTOIMAGE_H
#define	PROTOIMAGE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "FreeImage.h"

#include <string>
#include <vector>
#include "ProtoDimension2.h"
#include "ProtoColor3.h"
#include "ProtoColor4.h"


namespace ijg {

    
    // ----------------------------------------------------------
    
    /**
     FreeImage error handler
     @param fif Format / Plugin responsible for the error
     @param message Error message
     */
    void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message);
    
    // ----------------------------------------------------------
    
    unsigned DLL_CALLCONV myReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle);
    unsigned DLL_CALLCONV myWriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle);
    int DLL_CALLCONV mySeekProc(fi_handle handle, long offset, int origin);
    long DLL_CALLCONV myTellProc(fi_handle handle);
    
    // ----------------------------------------------------------
    
    
    class ProtoImage {
    
    public:
        ProtoImage();
        ProtoImage(int w, int h);
        ProtoImage(const std::string& imageURL);
        ProtoImage(const std::string& imageURL, int w, int h);
        ProtoImage(const std::string& imageURL, const Dim2f& dim);

        void load(const std::string& imageURL);
        


    private:
        float w, h;
        Dim2f dim;
        std::vector< Col3b > pixels3;
        std::vector< Col4b > pixels4;
        std::string imageURL;

    };
    
    // ----------------------------------------------------------
    
    /**
     FreeImage error handler
     @param fif Format / Plugin responsible for the error
     @param message Error message
     */
    inline void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) {
        printf("\n*** ");
        if(fif != FIF_UNKNOWN) {
            printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
        }
        printf(message);
        printf(" ***\n");
    }
    
    // ----------------------------------------------------------
    
    inline  unsigned DLL_CALLCONV
    myReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
        return fread(buffer, size, count, (FILE *)handle);
    }
    
    inline  unsigned DLL_CALLCONV
    myWriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
        return fwrite(buffer, size, count, (FILE *)handle);
    }
    
    inline  int DLL_CALLCONV
    mySeekProc(fi_handle handle, long offset, int origin) {
        return fseek((FILE *)handle, offset, origin);
    }
    
    inline  long DLL_CALLCONV
    myTellProc(fi_handle handle) {
        return ftell((FILE *)handle);
    }
    
    // ----------------------------------------------------------


}

#endif	/* PROTOIMAGE_H */

