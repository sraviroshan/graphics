#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cmath>

#include "gl_framework.hpp"
#include "texture_utils.h"
#include "optimus.h"

#define id_torso 1
#define torso_xl 2.50 
#define torso_yl 3.0
#define torso_zl 1.70

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
#define radius 1.7
#define ANGLE 60
#define VERTICAL_ANGLE_PARTS 3
#define id_hemisphere 13

#define throat_xl .7
#define throat_yl 1.5
#define throat_zl .7

#define id_truck_ceiling 14
#define truck_ceiling_width .2

#define id_front_glass 15
#define front_glass_xl 1.25
#define front_glass_yl 2.0
#define front_glass_zl 0.14

#define id_side_gate 17
#define side_gate_width 0.2f

#define PI 3.14159265359

static GLdouble normal_buffer[3];

void optimus_t::init_structures(void)
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
  hood_feet_left();

  unit_weel();
  weel();
  truck_ceiling();
  side_gate();

}

// Load bitmap images to form textures
void optimus_t::load_textures() { 
    glEnable(GL_TEXTURE_2D);

    //texture for torso
    glGenTextures(1, &texture[0]);
    Texture t0(texture[0], "images/silver1.bmp");
    t0.generate();

    glGenTextures(1, &texture[1]);
    Texture t1(texture[1], "images/tyre2.bmp");
    t1.generate();

    glGenTextures(1, &texture[2]);
    Texture t2(texture[2], "images/front_glass.bmp");
    t2.generate();

    glGenTextures(1, &texture[3]);
    Texture t3(texture[3], "images/rim.bmp");
    t3.generate();

    glGenTextures(1, &texture[4]);
    Texture t4(texture[4], "images/front_left.bmp");
    t4.generate();

    glGenTextures(1, &texture[5]);
    Texture t5(texture[5], "images/headlight.bmp");
    t5.generate();

    glGenTextures(1, &texture[6]);
    Texture t6(texture[6], "images/hood_top.bmp");
    t6.generate();

    glGenTextures(1, &texture[7]);
    Texture t7(texture[7], "images/torso_front.bmp");
    t7.generate();

    glGenTextures(1, &texture[8]);
    Texture t8(texture[8], "images/rainbow.bmp");
    t8.generate();

    glGenTextures(1, &texture[9]);
    Texture t9(texture[9], "images/autobots.bmp");
    t9.generate();

    glGenTextures(1, &texture[10]);
    Texture t10(texture[10], "images/back_suspension.bmp");
    t10.generate();

    glGenTextures(1, &texture[11]);
    Texture t11(texture[11], "images/head.bmp");
    t11.generate();

    glGenTextures(1, &texture[12]);
    Texture t12(texture[12], "images/lower_leg.bmp");
    t12.generate();

    glGenTextures(1, &texture[13]);
    Texture t13(texture[13], "images/upper_leg.bmp");
    t13.generate();

    glGenTextures(1, &texture[14]);
    Texture t14(texture[14], "images/lower_hand.bmp");
    t14.generate();

    glGenTextures(1, &texture[15]);
    Texture t15(texture[15], "images/upper_hand.bmp");
    t15.generate();

    glGenTextures(1, &texture[16]);
    Texture t16(texture[16], "images/side_glass.bmp");
    t16.generate();

    glDisable(GL_TEXTURE_2D);
};

///camera
void optimus_t::set_camera_head(void){
  float pos_x = 0;
  float pos_y =  torso_yl + 2*radius*throat_yl; //center of head looking horizontal front
  float pos_z =  torso_zl;
  float center_x = 0;
  float center_y =  pos_y;
  float center_z =  2*torso_zl;

  gluLookAt(pos_x,pos_y,pos_z,
      center_x, center_y, center_z,
      0, 1, 0); //vertical is y direction

  glTranslatef(0, -1*throat_translate_y,0);
  glRotatef(-1*body_rotation_y,0,1,0);
  glTranslatef(-1*forword_backword_movement_x,0,-1*forword_backword_movement_z);
  // glRotatef(-1*body_rotation_z,0,0,1);
  // glRotatef(-1*body_rotation_x,1,0,0);
}

void optimus_t::set_camera_top(void){
  float pos_x = 0;
  float pos_y =  torso_yl + 10*radius*throat_yl; //center of head looking horizontal front
  float pos_z =  -14*torso_zl;
  float center_x = 0;
  float center_y =  pos_y -2*radius*throat_yl;
  float center_z =  torso_zl + lower_leg_l + uper_leg_l;

  gluLookAt(pos_x,pos_y,pos_z,
      center_x, center_y, center_z,
      0, (center_z - pos_z) , -1*(center_y-pos_y)); //vertical is y direction

  glTranslatef(0, -1*throat_translate_y,0);
  glRotatef(-1*body_rotation_y,0,1,0);
  glTranslatef(-1*forword_backword_movement_x,0,-1*forword_backword_movement_z);
  
}




