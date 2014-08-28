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


#include "render_drawing.hpp"


void triline(turtle_t &turt, double length)
{
   if (length <= 0.1)
   {
      turt.forward(length);
   }
   else
   {
     double newlength = length/3.0;
     triline(turt, newlength);
     turt.turn_left(60);
     triline(turt, newlength);
     turt.turn_right(120);
     triline(turt, newlength);
     turt.turn_left(60);
     triline(turt, newlength);
   }
}
//Sierpinski triangle helpher ; just scatch recursive call 

void sierpinski_helper(turtle_t &turt, double length)
{
  if(length<=0.05) //simply draw a triangle of 'length' side and return back to same pos,dir
  {
    turt.forward(length);
    turt.turn_left(120);
    turt.forward(length);
    turt.turn_left(120);
    turt.forward(length);
    turt.turn_left(120);
  }
  else
  { //recursively call 3 times and move back to top vertex with same orientation
    double newlength = length/2.0;
    sierpinski_helper(turt, newlength);
    turt.forward_move(newlength);
    sierpinski_helper(turt, newlength);
    turt.turn_left(120);
    turt.forward_move(newlength);
    turt.turn_right(120);
    sierpinski_helper(turt, newlength);

    //move back to top vertex
    turt.turn_right(120);
    turt.forward_move(newlength);
    turt.turn_left(120);
  }
}

void sierpinski(turtle_t &turt, double x){
  turt.reset();
  turt.clear();
  turt.turn_left(90);
  turt.forward_move(0.7);
  turt.turn_left(150);

  sierpinski_helper(turt, x);
}


//Drawing a Koch Snowflake
void koch(turtle_t &turt, double x)
{
   turt.reset();
   turt.clear();
   turt.set_pos(-0.3, 0.5);
   turt.turn_right(30);

   for (int i = 0; i<3; i++)
     {
       triline(turt, x);
       turt.turn_right(120);
     }
}

void render_drawing(turtle_t &turt)
{
  // koch(turt, 1.0);
  sierpinski(turt, 1.2);
}
