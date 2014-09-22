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

#include "gl_framework.hpp"

#define id_torso 1
#define torso_xl 3.0 
#define torso_yl 5.0
#define torso_zl 2.0

#define id_uper_hand 2
#define uper_hand_l 2.5

#define id_lower_hand 3
#define lower_hand_l 4.0 

//! The pointer to the GLFW window
GLFWwindow* window;

//GLFW display callback
void unit_cube(void);
void torso(void);
void uper_hand(void);
void lower_hand(void);

/*-----------------------------INIT DISPLAY LISTS------------------------*/
void init_structures(void)
{
  torso();
  uper_hand();
  lower_hand();
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
  unit_cube();
  glEndList();
}
void uper_hand(){
  glNewList(id_uper_hand,GL_COMPILE);
  glTranslatef(uper_hand_l/2,0,0);
  glScalef(uper_hand_l,1,1);
  unit_cube();
  glEndList();
}

void lower_hand(){
  glNewList(id_lower_hand,GL_COMPILE);
  glTranslatef(lower_hand_l,0,0);
  glScalef(lower_hand_l,1,1);
  unit_cube();
  glEndList();
}

void hierarchi(){
  glLoadIdentity();

  //body rotation
   glScalef(0.05, 0.05, 0.05);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glRotatef(csX75::body_rotation_x,1,0,0);
       glRotatef(csX75::body_rotation_y,0,1,0);
       glRotatef(csX75::body_rotation_z,0,0,1);
      

    glPushMatrix();
      glColor4f(1.0,0.0,0.0,1.0);
      glCallList(id_torso);
    glPopMatrix();
  
    glPushMatrix();
       glTranslatef(torso_xl,torso_yl,0.0f);
       glRotatef(csX75::solder_rotation_x,1,0,0);
       glRotatef(csX75::solder_rotation_y,0,1,0);
       glRotatef(csX75::solder_rotation_z,0,0,1);
            
       glPushMatrix();
         glColor4f(0.0,1.0,0.0,1.0);
         glCallList(id_uper_hand);
       glPopMatrix();

      glPushMatrix();
        glTranslatef(uper_hand_l,0.0f,0.0f);
        glRotatef(csX75::elbows_rotation,0,0,1);
        glColor4f(0.0,0.0,1.0,1.0);
        glCallList(id_lower_hand);
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

  int win_width=512;
  int win_height=512;

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
  //csX75::rotation_angle=0;
  csX75::body_rotation_x=0;
  csX75::body_rotation_y=0;
  csX75::body_rotation_z=0;
  csX75::solder_rotation_x=0;
  csX75::solder_rotation_y=0;
  csX75::solder_rotation_z=0;
  csX75::elbows_rotation=0;

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