void optimus_t::hierarchi(){
  glPushMatrix();  
    //glLoadIdentity(); SHOULD NOT BE HERE. THIS CANCELS THE EFFECT OF GLULOOKAT which also works on modelview stack

    //body rotation
     // glScalef(0.04, 0.04, 0.04);
    
      //move body forword
    glTranslatef(forword_backword_movement_x,0,forword_backword_movement_z);
  
  //       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  SHOULD NOT BE HERE.
         // glRotatef(body_rotation_x,1,0,0);
         glRotatef(body_rotation_y,0,1,0);
         // glRotatef(body_rotation_z,0,0,1);
        
      
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
        glRotatef(truck_ceiling_rotation,1,0,0);
        glCallList(id_truck_ceiling);
      glPopMatrix();
      //throat
      glPushMatrix();
        glTranslatef(0, throat_translate_y,0);
        glTranslatef(0,torso_yl,0);
        glRotatef(180, 0, 1, 0);
        glPushMatrix();
          glScalef(throat_xl,throat_yl,throat_zl);
          glColor4f(0.39,0.1638,0.3033,1.0);
          glCallList(id_hemisphere);
        glPopMatrix();
        //head
        glPushMatrix();
          glTranslatef(0,throat_yl+radius*1.3,0);
          glScalef(1,1.3, 1);
          glColor4f(1,0.2528,0.49,1.0);
          glCallList(id_sphere);
        glPopMatrix();
        
      glPopMatrix();

      //back left weel slab
        glPushMatrix();
          glTranslatef((torso_xl+back_weel_slab_xl),-1*torso_yl,-1*torso_zl);
          glRotatef(back_weel_slab_rotation,1,0,0);
          glPushMatrix();
            glColor4f(0.84,0.7669,0.1092,1.0);
            glCallList(id_back_weel_slab);
          glPopMatrix();
          //back weel
          glPushMatrix();
            glTranslatef(back_weel_slab_xl,0,-2*back_weel_slab_zl);
            glRotatef(90,0,1,0);
            glRotatef(weel_rotation,0,0,1);
            glColor4f(0.0588,0.2528,0.49,1.0);
            glCallList(id_weel);
          glPopMatrix();
        glPopMatrix();
      //back right weel slab
        glPushMatrix();
          glTranslatef(-(torso_xl+back_weel_slab_xl),-1*torso_yl,-1*torso_zl);
          glRotatef(back_weel_slab_rotation,1,0,0);
          glPushMatrix();
            glColor4f(0.84,0.7669,0.1092,1.0);
            glCallList(id_back_weel_slab);
          glPopMatrix();
          //back weel
          glPushMatrix();
            glTranslatef(-1*back_weel_slab_xl,0,-2*back_weel_slab_zl);
            glRotatef(90,0,1,0);
            glRotatef(weel_rotation,0,0,1);
            glColor4f(0.0588,0.2528,0.49,1.0);
            glCallList(id_weel);
          glPopMatrix();
        glPopMatrix();

      //left hand  
      glPushMatrix();
         glTranslatef(torso_xl,torso_yl,0.0f);
         glRotatef(solder_rotation_xl,1,0,0);
         glRotatef(solder_rotation_yl,0,1,0);
         glRotatef(solder_rotation_zl,0,0,1);
              
         glPushMatrix();
           glColor4f(0.0,1.0,0.0,1.0);
           glCallList(id_uper_hand);
         glPopMatrix();

        glPushMatrix();
          glTranslatef(uper_hand_l*2,0.0f,0.0f);
          glRotatef(elbows_rotation_l,0,0,1);
          
          glPushMatrix();
            glColor4f(0.0,0.0,1.0,1.0);
            glCallList(id_lower_hand);
          glPopMatrix();
                  //side gate
          glPushMatrix();
            glTranslatef(0.0f,0.50f,0.0f);
            glRotatef(side_gate_rotation,1,0,0);
            glCallList(id_side_gate);
          glPopMatrix();

        glPopMatrix();
      glPopMatrix();
      //right hand
      glPushMatrix();
         glTranslatef(-1*torso_xl,torso_yl,0.0f);
         glRotatef(solder_rotation_xr,1,0,0);
         glRotatef(solder_rotation_yr,0,1,0);
         glRotatef(solder_rotation_zr,0,0,1);
              
         glPushMatrix();
           glColor4f(0.0,1.0,0.0,1.0);
           glScalef(-1,1,1);
           glCallList(id_uper_hand);
         glPopMatrix();

        glPushMatrix();
          glTranslatef(-1*uper_hand_l*2,0.0f,0.0f);
          glRotatef(elbows_rotation_r,0,0,1);
          glColor4f(0.0,0.0,1.0,1.0);
          glScalef(-1,1,1);
          glPushMatrix();
            glCallList(id_lower_hand);
          glPopMatrix();
                  //side gate
          glPushMatrix();
            glTranslatef(0,0.50f,0.0f);
            glRotatef(side_gate_rotation,1,0,0);
            glCallList(id_side_gate);
          glPopMatrix();

        glPopMatrix();
      glPopMatrix();
      
      //waist
      glPushMatrix();
        glTranslatef(0,-1*torso_yl,0);
        glRotatef(waist_rotation,0,1,0);

        glPushMatrix();
          glCallList(id_waist);
        glPopMatrix();

        //left leg
        glPushMatrix();
          glTranslatef(torso_xl/2,-2*waist_yl,0);
          glRotatef(uper_leg_rotation_xl,1,0,0);
          glRotatef(uper_leg_rotation_zl,0,0,1);
          glPushMatrix();
            glCallList(id_uper_leg);
          glPopMatrix();
          //lower leg
          glPushMatrix();
            glTranslatef(0,-2*uper_leg_l,0);
            glRotatef(lower_leg_rotation_l,1,0,0);
            glPushMatrix();
              glCallList(id_lower_leg);
            glPopMatrix();
            glPushMatrix();
              glTranslatef(lower_leg_xl+front_weel_slab_xl,(-1*lower_leg_l),0);
              glRotatef(front_weel_slab_rotation,1,0,0);
              
              glPushMatrix();
                glCallList(id_front_weel_slab);
              glPopMatrix();
              
              glPushMatrix();
                glTranslatef(front_weel_slab_xl+weel_width/2,-1*front_weel_slab_yl,0);
                glRotatef(90,0,1,0);
                glRotatef(-weel_rotation,0,0,1);
                glColor4f(0.0588,0.2528,0.49,1.0);
                glCallList(id_weel);
              glPopMatrix();  
            glPopMatrix();
            //hood feet
            glPushMatrix();
              glTranslatef(0,-2*lower_leg_l,-1 );
              glRotatef(hood_feet_rotation_xl1,1,0,0);
              glPushMatrix();
                //glColor4f(0.105,0.5,0.1708,1.0);
                glCallList(id_hood_feet_left);
              glPopMatrix();
              glPushMatrix();
                glTranslatef(0,0,-2*hood_feet_zl);
                glRotatef(hood_feet_rotation_xl2,1,0,0);
                glPushMatrix();
                  //glColor4f(0.1098,0.61,0.3932,1.0);
                  glCallList(id_hood_feet_left);
                glPopMatrix();
                //front left glass
                glPushMatrix();
                  glTranslatef(0,2*front_glass_yl,-2*hood_feet_zl);
                  glRotatef(front_glass_rotation,1,0,0);
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
          glRotatef(uper_leg_rotation_xr,1,0,0);
          glRotatef(uper_leg_rotation_zr,0,0,1);
          glPushMatrix();
            glCallList(id_uper_leg);
          glPopMatrix();
          
          glPushMatrix();
            glTranslatef(0,-2*uper_leg_l,0);
            glRotatef(lower_leg_rotation_r,1,0,0);
            glPushMatrix();
              glCallList(id_lower_leg);
            glPopMatrix();
            glPushMatrix();
              glTranslatef(-1*(lower_leg_xl+front_weel_slab_xl),(-1*lower_leg_l),0);
              glRotatef(front_weel_slab_rotation,1,0,0);
              glPushMatrix();
                glCallList(id_front_weel_slab);
              glPopMatrix();
              glPushMatrix();
                glTranslatef(-1*(front_weel_slab_xl+weel_width/2),-1*front_weel_slab_yl,0);
                glRotatef(90,0,1,0);
                glRotatef(-weel_rotation,0,0,1);
                glColor4f(0.0588,0.2528,0.49,1.0);
                glCallList(id_weel);
              glPopMatrix();
            glPopMatrix();
            //hood feet
            glPushMatrix();
              glTranslatef(0,-2*lower_leg_l,-1 );
              glRotatef(hood_feet_rotation_xr1,1,0,0);
              glPushMatrix();
                glColor4f(0.105,0.5,0.1708,1.0);
                glCallList(id_hood_feet_left);
              glPopMatrix();
              glPushMatrix();
                glTranslatef(0,0,-2*hood_feet_zl);
                glRotatef(hood_feet_rotation_xr2,1,0,0);
                glPushMatrix();
                glColor4f(0.1098,0.61,0.3932,1.0);
                glCallList(id_hood_feet_left);
                glPopMatrix();
                //front left glass
                glPushMatrix();
                  glTranslatef(0,2*front_glass_yl,-2*hood_feet_zl);
                  glRotatef(front_glass_rotation,1,0,0);
                  glColor4f(1,1,1,1.0);
                  glCallList(id_front_glass);
                glPopMatrix();
              glPopMatrix();
            glPopMatrix();
          glPopMatrix();                
        glPopMatrix();
      glPopMatrix();
  glPopMatrix();   
}


