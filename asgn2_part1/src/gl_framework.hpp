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

#define id_back_weel_slab 10
#define back_weel_slab_xl 0.5 
//#define back_weel_slab_zl 3
#define back_weel_slab_zl 1.5

#define id_unit_weel 8
#define unit_weel_y 6.0
#define id_weel 9
#define weel_radius 2.0
#define weel_width  1.0
#define weel_angle  15

#define id_hood_feet 11
#define hood_feet_xl 1.25 
#define hood_feet_yl 2.0
#define hood_feet_zl 0.5

#define id_hood_feet_left 16

#define id_sphere 12
#define radius 1.8
#define ANGLE 5
#define VERTICAL_ANGLE_PARTS 10
#define id_hemisphere 13

#define throat_xl .7
#define throat_yl 2
#define throat_zl .7

#define id_truck_ceiling 14
#define truck_ceiling_width .2

#define id_front_glass 15
#define front_glass_xl 1.25
#define front_glass_yl 2.0
#define front_glass_zl 0.14

#define PI 3.14159265359

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

  void reset_transformer_config();
  void reset_car_config();
  void reset_view_angle();

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
  extern int hood_feet_rotation_xl1; //rotation of left whole feet about x axis
  extern int hood_feet_rotation_xl2; //rotation of left uper feet about x axis
  extern int hood_feet_rotation_xr1; //rotation of right whole feet about x axis
  extern int hood_feet_rotation_xr2; //rotation of right uper feet about x axis
  extern float throat_translate_y; //translation of throat along y axis
  extern int truck_ceiling_rotation; //rotation of truck ceilig about x axis
  extern int front_glass_rotation; //totation of fron glass bout x axis
};

#endif
