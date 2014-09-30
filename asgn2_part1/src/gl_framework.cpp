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
  int solder_rotation_zl;
  int solder_rotation_yl;
  int solder_rotation_xl;
  int elbows_rotation_l;
  int solder_rotation_zr;
  int solder_rotation_yr;
  int solder_rotation_xr;
  int elbows_rotation_r;
  int waist_rotation;
  int lower_leg_rotation_l;
  int lower_leg_rotation_r;
  int front_weel_slab_rotation;
  int uper_leg_rotation_xl;
  int uper_leg_rotation_zl;
  int uper_leg_rotation_xr;
  int uper_leg_rotation_zr;
  int back_weel_slab_rotation;
  int hood_feet_rotation_xl1;
  int hood_feet_rotation_xl2;
  int hood_feet_rotation_xr1;
  int hood_feet_rotation_xr2;
  float throat_translate_y;
  int truck_ceiling_rotation;
  int front_glass_rotation;


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
    //Enable texture
    glEnable(GL_TEXTURE_2D); 

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

  void reset_transformer_config(){
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
    csX75::front_weel_slab_rotation=180;
    csX75::uper_leg_rotation_xl=0;
    csX75::uper_leg_rotation_zl=0;
    csX75::uper_leg_rotation_xr=0;
    csX75::uper_leg_rotation_zr=0;
    csX75::back_weel_slab_rotation=55;
    csX75::hood_feet_rotation_xl1=-110;
    csX75::hood_feet_rotation_xl2=-140;
    csX75::hood_feet_rotation_xr1=-110;
    csX75::hood_feet_rotation_xr2=-140;
    csX75::throat_translate_y = 0;
    csX75::truck_ceiling_rotation = -150;
    csX75::front_glass_rotation =0;
  }

  void reset_car_config(){
    csX75::solder_rotation_xl=0;
    csX75::solder_rotation_yl=-90;
    csX75::solder_rotation_zl=-90;
    csX75::elbows_rotation_l=90;
    csX75::solder_rotation_xr=0;
    csX75::solder_rotation_yr=90;
    csX75::solder_rotation_zr=90;
    csX75::elbows_rotation_r=-90;
    csX75::waist_rotation=180;
    csX75::lower_leg_rotation_l=0;
    csX75::lower_leg_rotation_r=0;
    csX75::front_weel_slab_rotation=0;
    csX75::uper_leg_rotation_xl=90;
    csX75::uper_leg_rotation_zl=0;
    csX75::uper_leg_rotation_xr=90;
    csX75::uper_leg_rotation_zr=0;
    csX75::back_weel_slab_rotation=-20;
    csX75::hood_feet_rotation_xl1=0;
    csX75::hood_feet_rotation_xl2=0;
    csX75::hood_feet_rotation_xr1=0;
    csX75::hood_feet_rotation_xr2=0;
    csX75::throat_translate_y = -2*torso_yl;
    csX75::truck_ceiling_rotation = 90;
    csX75::front_glass_rotation=120;
  }

  void reset_view_angle(){
    csX75::body_rotation_x=0;
    csX75::body_rotation_y=0;
    csX75::body_rotation_z=0;
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
    else if(key==GLFW_KEY_Z && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      body_rotation_z = (body_rotation_z - 5)%360;
    else if(key==GLFW_KEY_Z && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      body_rotation_z = (body_rotation_z + 5)%360;    
    
    // uper left hand rotation
    else if(key==GLFW_KEY_E && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_zl = (solder_rotation_zl + 5)%360;    
    else if(key==GLFW_KEY_E && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_zl = (solder_rotation_zl - 5)%360;
    else if(key==GLFW_KEY_Q && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_xl = (solder_rotation_xl + 5)%360;    
    else if(key==GLFW_KEY_Q && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_xl = (solder_rotation_xl - 5)%360;      
    else if(key==GLFW_KEY_W && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_yl = (solder_rotation_yl + 5)%360;    
    else if(key==GLFW_KEY_W && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_yl = (solder_rotation_yl - 5)%360;      
    //lower left hand rotation
    else if(key==GLFW_KEY_R && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      elbows_rotation_l = (elbows_rotation_l + 5)%360;    
    else if(key==GLFW_KEY_R && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      elbows_rotation_l = (elbows_rotation_l - 5)%360;  
    // uper right hand rotation
    else if(key==GLFW_KEY_3 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_zr = (solder_rotation_zr + 5)%360;    
    else if(key==GLFW_KEY_3 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_zr = (solder_rotation_zr - 5)%360;
    else if(key==GLFW_KEY_1 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_xr = (solder_rotation_xr + 5)%360;    
    else if(key==GLFW_KEY_1 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_xr = (solder_rotation_xr - 5)%360;      
    else if(key==GLFW_KEY_2 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_yr = (solder_rotation_yr + 5)%360;    
    else if(key==GLFW_KEY_2 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_yr = (solder_rotation_yr - 5)%360;      
    //lower right hand rotation
    else if(key==GLFW_KEY_4 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      elbows_rotation_r = (elbows_rotation_r + 5)%360;    
    else if(key==GLFW_KEY_4 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      elbows_rotation_r = (elbows_rotation_r - 5)%360;  
    // back weel slab rotarion
    else if (key==GLFW_KEY_F && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      back_weel_slab_rotation = (back_weel_slab_rotation +5)%360;
    else if (key==GLFW_KEY_F && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      back_weel_slab_rotation = (back_weel_slab_rotation -5)%360;
    
    // waist rotation
    else if (key==GLFW_KEY_M && action == GLFW_PRESS  && !(mods & GLFW_MOD_SHIFT))
      waist_rotation = (waist_rotation +5)%360;
    else if (key==GLFW_KEY_M && action == GLFW_PRESS  && (mods & GLFW_MOD_SHIFT))
      waist_rotation = (waist_rotation -5)%360;
    //uper left leg toration
    else if (key == GLFW_KEY_P && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_xl = (uper_leg_rotation_xl + 5)%360;
    else if (key == GLFW_KEY_P && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_xl = (uper_leg_rotation_xl - 5)%360;
    else if (key == GLFW_KEY_O && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_zl = (uper_leg_rotation_zl + 5)%360;
    else if (key == GLFW_KEY_O && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_zl = (uper_leg_rotation_zl - 5)%360;
    //uper right leg rotation
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_xr = (uper_leg_rotation_xr + 5)%360;
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_xr = (uper_leg_rotation_xr - 5)%360;
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_zr = (uper_leg_rotation_zr + 5)%360;
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)) 
      uper_leg_rotation_zr = (uper_leg_rotation_zr - 5)%360;

    //lower left leg
    else if (key==GLFW_KEY_I && action== GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      lower_leg_rotation_l = (lower_leg_rotation_l + 5)%360;
    else if (key==GLFW_KEY_I && action== GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      lower_leg_rotation_l = (lower_leg_rotation_l - 5)%360;
    //lower right leg
    else if (key==GLFW_KEY_8 && action== GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      lower_leg_rotation_r = (lower_leg_rotation_r + 5)%360;
    else if (key==GLFW_KEY_8 && action== GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      lower_leg_rotation_r = (lower_leg_rotation_r - 5)%360;
    //front leg slab contain weel rotation
    else if(key== GLFW_KEY_L && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      front_weel_slab_rotation = (front_weel_slab_rotation + 5)%360;
    else if(key== GLFW_KEY_L && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      front_weel_slab_rotation = (front_weel_slab_rotation - 5)%360;
    //hood  left feet rotation
    else if (key == GLFW_KEY_K && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xl1 = (hood_feet_rotation_xl1 +5)%360;
    else if (key == GLFW_KEY_K && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xl1 = (hood_feet_rotation_xl1 -5)%360;
    else if (key == GLFW_KEY_J && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xl2 = (hood_feet_rotation_xl2 +5)%360;
    else if (key == GLFW_KEY_J && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xl2 = (hood_feet_rotation_xl2 -5)%360;
    //hood  right feet rotation
    else if (key == GLFW_KEY_H && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xr1 = (hood_feet_rotation_xr1 +5)%360;
    else if (key == GLFW_KEY_H && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xr1 = (hood_feet_rotation_xr1 -5)%360;
    else if (key == GLFW_KEY_G && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xr2 = (hood_feet_rotation_xr2 +5)%360;
    else if (key == GLFW_KEY_G && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xr2 = (hood_feet_rotation_xr2 -5)%360;
    else if (key == GLFW_KEY_A && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      throat_translate_y += 0.3;
    else if (key == GLFW_KEY_A && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      throat_translate_y -= 0.3;
    else if (key == GLFW_KEY_D && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      truck_ceiling_rotation = (truck_ceiling_rotation +5)%360;
    else if (key == GLFW_KEY_D && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      truck_ceiling_rotation = (truck_ceiling_rotation -5)%360;
    else if (key == GLFW_KEY_T && action == GLFW_PRESS)
      reset_transformer_config();
    else if (key == GLFW_KEY_C && action == GLFW_PRESS)
      reset_car_config();
    else if (key == GLFW_KEY_V && action == GLFW_PRESS)
      reset_view_angle();
    else if (key == GLFW_KEY_B && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      front_glass_rotation = (front_glass_rotation +5)%360;
    else if (key == GLFW_KEY_B && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      front_glass_rotation = (front_glass_rotation -5)%360;
    
  }
};  
  


