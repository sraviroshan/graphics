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
static GLdouble normal_buffer[3];

void configure_light0(){
	GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}

void configure_light1(){
	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
}

void surrounding_t::init_surrounding(void){
	configure_light0();
	configure_light1();

	back_wall();
	// front_wall();
	left_wall();
	right_wall();
	// top_wall();
	floor_wall();
}

void surrounding_t::set_camera_wall_corner(void){
	
	// gluLookAt(-cx_wall, cy_wall, cz_wall,
 //            0, 0, 0,
 //            cx_wall, (cx_wall*cx_wall + cz_wall*cz_wall)/1.0 * cy_wall, -1*cz_wall);
	gluLookAt(-x_wall, y_wall, 0,
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
	glBegin(GL_QUADS);
    calculate_normal(-1* x_wall,-1* y_wall,-1*z_wall, x_wall,-1* y_wall,-1*z_wall, x_wall,y_wall,-1*z_wall, normal_buffer);
    glNormal3dv(normal_buffer);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1* x_wall,-1* y_wall,-1*z_wall); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x_wall,-1* y_wall,-1*z_wall);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x_wall,y_wall,-1*z_wall);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1* x_wall,y_wall,-1*z_wall);
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
    calculate_normal(1* x_wall,-1* y_wall,-1*z_wall, x_wall,-1* y_wall,1*z_wall, x_wall,y_wall,1*z_wall, normal_buffer);
    glNormal3dv(normal_buffer);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1* x_wall,-1* y_wall,-1*z_wall); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x_wall,-1* y_wall,1*z_wall);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x_wall,y_wall,1*z_wall);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1* x_wall,y_wall,-1*z_wall);
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
    calculate_normal(-1* x_wall,-1* y_wall,1*z_wall, -1*x_wall,-1* y_wall,-1*z_wall, -1*x_wall,y_wall,-1*z_wall, normal_buffer);
    glNormal3dv(normal_buffer);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1* x_wall,-1* y_wall,1*z_wall); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1*x_wall,-1* y_wall,-1*z_wall);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1*x_wall,y_wall,-1*z_wall);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1* x_wall,y_wall,1*z_wall);
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
    calculate_normal(-1* x_wall,-1* y_wall,-1*z_wall, -1*x_wall,-1* y_wall,1*z_wall, x_wall,-1*y_wall,1*z_wall, normal_buffer);
    glNormal3dv(normal_buffer);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1* x_wall,-1* y_wall,-1*z_wall); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1*x_wall,-1* y_wall,1*z_wall);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x_wall,-1*y_wall,1*z_wall);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1* x_wall,-1*y_wall,-1*z_wall);
	glEnd();

  	glDisable(GL_TEXTURE_2D);
	glEndList();
  	
}

void surrounding_t::set_lights(){
	glPushMatrix();

		GLfloat light0_position[] = {-x_wall, y_wall, 0, 0.0 }; //last is zero means directional
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

		GLfloat light1_position[] = {0, y_wall, z_wall, 0.0 }; //last is zero means directional
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glPopMatrix();
}


void surrounding_t::surround_all(){
	glPushMatrix();
	  
   //    glRotatef(optimus.body_rotation_x,1,0,0);
   //    glRotatef(optimus.body_rotation_y,0,1,0);
   // 	 glRotatef(optimus.body_rotation_z,0,0,1);
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
