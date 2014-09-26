/*
 * CS475/CS675 - Computer Graphics
 *  ToyLOGO Assignment Base Code
 *
 * Copyright 2009-2014, Parag Chaudhuri, Department of CSE, IIT Bombay
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cmath>

#include "gl_framework.hpp"

#define id_torso 1
#define torso_xl 2.50 
#define torso_yl 3.0
#define torso_zl 1.50

#define id_uper_hand 2
#define uper_hand_l 2.5

#define id_lower_hand 3
#define lower_hand_l 4.0 

#define id_waist  4
#define waist_xl 2.0
#define waist_yl 0.5
#define waist_zl 1.0

#define id_uper_leg 5
#define uper_leg_l 2.0

#define id_lower_leg 6
#define lower_leg_l 4.0
#define lower_leg_xl 0.8

#define id_front_weel_slab 7
#define front_weel_slab_xl 0.5
#define front_weel_slab_yl 2.0

#define id_unit_weel 8
#define unit_weel_y 6.0
#define id_weel 9
#define weel_radius 2.0
#define weel_width  1.0
#define weel_angle  15

#define PI 3.14159265359

//! The pointer to the GLFW window
GLFWwindow* window;

//GLFW display callback
void unit_cube(void);
void torso(void);
void uper_hand(void);
void lower_hand(void);
void waist(void);
void uper_leg(void);
void lower_leg(void);
void unit_weel(void);
void front_weel_slab(void);
void weel(void);


/*-----------------------------INIT DISPLAY LISTS------------------------*/
void init_structures(void)
{
  torso();
  uper_hand();
  lower_hand();
  waist();
  uper_leg();
  lower_leg();
  front_weel_slab();

  unit_weel();
  weel();
}
//unit weel
void unit_weel(){
  
  glNewList(id_unit_weel,GL_COMPILE);
  glTranslatef(0,unit_weel_y,0);
  
  glColor4f(1, 0.44, .555, 1);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f,0.0f,0.20f);
    glVertex3f(1.0f,0.0f,0.20f);
    glVertex3f(0.8660f,0.50f,0.20f);
    glVertex3f(0.50f,0.8660f,0.20f);
    glVertex3f(0.0f,1.0f,0.20f);
    glVertex3f(-0.50f,0.8660f,0.20f);
    glVertex3f(-0.8660f,0.50f,0.20f);
    glVertex3f(-1.0f,0.0f,0.20f);
    glVertex3f(-0.8660f,-0.50f,0.20f);
    glVertex3f(-0.50f,-0.8660f,0.20f);
    glVertex3f(0.0f,-1.0f,0.20f);
    glVertex3f(0.50f,-0.8660f,0.20f);
    glVertex3f(0.8660f,-0.50f,0.20f);
    glVertex3f(1.0f,0.0f,0.20f);
  glEnd();
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f,0.0f,-0.20f);
    glVertex3f(1.0f,0.0f,-0.20f);
    glVertex3f(0.8660f,0.50f,-0.20f);
    glVertex3f(0.50f,0.8660f,-0.20f);
    glVertex3f(0.0f,1.0f,-0.20f);
    glVertex3f(-0.50f,0.8660f,-0.20f);
    glVertex3f(-0.8660f,0.50f,-0.20f);
    glVertex3f(-1.0f,0.0f,-0.20f);
    glVertex3f(-0.8660f,-0.50f,-0.20f);
    glVertex3f(-0.50f,-0.8660f,-0.20f);
    glVertex3f(0.0f,-1.0f,-0.20f);
    glVertex3f(0.50f,-0.8660f,-0.20f);
    glVertex3f(0.8660f,-0.50f,-0.20f);
    glVertex3f(1.0f,0.0f,-0.20f);
  glEnd();
  
  glColor4f(0, 0.44, .555, 1);
  glBegin(GL_QUAD_STRIP);
    glVertex3f(1.0f,0.0f,0.20f);
    glVertex3f(0.0f,0.0f,-0.20f);
    glVertex3f(0.8660f,0.50f,0.20f);
    glVertex3f(0.8660f,0.50f,-0.20f);
    glVertex3f(0.50f,0.8660f,0.20f);
    glVertex3f(0.50f,0.8660f,-0.20f);
    glVertex3f(0.0f,1.0f,0.20f);
    glVertex3f(0.0f,1.0f,-0.20f);
    glVertex3f(-0.50f,0.8660f,0.20f);
    glVertex3f(-0.50f,0.8660f,-0.20f);
    glVertex3f(-0.8660f,0.50f,0.20f);
    glVertex3f(-0.8660f,0.50f,-0.20f);
    glVertex3f(-1.0f,0.0f,0.20f);
    glVertex3f(-1.0f,0.0f,-0.20f);
    glVertex3f(-0.8660f,-0.50f,0.20f);
    glVertex3f(-0.8660f,-0.50f,-0.20f);
    glVertex3f(-0.50f,-0.8660f,0.20f);
    glVertex3f(-0.50f,-0.8660f,-0.20f);
    glVertex3f(0.0f,-1.0f,0.20f);
    glVertex3f(0.0f,-1.0f,-0.20f);
    glVertex3f(0.50f,-0.8660f,0.20f);
    glVertex3f(0.50f,-0.8660f,-0.20f);
    glVertex3f(0.8660f,-0.50f,0.20f);
    glVertex3f(0.8660f,-0.50f,-0.20f);
  glEnd();

  glEndList();
    
}

