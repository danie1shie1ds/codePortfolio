// grav.c
// applying gravity, and bouncing off of sides and bottom
#include <unistd.h>
#include "gfx.h"

int main()
{
  int wd = 400, ht = 500;        
  float xc = 50, yc = 50;    // ball's center's initial position
  int rad = 20;  
  float vx = 1.3, vy = 0;  // velocity vector
  float g = .06;             // gravity

  char c = 0;                    
  int pausetime = 5000;          

  gfx_open(wd, ht, "My window");
	gfx_clear_color(50, 0, 50);

  while (c != 'q') {              
    gfx_clear();                 

    gfx_circle(xc, yc, rad);     
    gfx_flush();

    // update location based on velocity vector
    xc += vx;
    yc += vy; 

    // update vertical velocity based on acceleration
    vy += g;

    if (xc > wd-rad || xc < rad)
      vx = -vx;
    if (yc > ht - rad){   // no need here to check upper edge
			//vy = -.9*vy; 
			yc = ht - rad;
			vy = -.9*vy;
		}

    if(gfx_event_waiting()) {    
      c = gfx_wait();            
    }

    usleep(pausetime); 
  }

  return 0;
}

// notes:
//  the above does not check for getting stuck at an edge
//  since gravity is being applied, and is positive (downwards),
//     there is no need to check with collision with the upper edge
//  if you want to implement floor attenuation, or friction, or bounciness,
//     use a  multiplier float variable in the vy statement

