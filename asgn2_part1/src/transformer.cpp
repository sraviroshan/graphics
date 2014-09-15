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


//! The pointer to the GLFW window
GLFWwindow* window;

//GLFW display callback
void oldrenderGL( void )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();                   // Reset The View
    //glTranslatef(-1.5f,0.0f,-6.0f);             // Move Left And Into The Screen
 
    glScalef(0.5, 0.5,  0.5);
    glRotatef(20,1.0f,0.0f,0.0f);             // Rotate The Pyramid On It's Y Axis (angle in degrees)
 
    glBegin(GL_TRIANGLES);                  // Start Drawing The Pyramid

    //front
    glColor3f(1.0f,0.0f,0.0f);          // Red
    glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);          // Left Of Triangle (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);          // Right Of Triangle (Front)

    //right
    glColor3f(0.0f,0.0f,1.0f);          // Blue
    glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);          // Left Of Triangle (Right)
    glVertex3f( 1.0f,-1.0f, -1.0f);         // Right Of Triangle (Right)

    //back
    glColor3f(0.0f,1.0f,0.0f);          // Green
    glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Back)
    glVertex3f( 1.0f,-1.0f, -1.0f);         // Left Of Triangle (Back)
    glVertex3f(-1.0f,-1.0f, -1.0f);         // Right Of Triangle (Back)

    //left
    glColor3f(1.0f,0.0f,0.0f);          // Red
    glVertex3f( 0.0f, 1.0f, 0.0f);          // Top Of Triangle (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);          // Left Of Triangle (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);          // Right Of Triangle (Left)
    glEnd();                        // Done Drawing The Pyramid
}

void renderGL(void){
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
