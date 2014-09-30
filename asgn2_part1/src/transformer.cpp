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
#include "texture_utils.h"

GLuint texture[10];



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
void back_weel_slab(void);
void hood_feet(void);
void sphere(void);
void hemisphere(void);
void truck_ceiling(void);
void front_glass(void);

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
  back_weel_slab();
  hood_feet();
  front_glass();
  sphere();
  hemisphere();

  unit_weel();
  weel();
  truck_ceiling();

}

// Load bitmap images to form textures
void load_textures() { 

    //texture for torso
    glGenTextures(1, &texture[0]);
    Texture t1(texture[0], "images/silver1.bmp");
    t1.generate();

    glGenTextures(1, &texture[1]);
    Texture t2(texture[1], "images/NeHe.bmp");
    t2.generate();
};

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
//sphere
void sphere_layer(float R, float angle1, float angle2){
    float z1 = R * sin(angle1 * PI/180);
    float z2 = R * sin(angle2 * PI/180);
    float r1 = sqrt(R*R - z1*z1);
    float r2 = sqrt(R*R - z2*z2);

    float theta = 0;

    for(theta = 0; theta < 360; theta+=ANGLE){
      float radian = theta * PI/180.0; 
      float radian1 = (theta+ANGLE) * PI/180.0; 
      glBegin(GL_QUADS);
      glVertex3f(r1 * cos(radian), z1, r1 * sin(radian));
      glVertex3f(r1 * cos(radian1), z1, r1 * sin(radian1));

      glVertex3f(r2 * cos(radian1), z2, r2 * sin(radian1));
      glVertex3f(r2 * cos(radian), z2, r2 * sin(radian));
      glEnd();
    }
}
void sphere(){
  glNewList(id_sphere,GL_COMPILE);
  float delta_angle = 90.0 / VERTICAL_ANGLE_PARTS;

  float v_angle = 0;
  for(int i=0; i < VERTICAL_ANGLE_PARTS; i++){
      sphere_layer(radius, v_angle, v_angle+delta_angle);
      v_angle += delta_angle;
  }
  
  v_angle=0;
  for(int i=0; i < VERTICAL_ANGLE_PARTS; i++){
      sphere_layer(radius, v_angle, v_angle-delta_angle);
      v_angle -= delta_angle;
  }
  glEndList();
}
//hamisphare
void hemisphere(){
  glNewList(id_hemisphere,GL_COMPILE);
  float delta_angle = 90.0 / VERTICAL_ANGLE_PARTS;

  float v_angle = 0;
  for(int i=0; i < VERTICAL_ANGLE_PARTS; i++){
      sphere_layer(radius, v_angle, v_angle+delta_angle);
      v_angle += delta_angle;
  }
  
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
void torso_old(){
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

void torso(){
  glNewList(id_torso, GL_COMPILE);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glScalef(torso_xl,torso_yl,torso_zl);
  
  glColor4f(1, 1, 1, 1);
  glBegin(GL_QUADS);            //front face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f); 
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  //glColor4f(1, 0, 0, 1);
  glBegin(GL_QUADS);          //back face       
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  //glColor4f(0, 1,0, 1);
  glBegin(GL_QUADS);          //left face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  //glColor4f(0, 1, 0, 1);
  glBegin(GL_QUADS);          //right face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glEnd();
  
  //glColor4f(0, 0, 1, 1);
  glBegin(GL_QUADS);        //top face        
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  //glColor4f(0, 0,1, 1);
  glBegin(GL_QUADS);        //bottom face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
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
//back weel slab
void back_weel_slab(){
  glNewList(id_back_weel_slab, GL_COMPILE);
  glTranslatef(0,0,-1*back_weel_slab_zl);
  glScalef(back_weel_slab_xl,1,back_weel_slab_zl);

  glColor4f(0.75, 0.7273, 0.0675, 1);
  unit_cube();
  glEndList();

}
//truck hood
void hood_feet(){
  glNewList(id_hood_feet,GL_COMPILE);
  glTranslatef(0,hood_feet_yl,-1*hood_feet_zl);
  glScalef(hood_feet_xl,hood_feet_yl,hood_feet_zl);
  unit_cube();
  glEndList();
}
void front_glass(){
  glNewList(id_front_glass,GL_COMPILE);
  glTranslatef(0,-1*front_glass_yl,-1*front_glass_zl);
  glScalef(front_glass_xl,front_glass_yl,front_glass_zl);
  unit_cube();
  glEndList();
}
//truck ceiling
void truck_ceiling(){
  glNewList(id_truck_ceiling,GL_COMPILE);
  glTranslatef(0,torso_zl+lower_hand_l/2,0);
  glScalef(torso_xl,torso_zl+lower_hand_l/2,truck_ceiling_width);

  glColor4f(0.28,0.0616, 1, 1);
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
    // //weel
    // glPushMatrix();
    //   glCallList(id_unit_weel);
    // glPopMatrix();
    // 
    //truck ceiling
    glPushMatrix();
      glTranslatef(0,torso_yl,-1*torso_zl);
      glRotatef(csX75::truck_ceiling_rotation,1,0,0);
      glCallList(id_truck_ceiling);
    glPopMatrix();
    //throat
    glPushMatrix();
      glTranslatef(0, csX75::throat_translate_y,0);
      glTranslatef(0,torso_yl,0);
      glPushMatrix();
        glScalef(throat_xl,throat_yl,throat_zl);
        glColor4f(0.39,0.1638,0.3033,1.0);
        glCallList(id_hemisphere);
      glPopMatrix();
      //head
      glPushMatrix();
        glTranslatef(0,throat_yl*radius,0);
        glColor4f(1,0.2528,0.49,1.0);
        glCallList(id_sphere);
      glPopMatrix();
      
    glPopMatrix();

    //back left weel slab
      glPushMatrix();
        glTranslatef((torso_xl+back_weel_slab_xl),-1*torso_yl,-1*torso_zl);
        glRotatef(csX75::back_weel_slab_rotation,1,0,0);
        glPushMatrix();
          glColor4f(0.84,0.7669,0.1092,1.0);
          glCallList(id_back_weel_slab);
        glPopMatrix();
        //back weel
        glPushMatrix();
          glTranslatef(back_weel_slab_xl,0,-2*back_weel_slab_zl);
          glRotatef(90,0,1,0);
          glColor4f(0.0588,0.2528,0.49,1.0);
          glCallList(id_weel);
        glPopMatrix();
      glPopMatrix();
    //back right weel slab
      glPushMatrix();
        glTranslatef(-(torso_xl+back_weel_slab_xl),-1*torso_yl,-1*torso_zl);
        glRotatef(csX75::back_weel_slab_rotation,1,0,0);
        glPushMatrix();
          glColor4f(0.84,0.7669,0.1092,1.0);
          glCallList(id_back_weel_slab);
        glPopMatrix();
        //back weel
        glPushMatrix();
          glTranslatef(-1*back_weel_slab_xl,0,-2*back_weel_slab_zl);
          glRotatef(90,0,1,0);
          glColor4f(0.0588,0.2528,0.49,1.0);
          glCallList(id_weel);
        glPopMatrix();
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
        //lower leg
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
              glColor4f(0.0588,0.2528,0.49,1.0);
              glCallList(id_weel);
            glPopMatrix();  
          glPopMatrix();
          //hood feet
          glPushMatrix();
            glTranslatef(0,-2*lower_leg_l,-1 );
            glRotatef(csX75::hood_feet_rotation_xl1,1,0,0);
            glPushMatrix();
              glColor4f(0.105,0.5,0.1708,1.0);
              glCallList(id_hood_feet);
            glPopMatrix();
            glPushMatrix();
              glTranslatef(0,0,-2*hood_feet_zl);
              glRotatef(csX75::hood_feet_rotation_xl2,1,0,0);
              glPushMatrix();
                glColor4f(0.1098,0.61,0.3932,1.0);
                glCallList(id_hood_feet);
              glPopMatrix();
              //front left glass
              glPushMatrix();
                glTranslatef(0,2*front_glass_yl,-2*hood_feet_zl);
                glRotatef(csX75::front_glass_rotation,1,0,0);
                glColor4f(1,1,1,1.0);
                glCallList(id_front_glass);
              glPopMatrix();

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
              glColor4f(0.0588,0.2528,0.49,1.0);
              glCallList(id_weel);
            glPopMatrix();
          glPopMatrix();
          //hood feet
          glPushMatrix();
            glTranslatef(0,-2*lower_leg_l,-1 );
            glRotatef(csX75::hood_feet_rotation_xr1,1,0,0);
            glPushMatrix();
              glColor4f(0.105,0.5,0.1708,1.0);
              glCallList(id_hood_feet);
            glPopMatrix();
            glPushMatrix();
              glTranslatef(0,0,-2*hood_feet_zl);
              glRotatef(csX75::hood_feet_rotation_xr2,1,0,0);
              glPushMatrix();
              glColor4f(0.1098,0.61,0.3932,1.0);
              glCallList(id_hood_feet);
              glPopMatrix();
              //front left glass
              glPushMatrix();
                glTranslatef(0,2*front_glass_yl,-2*hood_feet_zl);
                glRotatef(csX75::front_glass_rotation,1,0,0);
                glColor4f(1,1,1,1.0);
                glCallList(id_front_glass);
              glPopMatrix();
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

  //Initialize GL state
  csX75::initGL();

  //Load textures
  load_textures();
  
  //initialise viewing angle
  csX75::reset_view_angle();
  //initialise all constraint angles and lengths
  csX75::reset_transformer_config();

  init_structures();  //create display lists of different body parts
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
