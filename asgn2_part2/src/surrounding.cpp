#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cmath>

#include "gl_framework.hpp"
#include "texture_utils.h"
#include "surrounding.h"
#include "optimus.h"

#define id_back_wall 100
#define x_wall 50
#define y_wall 19
#define z_wall 50
#define id_left_wall 101
#define id_right_wall 102
#define id_floor_wall 103

extern optimus_t optimus;

void surrounding_t::init_surrounding(void){
	back_wall();
	// front_wall();
	left_wall();
	right_wall();
	// top_wall();
	floor_wall();
}

void surrounding_t::set_camera_wall_corner(void){
	float cx_wall = x_wall*1;//0.02;//
	float cy_wall = y_wall*1;//0.02;//
	float cz_wall = z_wall*1;//0.02;//

	// gluLookAt(-cx_wall, cy_wall, cz_wall,
 //            0, 0, 0,
 //            cx_wall, (cx_wall*cx_wall + cz_wall*cz_wall)/1.0 * cy_wall, -1*cz_wall);
	gluLookAt(-cx_wall, 0, 0,
            0, 0, 0,
            0,1, 0);
}


// Load bitmap images to form textures
void surrounding_t::load_textures() { 
    glEnable(GL_TEXTURE_2D);

    //texture for torso
    glGenTextures(1, &texture[0]);
    Texture t0(texture[0], "images/wall.bmp");
    t0.generate();

    glGenTextures(1, &texture[1]);
    Texture t1(texture[1], "images/floor.bmp");
    t1.generate();

    glDisable(GL_TEXTURE_2D);
};

void surrounding_t::back_wall(){
	glNewList(id_back_wall, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
  	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);            //front face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1* x_wall,-1* y_wall,-1*z_wall); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1* x_wall,y_wall,-1*z_wall);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x_wall,y_wall,-1*z_wall);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x_wall,-1* y_wall,-1*z_wall);
	glEnd();

  	glDisable(GL_TEXTURE_2D);
	glEndList();
  	
}
//left wall
void surrounding_t::left_wall(){
	glNewList(id_left_wall, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
  	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);            //front face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1* x_wall,-1* y_wall,-1*z_wall); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1* x_wall,y_wall,-1*z_wall);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x_wall,y_wall,1*z_wall);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x_wall,-1* y_wall,1*z_wall);
	glEnd();

  	glDisable(GL_TEXTURE_2D);
	glEndList();
  	
}
//right wall
void surrounding_t::right_wall(){
	glNewList(id_right_wall, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
  	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);            //front face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1* x_wall,-1* y_wall,1*z_wall); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1* x_wall,y_wall,1*z_wall);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1*x_wall,y_wall,-1*z_wall);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1*x_wall,-1* y_wall,-1*z_wall);
	glEnd();

  	glDisable(GL_TEXTURE_2D);
	glEndList();
  	
}
//floor
void surrounding_t::floor_wall(){
	glNewList(id_floor_wall, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
  	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);            //front face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1* x_wall,-1* y_wall,-1*z_wall); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1* x_wall,-1*y_wall,-1*z_wall);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x_wall,-1*y_wall,1*z_wall);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1*x_wall,-1* y_wall,1*z_wall);
	glEnd();

  	glDisable(GL_TEXTURE_2D);
	glEndList();
  	
}


void surrounding_t::surround_all(){
	glPushMatrix();
	  // glScalef(0.04, 0.04, 0.04);

	  // glRotatef(optimus.body_rotation_x,1,0,0);
   //    glRotatef(optimus.body_rotation_y,0,1,0);
   //    glRotatef(optimus.body_rotation_z,0,0,1);
      glPushMatrix();
      	glCallList(id_back_wall);
      glPopMatrix();
      glPushMatrix();
      	glCallList(id_left_wall);
      glPopMatrix();
      glPushMatrix();
      	glCallList(id_right_wall);
      glPopMatrix();
      glPushMatrix();
      	glCallList(id_floor_wall);
      glPopMatrix();
    glPopMatrix();
}
