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
#include <vector>
#include <stdlib.h>
#include "texture_utils.h"

extern GLFWwindow* window;

namespace csX75
{
  extern int MODE; //3 modes (0)recording, (1)testing, (2)playback(animation). Change using key <F12>
  extern vector<keyframe_t> saved_keyframes;
  extern int curr_keyframe_index;

  extern bool animation_on;
  extern bool playback_mode;
  extern int FPS;
  extern int NUM_INTER_FRAMES;
  extern string output_folder;
  extern string image_file_prefix;
  extern int interpolated_index_number; //from [0,NUM_INTER_FRAMES-1]
  extern int output_frame_number; //used for naming output images


  //! Initialize GL State
  void initGL(void);
 
  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  bool animate(); //returns true if success, false if last frame has been rendered

  void dump();

};

#endif
