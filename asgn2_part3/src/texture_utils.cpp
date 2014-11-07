#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <fstream>
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

void keyframe_t::write(string filename){
    ofstream myfile;
    myfile.open (filename.c_str(), ios::out | ios::app);

    myfile << camera_no << " ";

    myfile << rotation_angle << " "; //angle for rotation about axis
    myfile << body_rotation_x << " "; //rotate body about x axis
    myfile << body_rotation_y << " "; //rotate body about x axis
    myfile << body_rotation_z << " "; //rotate body about x axis
    myfile << back_weel_slab_rotation << " "; //rotation of back weel slab bout x axis
    myfile << solder_rotation_zl << " "; //left solder rotation angle about z axis
    myfile << solder_rotation_yl << " "; //left solder rotation angle about y axis
    myfile << solder_rotation_xl << " "; // left solder rotation angle about x axis
    myfile << elbows_rotation_l << " "; //left elbows rotarion angle about z axis
    myfile << solder_rotation_zr << " "; // right solder rotation angle about z axis
    myfile << solder_rotation_yr << " "; // right solder rotation angle about y axis
    myfile << solder_rotation_xr << " "; // right solder rotation angle about x axis
    myfile << elbows_rotation_r << " "; //right elbows rotarion angle about z axis
    myfile << waist_rotation << " "; // rotation of waist about y axis
    myfile << upper_body_rotation << " "; //rotation of upper body about x axis
    myfile << lower_leg_rotation_l << " "; //rotation of left lower leg about x axis
    myfile << lower_leg_rotation_r << " "; //rotation of right lower leg about x axis
    myfile << front_weel_slab_rotation << " "; //rotarion of slab contain weel around x axis
    myfile << uper_leg_rotation_xl << " "; //rotation of uper left leg about x axis
    myfile << uper_leg_rotation_zl << " "; //rotation of uper left leg about z axis
    myfile << uper_leg_rotation_xr << " "; //rotation of uper right leg about x axis
    myfile << uper_leg_rotation_zr << " "; //rotation of uper right leg about z axis
    myfile << hood_feet_rotation_xl1 << " "; //rotation of left whole feet about x axis
    myfile << hood_feet_rotation_xl2 << " "; //rotation of left uper feet about x axis
    myfile << hood_feet_rotation_xr1 << " "; //rotation of right whole feet about x axis
    myfile << hood_feet_rotation_xr2 << " "; //rotation of right uper feet about x axis
    myfile << throat_translate_y << " "; //translation of throat along y axis
    myfile << truck_ceiling_rotation << " "; //rotation of truck ceilig about x axis
    myfile << front_glass_rotation << " "; //totation of fron glass bout x axis
    myfile << side_gate_rotation << " "; //side gate rotation about x axis
    myfile << weel_rotation << " "; //roatation of weel about z axis
    myfile << forword_backword_movement_z << " "; // translate whole body along z axis
    myfile << forword_backword_movement_x << " "; // translate whole body along x axis

    myfile << vertical_movement << " "; // vertical movement of transformer(independent)

    myfile << headlight_on << " ";  // whether headlight on (decide which texture to load)
    myfile << lighting_enabled << " ";
    myfile << light0_enabled << " ";
    myfile << light1_enabled << endl;
    myfile.close();
}