void weel(){
  glNewList(id_weel,GL_COMPILE);


  glBegin(GL_TRIANGLE_FAN);
    for(int i=0;i<=360;i+=weel_angle){
      float radian = i* PI/180.0;
      glVertex3f(weel_radius*cos(radian),weel_radius*sin(radian),weel_width/2);
    }
  glEnd();
  glBegin(GL_TRIANGLE_FAN);
    for(int i=0;i<=360;i+=weel_angle){
      float radian = i* PI/180.0;
      glVertex3f(weel_radius*cos(radian),weel_radius*sin(radian),-1*weel_width/2);
    }
  glEnd();
  glBegin(GL_QUAD_STRIP);
    for(int i=0;i<=360;i+=weel_angle){
      float radian = i* PI/180.0;
      glVertex3f(weel_radius*cos(radian),weel_radius*sin(radian),weel_width/2);
      glVertex3f(weel_radius*cos(radian),weel_radius*sin(radian),-1*weel_width/2);
    }
  glEnd();
  glEndList();
}
void unit_cube(){
  glBegin(GL_QUADS);            //front face
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //left face
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glBegin(GL_QUADS);          //right face
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //top face        
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //bottom face
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glEnd();

}
void torso(){
  glNewList(id_torso,GL_COMPILE);
  glScalef(torso_xl,torso_yl,torso_zl);
  
  glColor4f(1, 0, 0, 1);
  glBegin(GL_QUADS);            //front face
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glColor4f(1, 0, 0, 1);
  glBegin(GL_QUADS);          //back face       
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0, 1,0, 1);
  glBegin(GL_QUADS);          //left face
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glColor4f(0, 1, 0, 1);
  glBegin(GL_QUADS);          //right face
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glEnd();
  
  glColor4f(0, 0, 1, 1);
  glBegin(GL_QUADS);        //top face        
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0, 0,1, 1);
  glBegin(GL_QUADS);        //bottom face
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glEnd();


  glEndList();
}
void uper_hand(){
  glNewList(id_uper_hand,GL_COMPILE);
  glTranslatef(uper_hand_l,0,0);
  glScalef(uper_hand_l,1,1);
  //unit_cube();
  glColor4f(0.1117, 0.34, 0.0816, 1);
  glBegin(GL_QUADS);            //front face
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glColor4f(0.1117, 0.34, 0.0816, 1);
  glBegin(GL_QUADS);          //back face       
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.37,0.3647 ,0.0518, 1);
  glBegin(GL_QUADS);          //left face
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glColor4f(0.37,0.3647 ,0.0518, 1);
  glBegin(GL_QUADS);          //right face
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glEnd();
  
  glColor4f(0.35, 0.0956, 0.0385, 1);
  glBegin(GL_QUADS);        //top face        
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.35, 0.0956, 0.0385, 1);
  glBegin(GL_QUADS);        //bottom face
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glEnd();


  glEndList();
}

