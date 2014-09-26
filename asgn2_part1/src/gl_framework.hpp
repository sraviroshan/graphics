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

#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <iostream>

namespace csX75
{
  //! Initialize GL State
  void initGL(void);
 
  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  extern int rotation_angle; //angle for rotation about axis
  extern int body_rotation_x; //rotate body about x axis
  extern int body_rotation_y; //rotate body about x axis
  extern int body_rotation_z; //rotate body about x axis
  extern int back_weel_slab_rotation; //rotation of back weel slab bout x axis
  extern int solder_rotation_zl; //left solder rotation angle about z axis
  extern int solder_rotation_yl; //left solder rotation angle about y axis
  extern int solder_rotation_xl; // left solder rotation angle about x axis
  extern int elbows_rotation_l; //left elbows rotarion angle about z axis
  extern int solder_rotation_zr; // right solder rotation angle about z axis
  extern int solder_rotation_yr; // right solder rotation angle about y axis
  extern int solder_rotation_xr; // right solder rotation angle about x axis
  extern int elbows_rotation_r; //right elbows rotarion angle about z axis
  extern int waist_rotation; // rotation of waist about y axis
  extern int lower_leg_rotation_l; //rotation of left lower leg about x axis
  extern int lower_leg_rotation_r; //rotation of right lower leg about x axis
  extern int front_weel_slab_rotation; //rotarion of slab contain weel around x axis
  extern int uper_leg_rotation_xl; //rotation of uper left leg about x axis
  extern int uper_leg_rotation_zl; //rotation of uper left leg about z axis
  extern int uper_leg_rotation_xr; //rotation of uper right leg about x axis
  extern int uper_leg_rotation_zr; //rotation of uper right leg about z axis
};

#endif