void optimus_t::reset_transformer_config(){
    solder_rotation_xl=0;
    solder_rotation_yl=0;
    solder_rotation_zl=0;
    elbows_rotation_l=0;
    solder_rotation_xr=0;
    solder_rotation_yr=0;
    solder_rotation_zr=0;
    elbows_rotation_r=0;
    waist_rotation=0;
    lower_leg_rotation_l=0;
    lower_leg_rotation_r=0;
    front_weel_slab_rotation=180;
    uper_leg_rotation_xl=0;
    uper_leg_rotation_zl=0;
    uper_leg_rotation_xr=0;
    uper_leg_rotation_zr=0;
    back_weel_slab_rotation=55;
    hood_feet_rotation_xl1=-110;
    hood_feet_rotation_xl2=-140;
    hood_feet_rotation_xr1=-110;
    hood_feet_rotation_xr2=-140;
    throat_translate_y = 0;
    truck_ceiling_rotation = -150;
    front_glass_rotation =0;
    side_gate_rotation=-90;
    weel_rotation=0;
    forword_backword_movement_z=0.0;
    forword_backword_movement_x=0.0;
}

void optimus_t::reset_car_config(){
	solder_rotation_xl=0;
	solder_rotation_yl=-90;
	solder_rotation_zl=-90;
	elbows_rotation_l=90;
	solder_rotation_xr=0;
	solder_rotation_yr=90;
	solder_rotation_zr=90;
	elbows_rotation_r=-90;
	waist_rotation=180;
	lower_leg_rotation_l=0;
	lower_leg_rotation_r=0;
	front_weel_slab_rotation=0;
	uper_leg_rotation_xl=90;
	uper_leg_rotation_zl=0;
	uper_leg_rotation_xr=90;
	uper_leg_rotation_zr=0;
	back_weel_slab_rotation=-20;
	hood_feet_rotation_xl1=0;
	hood_feet_rotation_xl2=0;
	hood_feet_rotation_xr1=0;
	hood_feet_rotation_xr2=0;
	throat_translate_y = -2*torso_yl;
	truck_ceiling_rotation = 90;
	front_glass_rotation=120;
	side_gate_rotation=0;
  weel_rotation=0;
  forword_backword_movement_z=0.0;
  forword_backword_movement_x=0.0;
}

