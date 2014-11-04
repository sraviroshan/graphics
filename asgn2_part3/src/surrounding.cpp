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
#define x_wall 50*2.5
#define y_wall 19*2.5
#define z_wall 50*2.5
#define id_left_wall 101
#define id_right_wall 102
#define id_floor_wall 103
#define id_front_wall 104
#define id_stage_floor 105
#define id_stage_front 106
#define id_stage_slop 107
#define stage_slop_w (1/6.0)*x_wall

#define WALL_TESSALATION 20

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
	front_wall();
	left_wall();
	right_wall();
	// top_wall();
	floor_wall();
  //stage
  stage_floor();
  stage_front();
  stage_slop();
}

void surrounding_t::set_camera_wall_corner(void){
	
	// gluLookAt(-cx_wall, cy_wall, cz_wall,
 //            0, 0, 0,
 //            cx_wall, (cx_wall*cx_wall + cz_wall*cz_wall)/1.0 * cy_wall, -1*cz_wall);
	gluLookAt(0, y_wall,z_wall,
            0, -y_wall, -z_wall,
            0,1, 0);
}


// Load bitmap images to form textures
void surrounding_t::load_textures() { 
    glEnable(GL_TEXTURE_2D);

    //texture for torso
    glGenTextures(1, &texture[0]);
    Texture t0(texture[0], "images/hall_wall.bmp");
    t0.generate();

    glGenTextures(1, &texture[2]);
    Texture t2(texture[2], "images/stage_b.bmp");
    t2.generate();

    glGenTextures(1, &texture[3]);
    Texture t3(texture[3], "images/stage_floor.bmp");
    t3.generate();

    glGenTextures(1, &texture[4]);
    Texture t4(texture[4], "images/stage_front.bmp");
    t4.generate();


    glGenTextures(1, &texture[1]);
    Texture t1(texture[1], "images/floor.bmp");
    t1.generate();

    glDisable(GL_TEXTURE_2D);
};

void surrounding_t::back_wall(){
	glNewList(id_back_wall, GL_COMPILE);
    //calculate_normal(-1* x_wall,-1* y_wall,-1*z_wall, x_wall,-1* y_wall,-1*z_wall, x_wall,y_wall,-1*z_wall, normal_buffer);
    GLdouble normal[3] = {0,0,1};
    glNormal3dv(normal);
    
    glTranslatef(0,y_wall/6.0,-z_wall);
    glScalef(x_wall,y_wall*5/6.0,0);

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    unit_wall_without_texture();

	glEndList();
}
void surrounding_t::stage_floor(){
  glNewList(id_stage_floor, GL_COMPILE);
  GLdouble normal[3] = {0,1,0};
  glNormal3dv(normal);

  glTranslatef(0,-y_wall*4/6.0,-z_wall*(1-1/8.0));
  glRotatef(90,1,0,0);
  glScalef(x_wall,z_wall/8.0,0);

  glBindTexture(GL_TEXTURE_2D, texture[3]);
  unit_wall_without_texture();  
  
  glEndList();
}
void surrounding_t::stage_front(){
 glNewList(id_stage_front, GL_COMPILE);
    //calculate_normal(-1* x_wall,-1* y_wall,-1*z_wall, x_wall,-1* y_wall,-1*z_wall, x_wall,y_wall,-1*z_wall, normal_buffer);
    GLdouble normal[3] = {0,0,1};
    glNormal3dv(normal);
    
    glTranslatef(0,-y_wall*5/6.0,-z_wall*6/8);
    glScalef(x_wall,y_wall/6.0,0);

    glBindTexture(GL_TEXTURE_2D, texture[4]);
    unit_wall_without_texture();

  glEndList(); 
}

