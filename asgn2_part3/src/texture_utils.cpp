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
    generate(GL_RGBA, false);
}

int Texture::generate_white_is_transparent(){
    generate(GL_RGBA, true);
}

//returns 1 if success, 0 otherwise
int Texture::generate(GLenum format, bool white_is_transparent){
    image = new Image();
    if(image == NULL) return 0;

    int res = ImageLoad(filename, image, white_is_transparent);
    if(!res) return 0;

    glBindTexture(GL_TEXTURE_2D, texture_id);
	if(USE_MIPMAP){
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		//GLint gluBuild2DMipmaps(GLenum  target,  GLint  internalFormat,  
		//GLsizei  width,  GLsizei  height,  GLenum  format,  GLenum  type,  const void *  data);
		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, image->sizeX, image->sizeY, format, GL_UNSIGNED_BYTE, image->data );
	}
	else{
		//set parameters
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

		// 2d texture, level of detail 0 (normal), RGBA, x size from image, y size from image, 
		// border 0 (normal), format, unsigned byte data, and finally the data itself.
        // Specifies the level-of-detail number. Level 0 is the base image level. mip maps

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0, format, GL_UNSIGNED_BYTE, image->data);
	}

    return 1;
}

int ImageLoad(std::string filename, Image *image, bool white_is_transparent) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    char * buffer; //to temporarily hold RGB data from file

    // make sure the file is there.
    if ((file = fopen(filename.c_str(), "rb"))==NULL){
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

    //allocate mem for buffer and image data
    int size_buffer = image->sizeX * image->sizeY * 3;
    buffer = (char *) malloc(size_buffer); //for exact RGB as the image is

    // calculate the size (4 bytes per pixel).
    size = image->sizeX * image->sizeY * 4;
    image->data = (char *) malloc(size); //to store RGBA
    
    if (buffer == NULL || image->data == NULL) {
	   printf("Error allocating memory for color-corrected image data");
	   return 0;	
    }

    //read into temp buffer
    if ((i = fread(buffer, size_buffer, 1, file)) != 1) {
	   printf("Error reading image data from %s.\n", filename.c_str());
	   return 0;
    }

    //correct adjust GRB => RGB
    for (i=0;i<size_buffer;i+=3) {
	   temp = buffer[i];
	   buffer[i] = buffer[i+1];
	   buffer[i+1] = temp;
    }

    //Now store into image->data with alpha value default 1
    for (int s=0, d=0;s<size_buffer;s+=3, d+=4){
        image->data[d] = buffer[s];
        image->data[d+1] = buffer[s+1];
        image->data[d+2] = buffer[s+2];
        if(white_is_transparent){
            if(image->data[d] == -1 && image->data[d+1] == -1 && image->data[d+2] == -1){
                image->data[d+3] = 0;
            }
            else{
                image->data[d+3] = 255;
            }
        }
        else{
            image->data[d+3] = 255;
        }
    }

    //free the temp buffer
    free(buffer);
    // we're done.
    return 1;
}

//components 1,2,3 are x,y,z respectively
void calculate_normal(GLdouble a1, GLdouble a2, GLdouble a3,
                          GLdouble b1, GLdouble b2, GLdouble b3,
                          GLdouble c1, GLdouble c2, GLdouble c3,
                          GLdouble * normal){
    GLdouble u1 = b1 - a1;
    GLdouble u2 = b2 - a2;
    GLdouble u3 = b3 - a3;

    GLdouble v1 = c1 - b1;
    GLdouble v2 = c2 - b2;
    GLdouble v3 = c3 - b3;

    normal[0] = (u2*v3 - u3*v2);
    normal[1] = (u3*v1 - u1*v3);
    normal[2] = (u1*v2 - u2*v1); //done
}

void set_optimus_material(){
    GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 128.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void set_wall_material(){
    GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
    // GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat shininess[] = { 30.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void set_glass_material(){
    GLfloat mat_ambient[] = { 0, 0, 0, 0.2 };
    GLfloat mat_diffuse[] = { 0, 0, 0, 0.2 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}