void optimus_t::reset_view_angle(){
    body_rotation_x=0;
    body_rotation_y=0;
    body_rotation_z=0;
}

void optimus_t::optimus_key_callback(int key, int scancode, int action, int mods){
	// if(key==GLFW_KEY_DOWN && action == GLFW_PRESS)
 //      body_rotation_x = (body_rotation_x - 10)%360;
 //    else if(key==GLFW_KEY_UP && action == GLFW_PRESS)
 //      body_rotation_x = (body_rotation_x + 10)%360;    
    if(key==GLFW_KEY_LEFT && action == GLFW_PRESS)
      body_rotation_y = (body_rotation_y + 10)%360;
    else if(key==GLFW_KEY_RIGHT && action == GLFW_PRESS)
      body_rotation_y = (body_rotation_y - 10)%360;    
    // else if(key==GLFW_KEY_Z && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
    //   body_rotation_z = (body_rotation_z - 10)%360;
    // else if(key==GLFW_KEY_Z && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
    //   body_rotation_z = (body_rotation_z + 10)%360;    
    
    // uper left hand rotation
    else if(key==GLFW_KEY_E && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_zl = (solder_rotation_zl + 10)%360;    
    else if(key==GLFW_KEY_E && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_zl = (solder_rotation_zl - 10)%360;
    else if(key==GLFW_KEY_Q && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_xl = (solder_rotation_xl + 10)%360;    
    else if(key==GLFW_KEY_Q && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_xl = (solder_rotation_xl - 10)%360;      
    else if(key==GLFW_KEY_W && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_yl = (solder_rotation_yl + 10)%360;    
    else if(key==GLFW_KEY_W && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_yl = (solder_rotation_yl - 10)%360;      
    //lower left hand rotation
    else if(key==GLFW_KEY_R && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      elbows_rotation_l = (elbows_rotation_l + 10)%360;    
    else if(key==GLFW_KEY_R && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      elbows_rotation_l = (elbows_rotation_l - 10)%360;  
    // uper right hand rotation
    else if(key==GLFW_KEY_3 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_zr = (solder_rotation_zr + 10)%360;    
    else if(key==GLFW_KEY_3 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_zr = (solder_rotation_zr - 10)%360;
    else if(key==GLFW_KEY_1 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_xr = (solder_rotation_xr + 10)%360;    
    else if(key==GLFW_KEY_1 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_xr = (solder_rotation_xr - 10)%360;      
    else if(key==GLFW_KEY_2 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      solder_rotation_yr = (solder_rotation_yr + 10)%360;    
    else if(key==GLFW_KEY_2 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      solder_rotation_yr = (solder_rotation_yr - 10)%360;      
    //lower right hand rotation
    else if(key==GLFW_KEY_4 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      elbows_rotation_r = (elbows_rotation_r + 10)%360;    
    else if(key==GLFW_KEY_4 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      elbows_rotation_r = (elbows_rotation_r - 10)%360;  
    // back weel slab rotarion
    else if (key==GLFW_KEY_F && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      back_weel_slab_rotation = (back_weel_slab_rotation + 10)%360;
    else if (key==GLFW_KEY_F && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      back_weel_slab_rotation = (back_weel_slab_rotation - 10)%360;
    
    // waist rotation
    else if (key==GLFW_KEY_M && action == GLFW_PRESS  && !(mods & GLFW_MOD_SHIFT))
      waist_rotation = (waist_rotation + 10)%360;
    else if (key==GLFW_KEY_M && action == GLFW_PRESS  && (mods & GLFW_MOD_SHIFT))
      waist_rotation = (waist_rotation - 10)%360;
    //uper left leg toration
    else if (key == GLFW_KEY_P && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_xl = (uper_leg_rotation_xl + 10)%360;
    else if (key == GLFW_KEY_P && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_xl = (uper_leg_rotation_xl - 10)%360;
    else if (key == GLFW_KEY_O && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_zl = (uper_leg_rotation_zl + 10)%360;
    else if (key == GLFW_KEY_O && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_zl = (uper_leg_rotation_zl - 10)%360;
    //uper right leg rotation
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_xr = (uper_leg_rotation_xr + 10)%360;
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_xr = (uper_leg_rotation_xr - 10)%360;
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      uper_leg_rotation_zr = (uper_leg_rotation_zr + 10)%360;
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)) 
      uper_leg_rotation_zr = (uper_leg_rotation_zr - 10)%360;

    //lower left leg
    else if (key==GLFW_KEY_I && action== GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      lower_leg_rotation_l = (lower_leg_rotation_l + 10)%360;
    else if (key==GLFW_KEY_I && action== GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      lower_leg_rotation_l = (lower_leg_rotation_l - 10)%360;
    //lower right leg
    else if (key==GLFW_KEY_8 && action== GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))  
      lower_leg_rotation_r = (lower_leg_rotation_r + 10)%360;
    else if (key==GLFW_KEY_8 && action== GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      lower_leg_rotation_r = (lower_leg_rotation_r - 10)%360;
    //front leg slab contain weel rotation
    else if(key== GLFW_KEY_L && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      front_weel_slab_rotation = (front_weel_slab_rotation + 10)%360;
    else if(key== GLFW_KEY_L && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      front_weel_slab_rotation = (front_weel_slab_rotation - 10)%360;
    //hood  left feet rotation
    else if (key == GLFW_KEY_K && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xl1 = (hood_feet_rotation_xl1 + 10)%360;
    else if (key == GLFW_KEY_K && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xl1 = (hood_feet_rotation_xl1 - 10)%360;
    else if (key == GLFW_KEY_J && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xl2 = (hood_feet_rotation_xl2 + 10)%360;
    else if (key == GLFW_KEY_J && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xl2 = (hood_feet_rotation_xl2 - 10)%360;
    //hood  right feet rotation
    else if (key == GLFW_KEY_H && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xr1 = (hood_feet_rotation_xr1 + 10)%360;
    else if (key == GLFW_KEY_H && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xr1 = (hood_feet_rotation_xr1 - 10)%360;
    else if (key == GLFW_KEY_G && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xr2 = (hood_feet_rotation_xr2 + 10)%360;
    else if (key == GLFW_KEY_G && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      hood_feet_rotation_xr2 = (hood_feet_rotation_xr2 - 10)%360;
    else if (key == GLFW_KEY_A && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      throat_translate_y += 0.3;
    else if (key == GLFW_KEY_A && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      throat_translate_y -= 0.3;
    else if (key == GLFW_KEY_D && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      truck_ceiling_rotation = (truck_ceiling_rotation + 10)%360;
    else if (key == GLFW_KEY_D && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      truck_ceiling_rotation = (truck_ceiling_rotation - 10)%360;
    else if (key == GLFW_KEY_T && action == GLFW_PRESS)
      reset_transformer_config();
    else if (key == GLFW_KEY_C && action == GLFW_PRESS)
      reset_car_config();
    else if (key == GLFW_KEY_V && action == GLFW_PRESS)
      reset_view_angle();
    else if (key == GLFW_KEY_B && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      front_glass_rotation = (front_glass_rotation + 10)%360;
    else if (key == GLFW_KEY_B && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      front_glass_rotation = (front_glass_rotation - 10)%360;
    else if (key == GLFW_KEY_X && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
      side_gate_rotation = (side_gate_rotation + 10)%360;
    else if (key == GLFW_KEY_X && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
      side_gate_rotation = (side_gate_rotation - 10)%360;
    //weel rotation about z axis
    else if (key == GLFW_KEY_UP /*&& action == GLFW_PRESS*/ /*&& !(mods & GLFW_MOD_SHIFT)*/){
      weel_rotation = (weel_rotation + 10)%360;
      forword_backword_movement_z = forword_backword_movement_z + 2.0*PI*weel_radius*(1.0/18.0)*cos(body_rotation_y*PI/180.0);
      forword_backword_movement_x = forword_backword_movement_x + 2.0*PI*weel_radius*(1.0/18.0)*sin(body_rotation_y*PI/180.0);
    }
    else if (key == GLFW_KEY_DOWN /*&& action == GLFW_PRESS*/ /*&& (mods & GLFW_MOD_SHIFT)*/){
      weel_rotation = (weel_rotation - 10)%360;
      forword_backword_movement_z = forword_backword_movement_z - 2.0*PI*weel_radius*(1.0/18.0)*cos(body_rotation_y*PI/180.0);
      forword_backword_movement_x = forword_backword_movement_x - 2.0*PI*weel_radius*(1.0/18.0)*sin(body_rotation_y*PI/180.0);
    }
}


//Structure/Parts
//unit weel
void optimus_t::unit_weel(){
  
  glNewList(id_unit_weel,GL_COMPILE);
  glTranslatef(0,unit_weel_y,0);
  
  glColor4f(1, 0.44, .555, 1);
  glBegin(GL_TRIANGLE_FAN);
  calculate_normal(0.0f,0.0f,0.20f, 1.0f,0.0f,0.20f, 0.8660f,0.50f,0.20f, normal_buffer);
  glNormal3dv(normal_buffer);
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
  calculate_normal(0.0f,0.0f,-0.20f, 1.0f,0.0f,-0.20f, 0.8660f,0.50f,-0.20f, normal_buffer);
  glNormal3dv(normal_buffer);
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
  calculate_normal(1.0f,0.0f,0.20f, 0.0f,0.0f,-0.20f, 0.8660f,0.50f,0.20f, normal_buffer);
  glNormal3dv(normal_buffer);
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

void optimus_t::weel(){
  glNewList(id_weel,GL_COMPILE);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[3]);
  glColor4f(1, 1, 1, 1);
  glBegin(GL_TRIANGLES);
    for(int i=0;i<360;i+=weel_angle){
      float radian = i* PI/180.0;
      float radian2 = (i+weel_angle) * PI/180.0;
      calculate_normal(0,0,0, weel_radius*cos(radian),weel_radius*sin(radian),weel_width/2, weel_radius*cos(radian2),weel_radius*sin(radian2),weel_width/2, normal_buffer);
      glNormal3dv(normal_buffer);
      glTexCoord2f(0.5f, 0.5f); glVertex3f(0,0,0);
      glTexCoord2f((cos(radian)+1)/2, (sin(radian)+1)/2); glVertex3f(weel_radius*cos(radian),weel_radius*sin(radian),weel_width/2);
      glTexCoord2f((cos(radian2)+1)/2, (sin(radian2)+1)/2); glVertex3f(weel_radius*cos(radian2),weel_radius*sin(radian2),weel_width/2);
    }
  glEnd();
  glBegin(GL_TRIANGLES);
    for(int i=0;i<360;i+=weel_angle){
      float radian = i* PI/180.0;
      float radian2 = (i+weel_angle) * PI/180.0;
      calculate_normal(0,0,0, weel_radius*cos(radian2),weel_radius*sin(radian2),-weel_width/2, weel_radius*cos(radian),weel_radius*sin(radian),-weel_width/2, normal_buffer);
      glNormal3dv(normal_buffer);
      glTexCoord2f(0.5f, 0.5f); glVertex3f(0,0,0);
      glTexCoord2f((cos(radian2)+1)/2, (sin(radian2)+1)/2); glVertex3f(weel_radius*cos(radian2),weel_radius*sin(radian2),-weel_width/2);
      glTexCoord2f((cos(radian)+1)/2, (sin(radian)+1)/2); glVertex3f(weel_radius*cos(radian),weel_radius*sin(radian),-weel_width/2);
    }
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[1]);

  glColor4f(1, 1, 1, 1);
  glBegin(GL_QUADS);
    for(int i=0;i<360;i+=weel_angle){
      float radian = i* PI/180.0;
      float radian2 = (i+weel_angle) * PI/180.0;
      calculate_normal(weel_radius*cos(radian),weel_radius*sin(radian),weel_width/2, weel_radius*cos(radian),weel_radius*sin(radian),-1*weel_width/2, weel_radius*cos(radian2),weel_radius*sin(radian2),-1*weel_width/2, normal_buffer);
      glNormal3dv(normal_buffer);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(weel_radius*cos(radian),weel_radius*sin(radian),weel_width/2);
      glTexCoord2f(1.0f, 0.0f); glVertex3f(weel_radius*cos(radian),weel_radius*sin(radian),-1*weel_width/2);
      
      glTexCoord2f(1.0f, 1.0f); glVertex3f(weel_radius*cos(radian2),weel_radius*sin(radian2),-1*weel_width/2);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(weel_radius*cos(radian2),weel_radius*sin(radian2),weel_width/2);
      
    }
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEndList();
}
//sphere
void optimus_t::sphere_layer(float R, float angle1, float angle2){
    float z1 = R * sin(angle1 * PI/180);
    float z2 = R * sin(angle2 * PI/180);
    float r1 = sqrt(R*R - z1*z1);
    float r2 = sqrt(R*R - z2*z2);

    float theta = 0;

    for(theta = 90; theta < 450; theta+=ANGLE){
      float radian = theta * PI/180.0; 
      float radian1 = (theta+ANGLE) * PI/180.0; 
      glBegin(GL_QUADS);
      calculate_normal(r1 * cos(radian), z1, r1 * sin(radian), r2 * cos(radian), z2, r2 * sin(radian), r2 * cos(radian1), z2, r2 * sin(radian1), normal_buffer);
      glNormal3dv(normal_buffer);
      glTexCoord2f((theta-90)/360, 0.5*(1+angle1/90)); glVertex3f(r1 * cos(radian), z1, r1 * sin(radian));
      glTexCoord2f((theta-90)/360, 0.5*(1+angle2/90)); glVertex3f(r2 * cos(radian), z2, r2 * sin(radian));
      glTexCoord2f((theta-90+ANGLE)/360, 0.5*(1+angle2/90)); glVertex3f(r2 * cos(radian1), z2, r2 * sin(radian1));
      glTexCoord2f((theta-90+ANGLE)/360, 0.5*(1+angle1/90)); glVertex3f(r1 * cos(radian1), z1, r1 * sin(radian1));
      
      glEnd();
    }
}
  
void optimus_t::sphere(){
  glNewList(id_sphere,GL_COMPILE);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[11]);
  glColor4f(1, 1, 1, 1);

  float delta_angle = 90.0 / VERTICAL_ANGLE_PARTS;

  float v_angle = 0;
  for(int i=0; i < VERTICAL_ANGLE_PARTS; i++){
      sphere_layer(radius, v_angle, v_angle+delta_angle);
      v_angle += delta_angle;
  }
  
  v_angle=0;
  for(int i=0; i < VERTICAL_ANGLE_PARTS; i++){
      sphere_layer(radius, v_angle-delta_angle, v_angle);
      v_angle -= delta_angle;
  }
  glDisable(GL_TEXTURE_2D);
  glEndList();
}
//hamisphare
void optimus_t::hemisphere(){
  glNewList(id_hemisphere,GL_COMPILE);
  float delta_angle = 90.0 / VERTICAL_ANGLE_PARTS;

  float v_angle = 0;
  for(int i=0; i < VERTICAL_ANGLE_PARTS; i++){
      sphere_layer(radius, v_angle, v_angle+delta_angle);
      v_angle += delta_angle;
  }
  
  glEndList();
}

void optimus_t::unit_cube(){
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

}

void optimus_t::torso(){
  glNewList(id_torso, GL_COMPILE);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[7]);
  glScalef(torso_xl,torso_yl,torso_zl);
  
  glColor4f(1, 1, 1, 1);
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,1.0f); 
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBindTexture(GL_TEXTURE_2D, texture[8]);
  //glColor4f(1, 0, 0, 1);
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  //glColor4f(0, 1,0, 1);
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  //glColor4f(0, 1, 0, 1);
  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  //glColor4f(0, 0, 1, 1);
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  //glColor4f(0, 0,1, 1);
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEndList();
}
void optimus_t::uper_hand(){
  glNewList(id_uper_hand,GL_COMPILE);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[15]);
  glColor4f(1, 1, 1, 1);

  glTranslatef(uper_hand_l,0,0);
  glScalef(uper_hand_l,1,1);
  //unit_cube();
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,1.0f); 
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);

  glColor4f(0.37,0.3647 ,0.0518, 1);
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glColor4f(0.37,0.3647 ,0.0518, 1);
  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[15]);
  glColor4f(1, 1, 1, 1);

  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);


  glEndList();
}

void optimus_t::lower_hand(){
  glNewList(id_lower_hand,GL_COMPILE);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[14]);
  glColor4f(1, 1, 1, 1);

  glTranslatef(lower_hand_l,0,0);
  glScalef(lower_hand_l,1,1);
  //unit_cube();
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,1.0f); 
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);

  glColor4f(0.3989,0.1056 ,0.48, 1);
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glColor4f(0.3989,0.1056 ,0.48, 1);
  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[14]);
  glColor4f(1, 1, 1, 1);

  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glDisable(GL_TEXTURE_2D);

  glEndList();
}
//waist
void optimus_t::waist(){
  glNewList(id_waist,GL_COMPILE);
  glTranslatef(0,-1*waist_yl,0);
  glScalef(waist_xl,waist_yl,waist_zl);
  unit_cube();
  glEndList();
}
//uper_leg
void optimus_t::uper_leg(){
  glNewList(id_uper_leg,GL_COMPILE);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[13]);
  glColor4f(1,1 ,1, 1);

  glTranslatef(0,-1*uper_leg_l,0);
  glScalef(1,uper_leg_l,1);
  
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,1.0f); 
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  

  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);

  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glEndList();

}
//lower leg
  
void optimus_t::lower_leg(){
  glNewList(id_lower_leg,GL_COMPILE);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[12]);

  glTranslatef(0,-1*lower_leg_l,0);
  glScalef(lower_leg_xl,lower_leg_l,1);
  
  glColor4f(1,1 ,1, 1);
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,1.0f); 
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  // glColor4f(0.2366, 0.1056, 0.48, 1);

  glEnable(GL_TEXTURE_2D);
  glColor4f(1, 1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
   
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEndList();

}
//front weel slab
void optimus_t::front_weel_slab(){
  glNewList(id_front_weel_slab, GL_COMPILE);
  glTranslatef(0,-1*front_weel_slab_yl,0);
  glScalef(front_weel_slab_xl,front_weel_slab_yl,1);

  glColor4f(0.28,0.0616, 1, 1);
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glColor4f(0.28,0.0616, 1, 1);
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.3989,0.1056 ,0.8, 1);
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glColor4f(0.3989,0.1056 ,0.8, 1);
  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glColor4f(0.2366, 0.1056, 0.48, 1);
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glEndList();

}
//back weel slab
void optimus_t::back_weel_slab(){
  glNewList(id_back_weel_slab, GL_COMPILE);
  glTranslatef(0,0,-1*back_weel_slab_zl);
  glScalef(back_weel_slab_xl,1,back_weel_slab_zl);

  glColor4f(0.75, 0.7273, 0.0675, 1);
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[10]);
  
  glColor4f(1, 1, 1, 1);

  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glEndList();

}
//truck hood
void optimus_t::hood_feet(){
  glNewList(id_hood_feet,GL_COMPILE);
  glTranslatef(0,hood_feet_yl,-1*hood_feet_zl);
  glScalef(hood_feet_xl,hood_feet_yl,hood_feet_zl);
  
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glEndList();
}
void optimus_t::hood_feet_left(){
  glNewList(id_hood_feet_left,GL_COMPILE);
  glTranslatef(0,hood_feet_yl,-1*hood_feet_zl);
  glScalef(hood_feet_xl,hood_feet_yl,hood_feet_zl);
  

  glColor4f(0.1098,0.61,0.3932,1.0);
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glEnable(GL_TEXTURE_2D);
  glColor4f(1, 1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f);glVertex3f(1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f);glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.5f, 1.0f);glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.5f, 0.0f);glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.5f, 1.0f);glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(0.5f, 0.0f);glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  glColor4f(0.1098,0.61,0.3932,1.0);
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glEnable(GL_TEXTURE_2D);
  glColor4f(1, 1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, texture[4]);
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
   
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEndList();

}


void optimus_t::front_glass(){
  glNewList(id_front_glass,GL_COMPILE);
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glColor4f(1, 1, 1, 0.2);
  set_glass_material();

  glTranslatef(0,-1*front_glass_yl,-1*front_glass_zl);
  glScalef(front_glass_xl,front_glass_yl,front_glass_zl);
  
  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f); 
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glColor4f(1, 1, 1, 1);
  set_normal_material();
  glEndList();
}
//truck ceiling
void optimus_t::truck_ceiling(){
  glNewList(id_truck_ceiling,GL_COMPILE);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[9]);
  glColor4f(1, 1, 1, 1);
  glTranslatef(0,torso_zl+lower_hand_l/2,0);
  glScalef(torso_xl,torso_zl+lower_hand_l/2,truck_ceiling_width);

  glBegin(GL_QUADS);            //front face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,1.0f,1.0f); 
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,-1.0f,1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,1.0f,1.0f);
  glEnd();
  
  glBegin(GL_QUADS);          //back face       
  calculate_normal(-1.0f,1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,1.0f,-1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f,-1.0f,-1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  glColor4f(0.28,0.0616, 1, 1);
  glBegin(GL_QUADS);          //left face
  calculate_normal(-1.0f,1.0f,1.0f, -1.0f,1.0f,-1.0f, -1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();

  glBegin(GL_QUADS);          //right face
  calculate_normal(1.0f,1.0f,1.0f, 1.0f,-1.0f,1.0f, 1.0f,-1.0f,-1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //top face        
  calculate_normal(-1.0f,1.0f,-1.0f, -1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,1.0f,-1.0f);
  glVertex3f(-1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);
  glVertex3f(1.0f,1.0f,-1.0f);
  glEnd();
  
  glBegin(GL_QUADS);        //bottom face
  calculate_normal(-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(-1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,-1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);
  glVertex3f(-1.0f,-1.0f,1.0f);
  glEnd();
  glEndList();
}
//side gate ot truck
void optimus_t::side_gate(){
  glNewList(id_side_gate,GL_COMPILE);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[16]);
  glColor4f(1, 1, 1, 1);

  glScalef(1,1,side_gate_width);
                    //front face
  glBegin(GL_QUADS);
  calculate_normal(0.0f,0.0f,0.5f, lower_hand_l*2,0.0f,0.5f, lower_hand_l*1.5,uper_hand_l,0.5f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,0.0f,0.5f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(lower_hand_l*2,0.0f,0.5f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(lower_hand_l*1.5,uper_hand_l,0.5f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f,uper_hand_l,0.5f);
  glEnd();
                    //back face
  glBegin(GL_QUADS);
  calculate_normal(0.0f,0.0f,-0.5f, 0.0f,uper_hand_l,-0.5f, lower_hand_l*1.5,uper_hand_l,-0.5f, normal_buffer);
  glNormal3dv(normal_buffer);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,0.0f,-0.5f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f,uper_hand_l,-0.5f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(lower_hand_l*1.5,uper_hand_l,-0.5f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(lower_hand_l*2,0.0f,-0.5f);
  glEnd();
  glDisable(GL_TEXTURE_2D);

                    //left face

  glBegin(GL_QUADS);
  calculate_normal(0.0f,0.0f,0.5f, 0.0f,uper_hand_l,0.5f, 0.0f,uper_hand_l,-0.5f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(0.0f,0.0f,0.5f);
  glVertex3f(0.0f,uper_hand_l,0.5f);
  glVertex3f(0.0f,uper_hand_l,-0.5f);
  glVertex3f(0.0f,0.0f,-0.5f);
  glEnd();
                    //right face
  glBegin(GL_QUADS);
  calculate_normal(lower_hand_l*2,0.0f,0.5f, lower_hand_l*1.5,uper_hand_l,0.5f, lower_hand_l*1.5,uper_hand_l,-0.5f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(lower_hand_l*2,0.0f,0.5f);
  glVertex3f(lower_hand_l*1.5,uper_hand_l,0.5f);
  glVertex3f(lower_hand_l*1.5,uper_hand_l,-0.5f);
  glVertex3f(lower_hand_l*2,0.0f,-0.5f);
  glEnd();
                    //top face
  glBegin(GL_QUADS);
  calculate_normal(0.0f,uper_hand_l,0.5f, lower_hand_l*1.5,uper_hand_l,0.5f, lower_hand_l*1.5,uper_hand_l,-0.5f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(0.0f,uper_hand_l,0.5f);
  glVertex3f(lower_hand_l*1.5,uper_hand_l,0.5f);
  glVertex3f(lower_hand_l*1.5,uper_hand_l,-0.5f);
  glVertex3f(0.0f,uper_hand_l,-0.5f);
  glEnd();
                    //bottom face
  glBegin(GL_QUADS);
  calculate_normal(0.0f,0.0f,0.5f, lower_hand_l*2,0.0f,0.5f, lower_hand_l*2,0.0f,-0.5f, normal_buffer);
  glNormal3dv(normal_buffer);
  glVertex3f(0.0f,0.0f,0.5f);
  glVertex3f(lower_hand_l*2,0.0f,0.5f);
  glVertex3f(lower_hand_l*2,0.0f,-0.5f);
  glVertex3f(0.0f,0.0f,-0.5f);
  glEnd();

  glEndList();
}