void surrounding_t::stage_slop(){
  glNewList(id_stage_slop, GL_COMPILE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
  
    glBegin(GL_QUADS);          //left face
    // calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
    // glNormal3dv(normal_buffer);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-stage_slop_w,-y_wall,-z_wall*4/8.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(stage_slop_w,-y_wall,-z_wall*4/8.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(stage_slop_w,-y_wall*4/6.0,-z_wall*6/8.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-stage_slop_w,-y_wall*4/6.0,-z_wall*6/8.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);


  glEndList();
}

void surrounding_t::front_wall(){
  glNewList(id_front_wall, GL_COMPILE);
    GLdouble normal[3] = {0,0,-1};
    glNormal3dv(normal);

    glTranslatef(0,0,z_wall);
    glRotatef(180, 0, 1, 0);
    glScalef(x_wall,y_wall,0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    unit_wall_without_texture();

  glEndList();
}


void surrounding_t::unit_wall_without_texture(){
	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);
    for(int i=0; i<WALL_TESSALATION; i++){
        for(int j=0; j<WALL_TESSALATION; j++){
            glBegin(GL_QUADS);
            glTexCoord2f(i*1.0/WALL_TESSALATION, j*1.0/WALL_TESSALATION); glVertex3f(-1+i*2.0/WALL_TESSALATION, -1+j*2.0/WALL_TESSALATION,0); 
            glTexCoord2f((i+1)*1.0/WALL_TESSALATION, j*1.0/WALL_TESSALATION); glVertex3f(-1+(i+1)*2.0/WALL_TESSALATION, -1+j*2.0/WALL_TESSALATION,0);
            glTexCoord2f((i+1)*1.0/WALL_TESSALATION, (j+1)*1.0/WALL_TESSALATION); glVertex3f(-1+(i+1)*2.0/WALL_TESSALATION, -1+(j+1)*2.0/WALL_TESSALATION,0);
            glTexCoord2f(i*1.0/WALL_TESSALATION, (j+1)*1.0/WALL_TESSALATION); glVertex3f(-1+i*2.0/WALL_TESSALATION, -1+(j+1)*2.0/WALL_TESSALATION,0);
            glEnd();
        }
    }
  	glDisable(GL_TEXTURE_2D);
}

//left wall
void surrounding_t::left_wall(){
	glNewList(id_left_wall, GL_COMPILE);
    // calculate_normal(1* x_wall,-1* y_wall,-1*z_wall, x_wall,-1* y_wall,1*z_wall, x_wall,y_wall,1*z_wall, normal_buffer);
    // glNormal3dv(normal_buffer);

    GLdouble normal[3] = {-1,0,0};
    glNormal3dv(normal);
    
    glTranslatef(x_wall, 0, 0);
    glRotatef(90, 0, 1, 0);
    glScalef(z_wall,y_wall,0);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    unit_wall_without_texture();

	glEndList();
}
//right wall
void surrounding_t::right_wall(){
	glNewList(id_right_wall, GL_COMPILE);
    // calculate_normal(-1* x_wall,-1* y_wall,1*z_wall, -1*x_wall,-1* y_wall,-1*z_wall, -1*x_wall,y_wall,-1*z_wall, normal_buffer);
    // glNormal3dv(normal_buffer);
    GLdouble normal[3] = {1,0,0};
    glNormal3dv(normal);

    glTranslatef(-x_wall, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glScalef(z_wall,y_wall,0);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    unit_wall_without_texture();
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
  //manage lights
  if(lighting_enabled){
    glEnable(GL_LIGHTING);
  }
  else{
    glDisable(GL_LIGHTING);
  }

  if(light0_enabled){
    glEnable(GL_LIGHT0);
  }
  else{
    glDisable(GL_LIGHT0);
  }

  if(light1_enabled){
    glEnable(GL_LIGHT1);
  }
  else{
    glDisable(GL_LIGHT1);
  }

	glPushMatrix();

		GLfloat light0_position[] = {-x_wall, y_wall, 0, 0 }; //left wall top center
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

		GLfloat light1_position[] = {0, y_wall, z_wall, 0 }; //front wall top center
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glPopMatrix();
}

//hierarchy of surrounding
void surrounding_t::surround_all(){
	glPushMatrix();
	  
   //    glRotatef(optimus.body_rotation_x,1,0,0);
   //    glRotatef(optimus.body_rotation_y,0,1,0);
   // 	 glRotatef(optimus.body_rotation_z,0,0,1);
      glPushMatrix();
      	glCallList(id_back_wall);
      glPopMatrix();
      glPushMatrix();
        glCallList(id_stage_floor);
      glPopMatrix();
      glPushMatrix();
        glCallList(id_stage_front);
      glPopMatrix();
      glPushMatrix();
        glCallList(id_stage_slop);
      glPopMatrix();
      
      glPushMatrix();
        glCallList(id_front_wall);
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
