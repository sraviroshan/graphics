#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cmath>

#include "gl_framework.hpp"
#include "texture_utils.h"
#include "surrounding.h"

#define id_back_wall 100
#define x_wall 20
#define y_wall 20
#define z_wall 20

void surrounding_t::init_surrounding(void){
	back_wall();
	// front_wall();
	// left_wall();
	// right_wall();
	// top_wall();
	// floor_wall();
}

// Load bitmap images to form textures
void surrounding_t::load_textures() { 
    glEnable(GL_TEXTURE_2D);

    //texture for torso
    glGenTextures(1, &texture[0]);
    Texture t0(texture[0], "images/wall.bmp");
    t0.generate();

    glDisable(GL_TEXTURE_2D);
};

void surrounding_t::back_wall(){
	glNewList(id_back_wall, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
  	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);            //front face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1* x_wall,-1* y_wall,-1*z_wall); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1* x_wall,y_wall,-1*z_wall);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x_wall,y_wall,-1*z_wall);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x_wall,-1* y_wall,-1*z_wall);
	glEnd();

  	glDisable(GL_TEXTURE_2D);
	glEndList();
  	
}

void surrounding_t::surround_all(){
	glPushMatrix();
	  glScalef(0.04, 0.04, 0.04);
      glCallList(id_back_wall);
    glPopMatrix();
}
