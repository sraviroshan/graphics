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

#include "gl_framework.hpp"
#include "optimus.h"

#define USE_PERSPECTIVE true
extern optimus_t optimus;
extern int camera_no;

namespace csX75
{
  int win_width;
  int win_height;

  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Enable Depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);     // The Type Of Depth Test To Do
    glEnable(GL_NORMALIZE);      //Enable force normalization of normals by open gl
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Check if following is needed
    glShadeModel(GL_SMOOTH);      // Enables Smooth Color Shading

  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    if  ( height == 0 ) height = 1;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Draw to the whole window
    glViewport( 0, 0, width, height );

    //Keep the aspect ratio fixed
    double aspect;

    if(USE_PERSPECTIVE){
      gluPerspective(70, (double)width/(double)height, 0.1, 4.0);
    }
    else{
      if (width > height)
      {
        aspect = (double)width/(double)height;
        glOrtho(-aspect, aspect, -1.0, 1.0, 0.0, 5.0);
            }
          else
            {
        aspect = (double)height/(double)width;
        glOrtho(-1.0, 1.0, -aspect, aspect, 0.0, 5.0);
      }
    }
    
    win_width = width;
    win_height = height;
  }

  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_F1 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT)) //f1 without shift
      glEnable(GL_LIGHTING);
    else if (key == GLFW_KEY_F1 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)) //shift+F1
      glDisable(GL_LIGHTING);
    else if (key == GLFW_KEY_F2 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT)) //f2 without shift
      glEnable(GL_LIGHT0);
    else if (key == GLFW_KEY_F2 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)) //shift+F2
      glDisable(GL_LIGHT0);
    else if (key == GLFW_KEY_F3 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT)) //f3 without shift
      glEnable(GL_LIGHT1);
    else if (key == GLFW_KEY_F3 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)) //shift+F3
          glDisable(GL_LIGHT1);
    else if (key == GLFW_KEY_F4 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT)){ //f4 without shift
      glEnable(GL_LIGHT2);
      glEnable(GL_LIGHT3);
      optimus.headlight_on = true;
    }
    else if (key == GLFW_KEY_F4 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)){ //shift+f4
      glDisable(GL_LIGHT2);
      glDisable(GL_LIGHT3);
      optimus.headlight_on = false;
    }
    else if (key == GLFW_KEY_F8 && action == GLFW_PRESS) //f8
      camera_no = 0;
    else if (key == GLFW_KEY_F9 && action == GLFW_PRESS) //f9
      camera_no = 1;
    else if (key == GLFW_KEY_F10 && action == GLFW_PRESS) //f10
      camera_no = 2;
    //whole body rotation
    else 
      optimus.optimus_key_callback(key, scancode, action, mods);
  }
};  
  