bool keyframe_t::read(ifstream &myfile){
    if(!(myfile >> camera_no)) return false;

    myfile >> rotation_angle ; //angle for rotation about axis
    myfile >> body_rotation_x ; //rotate body about x axis
    myfile >> body_rotation_y ; //rotate body about x axis
    myfile >> body_rotation_z ; //rotate body about x axis
    myfile >> back_weel_slab_rotation ; //rotation of back weel slab bout x axis
    myfile >> solder_rotation_zl ; //left solder rotation angle about z axis
    myfile >> solder_rotation_yl ; //left solder rotation angle about y axis
    myfile >> solder_rotation_xl ; // left solder rotation angle about x axis
    myfile >> elbows_rotation_l ; //left elbows rotarion angle about z axis
    myfile >> solder_rotation_zr ; // right solder rotation angle about z axis
    myfile >> solder_rotation_yr ; // right solder rotation angle about y axis
    myfile >> solder_rotation_xr ; // right solder rotation angle about x axis
    myfile >> elbows_rotation_r ; //right elbows rotarion angle about z axis
    myfile >> waist_rotation ; // rotation of waist about y axis
    myfile >> upper_body_rotation ; //rotation of upper body about x axis
    myfile >> lower_leg_rotation_l ; //rotation of left lower leg about x axis
    myfile >> lower_leg_rotation_r ; //rotation of right lower leg about x axis
    myfile >> front_weel_slab_rotation ; //rotarion of slab contain weel around x axis
    myfile >> uper_leg_rotation_xl ; //rotation of uper left leg about x axis
    myfile >> uper_leg_rotation_zl ; //rotation of uper left leg about z axis
    myfile >> uper_leg_rotation_xr ; //rotation of uper right leg about x axis
    myfile >> uper_leg_rotation_zr ; //rotation of uper right leg about z axis
    myfile >> hood_feet_rotation_xl1 ; //rotation of left whole feet about x axis
    myfile >> hood_feet_rotation_xl2 ; //rotation of left uper feet about x axis
    myfile >> hood_feet_rotation_xr1 ; //rotation of right whole feet about x axis
    myfile >> hood_feet_rotation_xr2 ; //rotation of right uper feet about x axis
    myfile >> throat_translate_y ; //translation of throat along y axis
    myfile >> truck_ceiling_rotation ; //rotation of truck ceilig about x axis
    myfile >> front_glass_rotation ; //totation of fron glass bout x axis
    myfile >> side_gate_rotation ; //side gate rotation about x axis
    myfile >> weel_rotation ; //roatation of weel about z axis
    myfile >> forword_backword_movement_z ; // translate whole body along z axis
    myfile >> forword_backword_movement_x ; // translate whole body along x axis

    myfile >> vertical_movement ; // vertical movement of transformer(independent)

    myfile >> headlight_on ;  // whether headlight on (decide which texture to load)
    myfile >> lighting_enabled; 
    myfile >> light0_enabled; 
    myfile >> light1_enabled; 
    return true;
}


