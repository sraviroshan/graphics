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


#include <cmath>
#include <iostream>
#include <cstdlib>
#include <GL/glew.h>


#include "turtle.hpp"
#define PI 3.14159265

void turtle_t::reset(void) 
{
  pos.x = 0;
  pos.y = 0;
  dir = 0;
}

void turtle_t::clear(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void turtle_t::set_pos(const vertex_t _pos)
{
  pos.x = _pos.x;
  pos.y = _pos.y; 
}

void turtle_t::set_pos(const double _x, const double _y)
{
  pos.x = _x;
  pos.y = _y;
}

void turtle_t::set_dir(const double _dir)
{
  dir = _dir;
}

void turtle_t::set_col(const color_t _col)
{
  col.r = _col.r;
  col.g = _col.g;
  col.b = _col.b;
  glColor4f(col.r, col.g, col.b, 1.0); 
}

void turtle_t::set_col(const double _r, const double _g, const double _b)
{
  col.r = _r;
  col.g = _g;
  col.b = _b;
  glColor4f(col.r, col.g, col.b, 1.0);
}

void turtle_t::set_bgcol(const double _r, const double _g, const double _b)
{ 
  glClearColor(_r, _g, _b, 1.0);
}

void turtle_t::scale(const double _s)
{ 
  scaling_factor = _s;
}

void turtle_t::turn_left(const double _angle)    
{
  set_dir(dir+ _angle);
}

void turtle_t::turn_right(const double _angle)
{
  set_dir(dir- _angle);
}

void turtle_t::forward(const double _dist)  
{
  glBegin(GL_LINES);
  glVertex3f(pos.x,  pos.y,  0.0f);
  
  double x1 = pos.x + _dist * cos(dir * PI /180) * 1/scaling_factor;
  double y1 = pos.y + _dist * sin(dir * PI /180) * 1/scaling_factor;

  glVertex3f(x1, y1,  0.0f);
  glEnd();

  set_pos(x1, y1);
}

void turtle_t::back(const double _dist)   
{
  forward(- _dist);
}

void turtle_t::forward_move(const double _dist)
{
  double x1 = pos.x + _dist * cos(dir * PI /180) * 1/scaling_factor;
  double y1 = pos.y + _dist * sin(dir * PI /180) * 1/scaling_factor;
  
  set_pos(x1, y1);  
}

void turtle_t::backward_move(const double _dist)
{
  forward_move(- _dist);
}

void turtle_t::pause(const double _period)
{
  glfwSwapBuffers(window);
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

void turtle_t::repeat(const unsigned int &_n, const turtle_com_list_t &_replist)
{
  for(int i=0; i< _n;i++)
  { 
    turtle_com_list_t::const_iterator liter;
    turtle_com_t *com;
    for( liter = _replist.begin(); liter!=_replist.end(); liter++)
    {
      com = *liter;
      exec(com);
    }
  }
}

void turtle_t::exec(turtle_com_t *com)
{
  if (com->cname==F)
    {
      turtle_fwd_t* fcom = dynamic_cast<turtle_fwd_t*>(com);
      if (fcom) forward(fcom->dist);
    }
  else if (com->cname==B)
    {
      turtle_bck_t* bcom = dynamic_cast<turtle_bck_t*>(com);
      if (bcom) back(bcom->dist);
    }
  else if (com->cname==L)
    {
      turtle_lft_t* lcom = dynamic_cast<turtle_lft_t*>(com);
      if (lcom) turn_left(lcom->angl);
    }
  else if (com->cname==R)
    {
      turtle_rht_t* rcom = dynamic_cast<turtle_rht_t*>(com);
      if (rcom) turn_right(rcom->angl);
    }
  else if (com->cname==MF)
    {
      turtle_mfwd_t* mfcom = dynamic_cast<turtle_mfwd_t*>(com);
      if (mfcom) forward_move(mfcom->dist);
    }
  else if (com->cname==MB)
    {
      turtle_mbck_t* mbcom = dynamic_cast<turtle_mbck_t*>(com);
      if (mbcom) backward_move(mbcom->dist);
    }
  else if (com->cname==CLS)
    {
      turtle_cls_t* clscom = dynamic_cast<turtle_cls_t*>(com);
      if (clscom) clear();
    }
  else if (com->cname==RESET)
    {
      turtle_rst_t* rstcom = dynamic_cast<turtle_rst_t*>(com);
      if (rstcom) reset();
    }
  else if (com->cname==COL)
    {
      turtle_col_t* colcom = dynamic_cast<turtle_col_t*>(com);
      if (colcom) set_col(colcom->r, colcom->g, colcom->b);
    }
  else if (com->cname==BGCOL)
    {
      turtle_bgcol_t* bgcolcom = dynamic_cast<turtle_bgcol_t*>(com);
      if (bgcolcom) set_bgcol(bgcolcom->r, bgcolcom->g, bgcolcom->b);
    }
  else if (com->cname==SCALE)
    {
      turtle_scale_t* scalecom = dynamic_cast<turtle_scale_t*>(com);
      if (scalecom) scale(scalecom->s);
    }
  else if (com->cname==PAUSE)
    {
      turtle_pause_t* pausecom = dynamic_cast<turtle_pause_t*>(com);
      if (pausecom) pause(pausecom->period);
    }
  else if (com->cname==REPEAT)
    {
      turtle_rep_t *repcom = dynamic_cast<turtle_rep_t*>(com);

      if (repcom)
	{
	  unsigned int times = repcom->times;
	  turtle_com_list_t sublist = repcom->replist;
	  repeat(times, sublist);
	}
     }
  else if ((com->cname==ENDREP) || (com->cname==END) || (com->cname==BEGIN)) 
    {
      //These commands are place holders and used for program structure
      //But no execution is necessary - generate a NoOP
      ;
    }
  else
    {
      std::cerr<<"Unknown Command: Ignoring"<<std::endl;
      exit(-1);
    }
}

