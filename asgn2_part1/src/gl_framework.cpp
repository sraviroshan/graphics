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

namespace csX75
{
  int win_width;
  int win_height;
 //int rotation_angle;
  int body_rotation_x;
  int body_rotation_y;
  int body_rotation_z;
  int solder_rotation_z;
  int solder_rotation_y;
  int solder_rotation_x;
  int elbows_rotation;
  int waist_rotation;
  int lower_leg_rotation_l;
  int lower_leg_rotation_r;
  int front_weel_slab_rotation;

  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
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
    if (width > height)
      {
	aspect = (double)width/(double)height;
	glOrtho(-aspect, aspect, -1.0, 1.0, -5.0, 5.0);
      }
    else
      {
	aspect = (double)height/(double)width;
	glOrtho(-1.0, 1.0, -aspect, aspect, -5.0, 5.0);
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
    //whole body rotation
    else if(key==GLFW_KEY_DOWN && action == GLFW_PRESS)
      body_rotation_x = (body_rotation_x - 5)%360;
    else if(key==GLFW_KEY_UP && action == GLFW_PRESS)
      body_rotation_x = (body_rotation_x + 5)%360;    
    else if(key==GLFW_KEY_LEFT && action == GLFW_PRESS)
      body_rotation_y = (body_rotation_y - 5)%360;
    else if(key==GLFW_KEY_RIGHT && action == GLFW_PRESS)
      body_rotation_y = (body_rotation_y + 5)%360;    
    else if(key==GLFW_KEY_Z && action == GLFW_PRESS)
      body_rotation_z = (body_rotation_z - 5)%360;
    else if(key==GLFW_KEY_A && action == GLFW_PRESS)
      body_rotation_z = (body_rotation_z + 5)%360;    
    
    // uper left hand rotation
    else if(key==GLFW_KEY_T && action == GLFW_PRESS)
      solder_rotation_z = (solder_rotation_z + 5)%360;    
    else if(key==GLFW_KEY_Y && action == GLFW_PRESS)
      solder_rotation_z = (solder_rotation_z - 5)%360;
    else if(key==GLFW_KEY_Q && action == GLFW_PRESS)
      solder_rotation_x = (solder_rotation_x + 5)%360;    
    else if(key==GLFW_KEY_W && action == GLFW_PRESS)
      solder_rotation_x = (solder_rotation_x - 5)%360;      
    else if(key==GLFW_KEY_E && action == GLFW_PRESS)
      solder_rotation_y = (solder_rotation_y + 5)%360;    
    else if(key==GLFW_KEY_R && action == GLFW_PRESS)
      solder_rotation_y = (solder_rotation_y - 5)%360;      
    //lower left hand rotation
    else if(key==GLFW_KEY_S && action == GLFW_PRESS)
      elbows_rotation = (elbows_rotation + 5)%360;    
    else if(key==GLFW_KEY_D && action == GLFW_PRESS)
      elbows_rotation = (elbows_rotation - 5)%360;  
    // waist rotation
    else if (key==GLFW_KEY_M && action == GLFW_PRESS)
      waist_rotation = (waist_rotation +5)%360;
    //lower left leg
    else if (key==GLFW_KEY_P && action== GLFW_PRESS)
      lower_leg_rotation_l = (lower_leg_rotation_l + 5)%360;
    else if (key==GLFW_KEY_O && action== GLFW_PRESS)
      lower_leg_rotation_l = (lower_leg_rotation_l - 5)%360;
    //lower right leg
    else if (key==GLFW_KEY_I && action== GLFW_PRESS)
      lower_leg_rotation_r = (lower_leg_rotation_r + 5)%360;
    else if (key==GLFW_KEY_U && action== GLFW_PRESS)
      lower_leg_rotation_r = (lower_leg_rotation_r - 5)%360;
    //front leg slab contain weel rotation
    else if(key== GLFW_KEY_L && action == GLFW_PRESS)
      front_weel_slab_rotation = (front_weel_slab_rotation + 5)%360;



  }
};  
  