keyframe_t interpolate(keyframe_t current, keyframe_t next, float fraction){
    keyframe_t result;

    //result.camera_no = (fraction > 0.5) ? current.camera_no : next.camera_no;
    result.camera_no = current.camera_no;

    result.rotation_angle = current.rotation_angle + (next.rotation_angle - current.rotation_angle)*fraction;
    result.body_rotation_x = current.body_rotation_x + (next.body_rotation_x - current.body_rotation_x)*fraction;
    result.body_rotation_y = current.body_rotation_y + (next.body_rotation_y - current.body_rotation_y)*fraction;
    result.body_rotation_z = current.body_rotation_z + (next.body_rotation_z - current.body_rotation_z)*fraction;
    result.back_weel_slab_rotation = current.back_weel_slab_rotation + (next.back_weel_slab_rotation - current.back_weel_slab_rotation)*fraction;
    result.solder_rotation_zl = current.solder_rotation_zl + (next.solder_rotation_zl - current.solder_rotation_zl)*fraction;
    result.solder_rotation_yl = current.solder_rotation_yl + (next.solder_rotation_yl - current.solder_rotation_yl)*fraction;
    result.solder_rotation_xl = current.solder_rotation_xl + (next.solder_rotation_xl - current.solder_rotation_xl)*fraction;
    result.elbows_rotation_l = current.elbows_rotation_l + (next.elbows_rotation_l - current.elbows_rotation_l)*fraction;
    result.solder_rotation_zr = current.solder_rotation_zr + (next.solder_rotation_zr - current.solder_rotation_zr)*fraction;
    result.solder_rotation_yr = current.solder_rotation_yr + (next.solder_rotation_yr - current.solder_rotation_yr)*fraction;
    result.solder_rotation_xr = current.solder_rotation_xr + (next.solder_rotation_xr - current.solder_rotation_xr)*fraction;
    result.elbows_rotation_r = current.elbows_rotation_r + (next.elbows_rotation_r - current.elbows_rotation_r)*fraction;
    result.waist_rotation = current.waist_rotation + (next.waist_rotation - current.waist_rotation)*fraction;
    result.upper_body_rotation = current.upper_body_rotation + (next.upper_body_rotation - current.upper_body_rotation)*fraction;
    result.lower_leg_rotation_l = current.lower_leg_rotation_l + (next.lower_leg_rotation_l - current.lower_leg_rotation_l)*fraction;
    result.lower_leg_rotation_r = current.lower_leg_rotation_r + (next.lower_leg_rotation_r - current.lower_leg_rotation_r)*fraction;
    result.front_weel_slab_rotation = current.front_weel_slab_rotation + (next.front_weel_slab_rotation - current.front_weel_slab_rotation)*fraction;
    result.uper_leg_rotation_xl = current.uper_leg_rotation_xl + (next.uper_leg_rotation_xl - current.uper_leg_rotation_xl)*fraction;
    result.uper_leg_rotation_zl = current.uper_leg_rotation_zl + (next.uper_leg_rotation_zl - current.uper_leg_rotation_zl)*fraction;
    result.uper_leg_rotation_xr = current.uper_leg_rotation_xr + (next.uper_leg_rotation_xr - current.uper_leg_rotation_xr)*fraction;
    result.uper_leg_rotation_zr = current.uper_leg_rotation_zr + (next.uper_leg_rotation_zr - current.uper_leg_rotation_zr)*fraction;
    result.hood_feet_rotation_xl1 = current.hood_feet_rotation_xl1 + (next.hood_feet_rotation_xl1 - current.hood_feet_rotation_xl1)*fraction;
    result.hood_feet_rotation_xl2 = current.hood_feet_rotation_xl2 + (next.hood_feet_rotation_xl2 - current.hood_feet_rotation_xl2)*fraction;
    result.hood_feet_rotation_xr1 = current.hood_feet_rotation_xr1 + (next.hood_feet_rotation_xr1 - current.hood_feet_rotation_xr1)*fraction;
    result.hood_feet_rotation_xr2 = current.hood_feet_rotation_xr2 + (next.hood_feet_rotation_xr2 - current.hood_feet_rotation_xr2)*fraction;
    result.throat_translate_y = current.throat_translate_y + (next.throat_translate_y - current.throat_translate_y)*fraction;
    result.truck_ceiling_rotation = current.truck_ceiling_rotation + (next.truck_ceiling_rotation - current.truck_ceiling_rotation)*fraction;
    result.front_glass_rotation = current.front_glass_rotation + (next.front_glass_rotation - current.front_glass_rotation)*fraction;
    result.side_gate_rotation = current.side_gate_rotation + (next.side_gate_rotation - current.side_gate_rotation)*fraction;
    result.weel_rotation = current.weel_rotation + (next.weel_rotation - current.weel_rotation)*fraction;
    result.forword_backword_movement_z = current.forword_backword_movement_z + (next.forword_backword_movement_z - current.forword_backword_movement_z)*fraction;
    result.forword_backword_movement_x = current.forword_backword_movement_x + (next.forword_backword_movement_x - current.forword_backword_movement_x)*fraction;

    result.vertical_movement = current.vertical_movement + (next.vertical_movement - current.vertical_movement)*fraction;

    result.headlight_on = current.headlight_on;
    result.lighting_enabled = current.lighting_enabled;
    result.light0_enabled = current.light0_enabled;
    result.light1_enabled = current.light1_enabled;

    return result;
}

void savePPM(int start_x,int start_y,int w,int h,char *fname){
    FILE *f=fopen(fname,"wb");
    if (!f) return;
    std::vector<unsigned char> out(3*w*h);
    glPixelStorei(GL_PACK_ALIGNMENT,1); /* byte aligned output */
    glReadPixels(start_x,start_y,w,h, GL_RGB,GL_UNSIGNED_BYTE,&out[0]);
    fprintf(f,"P6\n%d %d\n255\n",w,h);
    for (int y=0;y<h;y++) { /* flip image bottom-to-top on output */
      fwrite(&out[3*(h-1-y)*w],1,3*w,f);
    }
    fclose(f);
}
