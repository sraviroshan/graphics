#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdlib>
#include "gl_framework.hpp"
#include "texture_utils.h"
#define USE_MIPMAP false
Image::Image(){
    sizeY = 0;
    sizeX = 0;
    data = NULL;
}

Image::~Image(){
    if(data != NULL) free(data);
}

Texture::Texture(GLuint tex_id, std::string fname){
    filename = fname;
    texture_id = tex_id;
    image = NULL;
}

Texture::~Texture(){
    if(image!=NULL) delete(image);
}

int Texture::generate(){
    generate(GL_RGB);
}

//returns 1 if success, 0 otherwise
int Texture::generate(GLenum format){
    image = new Image();
    if(image == NULL) return 0;

    int res = ImageLoad(filename, image);
    if(!res) return 0;

    glBindTexture(GL_TEXTURE_2D, texture_id);
	if(USE_MIPMAP){
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		//GLint gluBuild2DMipmaps(GLenum  target,  GLint  internalFormat,  
		//GLsizei  width,  GLsizei  height,  GLenum  format,  GLenum  type,  const void *  data);
		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image->sizeX, image->sizeY, format, GL_UNSIGNED_BYTE, image->data );
	}
	else{
		//set parameters
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

		// 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
		// border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
		glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, format, GL_UNSIGNED_BYTE, image->data);
	}

    return 1;
}

int ImageLoad(std::string filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename.c_str(), "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename.c_str());
	return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename.c_str());
	return 0;
    }
    printf("Width of %s: %lu\n", filename.c_str(), image->sizeX);
    
    // read the height 
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename.c_str());
	return 0;
    }
    printf("Height of %s: %lu\n", filename.c_str(), image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename.c_str());
	return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename.c_str(), planes);
	return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename.c_str());
	return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename.c_str(), bpp);
	return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename.c_str());
	return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb) grb
	temp = image->data[i];
	image->data[i] = image->data[i+1];
	image->data[i+1] = temp;
    unsigned int a = (unsigned char) image->data[i];
    //printf("%u ", a);
    }
    
    // we're done.
    return 1;
}
