#include "ProtoImage.h"





// ProtoImage stuff
using namespace ijg;

ProtoImage::ProtoImage(){
}

ProtoImage::ProtoImage(int w, int h):
w(w), h(h){
    
}

ProtoImage::ProtoImage(const std::string& imageURL):
imageURL(imageURL){
}


ProtoImage::ProtoImage(const std::string& imageURL, int w, int h):
imageURL(imageURL), w(w), h(h)
{
    load(imageURL);
}
ProtoImage::ProtoImage(const std::string& imageURL, const Dim2f& dim):
imageURL(imageURL), dim(dim){
     load(imageURL);
}

void ProtoImage::load(const std::string& imageURL){
    this->imageURL = imageURL;
    
    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif // FREEIMAGE_LIB
    
	// initialize your own FreeImage error handler
    
	FreeImage_SetOutputMessage(FreeImageErrorHandler);
    
	// print version & copyright infos
    
	printf(FreeImage_GetVersion());
	printf("\n");
	printf(FreeImage_GetCopyrightMessage());
	printf("\n");
    
    
//	if(argc != 2) {
//		printf("Usage : LoadFromHandle <input file name>\n");
//		return 0;
//	}
    
	// initialize your own IO functions
    
	FreeImageIO io;
    
	io.read_proc  = myReadProc;
	io.write_proc = myWriteProc;
	io.seek_proc  = mySeekProc;
	io.tell_proc  = myTellProc;
    

    
	FILE *file = fopen(imageURL.c_str(), "rb");
    
	if (file != NULL) {
		// find the buffer format
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromHandle(&io, (fi_handle)file, 0);
        
		if(fif != FIF_UNKNOWN) {
			// load from the file handle
			FIBITMAP *dib = FreeImage_LoadFromHandle(fif, &io, (fi_handle)file, 0);
            
			// save the bitmap as a PNG ...
			const char *output_filename = "test.png";
            
			// first, check the output format from the file name or file extension
			FREE_IMAGE_FORMAT out_fif = FreeImage_GetFIFFromFilename(output_filename);
            
			if(out_fif != FIF_UNKNOWN) {
				// then save the file
				FreeImage_Save(out_fif, dib, output_filename, 0);
			}
            
			// free the loaded FIBITMAP
			FreeImage_Unload(dib);
		}
		fclose(file);
	}
    
	// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise();
#endif // FREEIMAGE_LIB

	}
    