void lower_hand(){
  glNewList(id_lower_hand,GL_COMPILE);
  glTranslatef(lower_hand_l,0,0);
  glScalef(lower_hand_l,1,1);
  //unit_cube();
  glColor4f(0.28,0.0616, 0.1126, 1);
  glBegin(GL_QUADS);            //front face
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glColor4f(0.28,0.0616, 0.1126, 1);
  glBegin(GL_QUADS);          //back face       
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.3989,0.1056 ,0.48, 1);
  glBegin(GL_QUADS);          //left face
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glColor4f(0.3989,0.1056 ,0.48, 1);
  glBegin(GL_QUADS);          //right face
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //top face        
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //bottom face
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glEnd();


  glEndList();
}
//waist
void waist(){
  glNewList(id_waist,GL_COMPILE);
  glTranslatef(0,-1*waist_yl,0);
  glScalef(waist_xl,waist_yl,waist_zl);
  unit_cube();
  glEndList();
}
//uper_leg
void uper_leg(){
  glNewList(id_uper_leg,GL_COMPILE);
  glTranslatef(0,-1*uper_leg_l,0);
  glScalef(1,uper_leg_l,1);
  
  glColor4f(0.28,0.0616, 0.1126, 1);
  glBegin(GL_QUADS);            //front face
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glColor4f(0.28,0.0616, 0.1126, 1);
  glBegin(GL_QUADS);          //back face       
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.3989,0.1056 ,0.48, 1);
  glBegin(GL_QUADS);          //left face
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glColor4f(0.3989,0.1056 ,0.48, 1);
  glBegin(GL_QUADS);          //right face
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //top face        
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //bottom face
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glEnd();

  glEndList();

}
//lower leg
void lower_leg(){
  glNewList(id_lower_leg,GL_COMPILE);
  glTranslatef(0,-1*lower_leg_l,0);
  glScalef(lower_leg_xl,lower_leg_l,1);
  
  glColor4f(0.3989,0.1056 ,0.48, 1);
  glBegin(GL_QUADS);            //front face
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glColor4f(0.3989,0.1056 ,0.48, 1);
  glBegin(GL_QUADS);          //back face       
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.28,0.0616, 0.1126, 1);
  glBegin(GL_QUADS);          //left face
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glColor4f(0.28,0.0616, 0.1126, 1);
  glBegin(GL_QUADS);          //right face
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //top face        
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //bottom face
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glEnd();

  glEndList();

}
//front weel slab
void front_weel_slab(){
  glNewList(id_front_weel_slab, GL_COMPILE);
  glTranslatef(0,-1*front_weel_slab_yl,0);
  glScalef(front_weel_slab_xl,front_weel_slab_yl,1);

  glColor4f(0.28,0.0616, 1, 1);
  glBegin(GL_QUADS);            //front face
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glColor4f(0.28,0.0616, 1, 1);
  glBegin(GL_QUADS);          //back face       
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.3989,0.1056 ,0.8, 1);
  glBegin(GL_QUADS);          //left face
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glColor4f(0.3989,0.1056 ,0.8, 1);
  glBegin(GL_QUADS);          //right face
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //top face        
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //bottom face
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glEnd();

  glEndList();

}


