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
#include "surrounding.h"
#include "texture_utils.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

#define NUM_MODES 3
#define USE_PERSPECTIVE true
#define NUM_CAMERAS 6
extern optimus_t optimus;
extern surrounding_t surrounding;

extern int camera_no;


namespace csX75
{
  string kf_file;
  vector<keyframe_t> saved_keyframes;
  int curr_keyframe_index;

  //for animation
  bool animation_on;
  bool playback_mode;
  int FPS;
  int NUM_INTER_FRAMES;
  string output_folder;
  string image_file_prefix;
  int interpolated_index_number; //from [0,NUM_INTER_FRAMES-1]
  int output_frame_number; //used for naming output images

  int MODE;
  int win_width;
  int win_height;

  //! Initialize GL State
  void initGL(void)
  {
    kf_file = "kf.txt";
    MODE = 0;
    curr_keyframe_index = saved_keyframes.size()-1; //@start of program -1
    animation_on = false;
    playback_mode = false;


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
      gluPerspective(70, (double)width/(double)height, 0.02, 4.0);
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

  void save_state(string filename){
      keyframe_t cur;

      //global variable
      cur.camera_no = camera_no;
      //optimus_t variables. refer by optimus.<variable_name>
      cur.rotation_angle = optimus.rotation_angle; //angle for rotation about axis
      cur.body_rotation_x = optimus.body_rotation_x; //rotate body about x axis
      cur.body_rotation_y = optimus.body_rotation_y; //rotate body about x axis
      cur.body_rotation_z = optimus.body_rotation_z; //rotate body about x axis
      cur.back_weel_slab_rotation = optimus.back_weel_slab_rotation; //rotation of back weel slab bout x axis
      cur.solder_rotation_zl = optimus.solder_rotation_zl; //left solder rotation angle about z axis
      cur.solder_rotation_yl = optimus.solder_rotation_yl; //left solder rotation angle about y axis
      cur.solder_rotation_xl = optimus.solder_rotation_xl; // left solder rotation angle about x axis
      cur.elbows_rotation_l = optimus.elbows_rotation_l; //left elbows rotarion angle about z axis
      cur.solder_rotation_zr = optimus.solder_rotation_zr; // right solder rotation angle about z axis
      cur.solder_rotation_yr = optimus.solder_rotation_yr; // right solder rotation angle about y axis
      cur.solder_rotation_xr = optimus.solder_rotation_xr; // right solder rotation angle about x axis
      cur.elbows_rotation_r = optimus.elbows_rotation_r; //right elbows rotarion angle about z axis
      cur.waist_rotation = optimus.waist_rotation; // rotation of waist about y axis
      cur.upper_body_rotation = optimus.upper_body_rotation; //rotation of upper body about x axis
      cur.lower_leg_rotation_l = optimus.lower_leg_rotation_l; //rotation of left lower leg about x axis
      cur.lower_leg_rotation_r = optimus.lower_leg_rotation_r; //rotation of right lower leg about x axis
      cur.front_weel_slab_rotation = optimus.front_weel_slab_rotation; //rotarion of slab contain weel around x axis
      cur.uper_leg_rotation_xl = optimus.uper_leg_rotation_xl; //rotation of uper left leg about x axis
      cur.uper_leg_rotation_zl = optimus.uper_leg_rotation_zl; //rotation of uper left leg about z axis
      cur.uper_leg_rotation_xr = optimus.uper_leg_rotation_xr; //rotation of uper right leg about x axis
      cur.uper_leg_rotation_zr = optimus.uper_leg_rotation_zr; //rotation of uper right leg about z axis
      cur.hood_feet_rotation_xl1 = optimus.hood_feet_rotation_xl1; //rotation of left whole feet about x axis
      cur.hood_feet_rotation_xl2 = optimus.hood_feet_rotation_xl2; //rotation of left uper feet about x axis
      cur.hood_feet_rotation_xr1 = optimus.hood_feet_rotation_xr1; //rotation of right whole feet about x axis
      cur.hood_feet_rotation_xr2 = optimus.hood_feet_rotation_xr2; //rotation of right uper feet about x axis
      cur.throat_translate_y = optimus.throat_translate_y; //translation of throat along y axis
      cur.truck_ceiling_rotation = optimus.truck_ceiling_rotation; //rotation of truck ceilig about x axis
      cur.front_glass_rotation = optimus.front_glass_rotation; //totation of fron glass bout x axis
      cur.side_gate_rotation = optimus.side_gate_rotation; //side gate rotation about x axis
      cur.weel_rotation = optimus.weel_rotation; //roatation of weel about z axis
      cur.forword_backword_movement_z = optimus.forword_backword_movement_z; // translate whole body along z axis
      cur.forword_backword_movement_x = optimus.forword_backword_movement_x; // translate whole body along x axis

      cur.vertical_movement = optimus.vertical_movement; // vertical movement of transformer(independent)

      cur.headlight_on = optimus.headlight_on;  // whether headlight on (decide which texture to load)

      //surrounding
      cur.lighting_enabled = surrounding.lighting_enabled;
      cur.light0_enabled = surrounding.light0_enabled;
      cur.light1_enabled = surrounding.light1_enabled;

      saved_keyframes.push_back(cur);
      cout << "keyfram #" << (saved_keyframes.size()-1) << endl;
      cur.write(filename.c_str());
  }

  void load_state(keyframe_t cur){ //do bounds check before calling
      //global variable
      camera_no = cur.camera_no;
      //optimus_t variables. refer by optimus.<variable_name>
      optimus.rotation_angle = cur.rotation_angle; //angle for rotation about axis
      optimus.body_rotation_x = cur.body_rotation_x; //rotate body about x axis
      optimus.body_rotation_y = cur.body_rotation_y; //rotate body about x axis
      optimus.body_rotation_z = cur.body_rotation_z; //rotate body about x axis
      optimus.back_weel_slab_rotation = cur.back_weel_slab_rotation; //rotation of back weel slab bout x axis
      optimus.solder_rotation_zl = cur.solder_rotation_zl; //left solder rotation angle about z axis
      optimus.solder_rotation_yl = cur.solder_rotation_yl; //left solder rotation angle about y axis
      optimus.solder_rotation_xl = cur.solder_rotation_xl; // left solder rotation angle about x axis
      optimus.elbows_rotation_l = cur.elbows_rotation_l; //left elbows rotarion angle about z axis
      optimus.solder_rotation_zr = cur.solder_rotation_zr; // right solder rotation angle about z axis
      optimus.solder_rotation_yr = cur.solder_rotation_yr; // right solder rotation angle about y axis
      optimus.solder_rotation_xr = cur.solder_rotation_xr; // right solder rotation angle about x axis
      optimus.elbows_rotation_r = cur.elbows_rotation_r; //right elbows rotarion angle about z axis
      optimus.waist_rotation = cur.waist_rotation; // rotation of waist about y axis
      optimus.upper_body_rotation = cur.upper_body_rotation; //rotation of upper body about x axis
      optimus.lower_leg_rotation_l = cur.lower_leg_rotation_l; //rotation of left lower leg about x axis
      optimus.lower_leg_rotation_r = cur.lower_leg_rotation_r; //rotation of right lower leg about x axis
      optimus.front_weel_slab_rotation = cur.front_weel_slab_rotation; //rotarion of slab contain weel around x axis
      optimus.uper_leg_rotation_xl = cur.uper_leg_rotation_xl; //rotation of uper left leg about x axis
      optimus.uper_leg_rotation_zl = cur.uper_leg_rotation_zl; //rotation of uper left leg about z axis
      optimus.uper_leg_rotation_xr = cur.uper_leg_rotation_xr; //rotation of uper right leg about x axis
      optimus.uper_leg_rotation_zr = cur.uper_leg_rotation_zr; //rotation of uper right leg about z axis
      optimus.hood_feet_rotation_xl1 = cur.hood_feet_rotation_xl1; //rotation of left whole feet about x axis
      optimus.hood_feet_rotation_xl2 = cur.hood_feet_rotation_xl2; //rotation of left uper feet about x axis
      optimus.hood_feet_rotation_xr1 = cur.hood_feet_rotation_xr1; //rotation of right whole feet about x axis
      optimus.hood_feet_rotation_xr2 = cur.hood_feet_rotation_xr2; //rotation of right uper feet about x axis
      optimus.throat_translate_y = cur.throat_translate_y; //translation of throat along y axis
      optimus.truck_ceiling_rotation = cur.truck_ceiling_rotation; //rotation of truck ceilig about x axis
      optimus.front_glass_rotation = cur.front_glass_rotation; //totation of fron glass bout x axis
      optimus.side_gate_rotation = cur.side_gate_rotation; //side gate rotation about x axis
      optimus.weel_rotation = cur.weel_rotation; //roatation of weel about z axis
      optimus.forword_backword_movement_z = cur.forword_backword_movement_z; // translate whole body along z axis
      optimus.forword_backword_movement_x = cur.forword_backword_movement_x; // translate whole body along x axis

      optimus.vertical_movement = cur.vertical_movement; // vertical movement of transformer(independent)

      optimus.headlight_on = cur.headlight_on;  // whether headlight on (decide which texture to load)

      //surrounding
      surrounding.lighting_enabled = cur.lighting_enabled;
      surrounding.light0_enabled = cur.light0_enabled;
      surrounding.light1_enabled = cur.light1_enabled;
  }

  void read_saved_keyframes(string filename){
      cout << filename << "read_saved_keyframes" << endl;
      saved_keyframes.clear(); //clear the vector
      ifstream myfile;
      myfile.open (filename.c_str(), ios::in);
      int index = 0;
      while(true){
          cout << "next_frame" << endl;
          keyframe_t cur;
          bool success = cur.read(myfile);
          if(!success) break;
          cout << index++ << " " << cur.camera_no <<  " " << cur.forword_backword_movement_z << " " << cur.uper_leg_rotation_xl << endl;
          saved_keyframes.push_back(cur);
      }
      cout<< "done ";
  }

  void pause(const double _period){
    double endtime = glfwGetTime() + _period;
    while(glfwWindowShouldClose(window) == 0){
      if(glfwGetTime() > endtime) break;
      glfwPollEvents();
    }
    if(glfwWindowShouldClose(window) == 1){
      glfwDestroyWindow(window);
      glfwTerminate();
      exit(0);
    }
  }

  bool animate(){
    cout << "into animate  curr_keyframe_index = " << curr_keyframe_index << "inter # = " <<interpolated_index_number << endl;
    if(curr_keyframe_index == saved_keyframes.size()-1) {
      cout << "#######################################falsifying" << endl;
      playback_mode = false; //playback is over if was on earlier
      animation_on = false; //animation has ended. Last frame has been dumped 
      load_state(saved_keyframes[saved_keyframes.size()-1]); //Load the last state
      return true;
    }

    double delta = 1.0/FPS; //seconds
    pause(delta);

    keyframe_t current = saved_keyframes[curr_keyframe_index];
    keyframe_t next = saved_keyframes[curr_keyframe_index+1];

    //interpolate by fraction  interpolated_index_number/NUM_INTER_FRAMES

    float fraction = 1.0*interpolated_index_number/NUM_INTER_FRAMES;

    keyframe_t interpolated_keyframe = interpolate(current, next, fraction);

    load_state(interpolated_keyframe);

    interpolated_index_number++;
    
    if(interpolated_index_number == NUM_INTER_FRAMES){
      //slide interpolation window
      curr_keyframe_index++;
      interpolated_index_number = 0;
    }

    return true;
  }

  void dump(){
    char imgname[100];
    sprintf(imgname, "%s/%s_%d.ppm", output_folder.c_str(), image_file_prefix.c_str(), output_frame_number);
    savePPM(0,0,win_width, win_height, imgname);
    output_frame_number++;
  }

  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_F12 && action == GLFW_PRESS){ //f12 change mode
      MODE = ((MODE+1) % 3); //starts from 1 to NUM_MODES
        
      cout << "mode changed " << MODE << " ";
      if(MODE == 0) {
        animation_on = false;
        cout << "RECORDING MODE : use = button to record current keyframe state" << endl;
        kf_file = "kf.txt";
      }
      else if(MODE == 1) {
        animation_on = false;
        cout << "TESTING SAVED KEY-FRAMES MODE: use < > keys to review key-frames" << endl;
      }
      else if(MODE == 2) {
        animation_on = false;
        cout << "PLAYBACK SAVED KEY-FRAMES MODE : use > to specify input textfile name and animate !!" << endl;
      }

      if(MODE == 1) curr_keyframe_index = saved_keyframes.size()-1; //set curr_keyframe_index to end
    }
    //!Close the window if the ESC key was pressed
    else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    if(MODE == 0){ //recording
        if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT)) //f1 without shift
          save_state(kf_file);
        else if (key == GLFW_KEY_F1 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT)) //f1 without shift
          surrounding.lighting_enabled = true;
        else if (key == GLFW_KEY_F1 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)) //shift+F1
          surrounding.lighting_enabled = false;
        else if (key == GLFW_KEY_F2 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT)) //f2 without shift
          surrounding.light0_enabled = true;
        else if (key == GLFW_KEY_F2 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)) //shift+F2
          surrounding.light0_enabled = false;
        else if (key == GLFW_KEY_F3 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT)) //f3 without shift
          surrounding.light1_enabled = true;
        else if (key == GLFW_KEY_F3 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)) //shift+F3
          surrounding.light1_enabled = false;
        else if (key == GLFW_KEY_F4 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT)){ //f4 without shift
          optimus.headlight_on = true;
        }
        else if (key == GLFW_KEY_F4 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT)){ //shift+f4
          optimus.headlight_on = false;
        }
        else if (key == GLFW_KEY_F8 && action == GLFW_PRESS) //f8
          camera_no = 0;
        else if (key == GLFW_KEY_F9 && action == GLFW_PRESS) //f9
          camera_no = 1;
        else if (key == GLFW_KEY_F10 && action == GLFW_PRESS) //f10
          camera_no = (camera_no+1)%NUM_CAMERAS;
        //whole body rotation
        else 
          optimus.optimus_key_callback(key, scancode, action, mods);
    }
    else if(MODE == 1){ //testing
        if (key == GLFW_KEY_PERIOD && action == GLFW_PRESS){
            if(curr_keyframe_index >= saved_keyframes.size()-1){
                cout << "next_frame() : Already pointing to last saved keyframe " << curr_keyframe_index << " [size : " << saved_keyframes.size() << "]" <<endl;
            }
            else{
                curr_keyframe_index += 1;
                cout << "loading keyframe : " << curr_keyframe_index << " [size : "  << saved_keyframes.size() << "]" << endl;
                keyframe_t kf = saved_keyframes[curr_keyframe_index];
                load_state(kf);
            }
        }
        else if (key == GLFW_KEY_COMMA && action == GLFW_PRESS){
            if(curr_keyframe_index <= 0){
                cout << "previous_frame() : Already pointing to begining saved keyframe " << curr_keyframe_index << " [size : " << saved_keyframes.size() << "]" <<endl;
            }
            else{
                curr_keyframe_index -= 1;
                cout << "loading keyframe : " << curr_keyframe_index << " [size : "  << saved_keyframes.size() << "]" << endl;
                keyframe_t kf = saved_keyframes[curr_keyframe_index];
                load_state(kf);
            }
        }
    }
    else if(MODE == 2){ //animation mode
        if (key == GLFW_KEY_PERIOD && action == GLFW_PRESS){
          cout << "Default Settings :: keyframe file = 'kf.txt', 30 FPS, 15 inter frames, \n output folder = 'output, prefix = 'anim', starting frame# = 0\n";
          cout << "Use default enter Y or N : ";
          string option;
          cin >> option;
          if(option == "N"){
            cout << "enter source keyframe file path :";
            cin >> kf_file;
            cout << "enter required FPS :";
            cin >> FPS;
            cout << "enter number of intermediate frames(b/w keyframes) :";
            cin >> NUM_INTER_FRAMES;
            cout << "Enter output folder :";
            cin >> output_folder;
            cout << "Enter image <prefix> : images will be saved as <prefix>_<frame#>.ppm : ";
            cin >> image_file_prefix;
            cout << "Enter starting output frame number : ";
            cin >> output_frame_number;
          }
          else{
            kf_file = "kf.txt";
            FPS = 30;
            NUM_INTER_FRAMES = 15;
            output_folder = "animate";
            image_file_prefix = "anim";
            output_frame_number = 0;
          }

          string command("mkdir -p ");
          system((command + output_folder).c_str()); //create output folder if not exists

          curr_keyframe_index = 0; //reset
          interpolated_index_number = 0;

          animation_on = true; //animation is on
          playback_mode = false; //default unless replayed after dumping the frames

          read_saved_keyframes(kf_file);
          cout << "succesfully loaded into saved_keyframes vector. Now can resume" << endl;
        }
        else if (key == GLFW_KEY_R && action == GLFW_PRESS){
          cout << "Replay" << endl;
          playback_mode = true;
          animation_on = true;
          curr_keyframe_index = 0;
          interpolated_index_number = 0;
        }
    }
  }
};  
  