void hierarchi(){
  glLoadIdentity();

  //body rotation
   glScalef(0.04, 0.04, 0.04);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glRotatef(csX75::body_rotation_x,1,0,0);
       glRotatef(csX75::body_rotation_y,0,1,0);
       glRotatef(csX75::body_rotation_z,0,0,1);
      

    glPushMatrix();
      glColor4f(1.0,0.0,0.0,1.0);
      glCallList(id_torso);
    glPopMatrix();
    //weel
    glPushMatrix();
      glCallList(id_unit_weel);
    glPopMatrix();
  
    //left hand  
    glPushMatrix();
       glTranslatef(torso_xl,torso_yl,0.0f);
       glRotatef(csX75::solder_rotation_xl,1,0,0);
       glRotatef(csX75::solder_rotation_yl,0,1,0);
       glRotatef(csX75::solder_rotation_zl,0,0,1);
            
       glPushMatrix();
         glColor4f(0.0,1.0,0.0,1.0);
         glCallList(id_uper_hand);
       glPopMatrix();

      glPushMatrix();
        glTranslatef(uper_hand_l*2,0.0f,0.0f);
        glRotatef(csX75::elbows_rotation_l,0,0,1);
        glColor4f(0.0,0.0,1.0,1.0);
        glCallList(id_lower_hand);
      glPopMatrix();
    glPopMatrix();
    //right hand
    glPushMatrix();
       glTranslatef(-1*torso_xl,torso_yl,0.0f);
       glRotatef(csX75::solder_rotation_xr,1,0,0);
       glRotatef(csX75::solder_rotation_yr,0,1,0);
       glRotatef(csX75::solder_rotation_zr,0,0,1);
            
       glPushMatrix();
         glColor4f(0.0,1.0,0.0,1.0);
         glScalef(-1,1,1);
         glCallList(id_uper_hand);
       glPopMatrix();

      glPushMatrix();
        glTranslatef(-1*uper_hand_l*2,0.0f,0.0f);
        glRotatef(csX75::elbows_rotation_r,0,0,1);
        glColor4f(0.0,0.0,1.0,1.0);
        glScalef(-1,1,1);
        glCallList(id_lower_hand);
      glPopMatrix();
    glPopMatrix();
    
    //waist
    glPushMatrix();
      glTranslatef(0,-1*torso_yl,0);
      glRotatef(csX75::waist_rotation,0,1,0);

      glPushMatrix();
        glCallList(id_waist);
      glPopMatrix();
      
      //left leg
      glPushMatrix();
        glTranslatef(torso_xl/2,-2*waist_yl,0);
        glRotatef(csX75::uper_leg_rotation_xl,1,0,0);
        glRotatef(csX75::uper_leg_rotation_zl,0,0,1);
        glPushMatrix();
          glCallList(id_uper_leg);
        glPopMatrix();

        glPushMatrix();
          glTranslatef(0,-2*uper_leg_l,0);
          glRotatef(csX75::lower_leg_rotation_l,1,0,0);
          glPushMatrix();
            glCallList(id_lower_leg);
          glPopMatrix();
          glPushMatrix();
            glTranslatef(lower_leg_xl+front_weel_slab_xl,(-1*lower_leg_l),0);
            glRotatef(csX75::front_weel_slab_rotation,1,0,0);
            
            glPushMatrix();
              glCallList(id_front_weel_slab);
            glPopMatrix();
            
            glPushMatrix();
              glTranslatef(front_weel_slab_xl+weel_width/2,-1*front_weel_slab_yl,0);
              glRotatef(90,0,1,0);
              glCallList(id_weel);
            glPopMatrix();
          glPopMatrix();
        glPopMatrix();        
      glPopMatrix();

      //right leg
      glPushMatrix();
        glTranslatef(-1*torso_xl/2,-2*waist_yl,0);
        glRotatef(csX75::uper_leg_rotation_xr,1,0,0);
        glRotatef(csX75::uper_leg_rotation_zr,0,0,1);
        glPushMatrix();
          glCallList(id_uper_leg);
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0,-2*uper_leg_l,0);
          glRotatef(csX75::lower_leg_rotation_r,1,0,0);
          glPushMatrix();
            glCallList(id_lower_leg);
          glPopMatrix();
          glPushMatrix();
            glTranslatef(-1*(lower_leg_xl+front_weel_slab_xl),(-1*lower_leg_l),0);
            glRotatef(csX75::front_weel_slab_rotation,1,0,0);
            glPushMatrix();
              glCallList(id_front_weel_slab);
            glPopMatrix();
            glPushMatrix();
              glTranslatef(-1*(front_weel_slab_xl+weel_width/2),-1*front_weel_slab_yl,0);
              glRotatef(90,0,1,0);
              glCallList(id_weel);
            glPopMatrix();

          glPopMatrix();
        glPopMatrix();                
      glPopMatrix();
    glPopMatrix();
   
}

void renderGL(void){
  //tringle_axial_rotation();
  hierarchi();
}

int main (int argc, char *argv[]) 
{
  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  int win_width=700;
  int win_height=700;

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(win_width, win_height, "ToyLOGO", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glfwGetFramebufferSize(window, &win_width, &win_height);
  csX75::framebuffer_size_callback(window, win_width, win_height);


  glEnable(GL_DEPTH_TEST);
  //Initialize GL state
  csX75::initGL();
  //csX75::rotation_angle=0;
  csX75::body_rotation_x=0;
  csX75::body_rotation_y=0;
  csX75::body_rotation_z=0;
  csX75::solder_rotation_xl=0;
  csX75::solder_rotation_yl=0;
  csX75::solder_rotation_zl=0;
  csX75::elbows_rotation_l=0;
  csX75::solder_rotation_xr=0;
  csX75::solder_rotation_yr=0;
  csX75::solder_rotation_zr=0;
  csX75::elbows_rotation_r=0;
  csX75::waist_rotation=0;
  csX75::lower_leg_rotation_l=0;
  csX75::lower_leg_rotation_r=0;
  csX75::front_weel_slab_rotation=0;
  csX75::uper_leg_rotation_xl=0;
  csX75::uper_leg_rotation_zl=0;
  csX75::uper_leg_rotation_xr=0;
  csX75::uper_leg_rotation_zr=0;



  init_structures();  //
  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
