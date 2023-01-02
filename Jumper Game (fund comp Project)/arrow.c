// arrows.c
// moving an object using arrow keys
// ( note: moving 1 pixel at a time is very slow;
//   using an increment variable is better.
//   So change lines below to, for instance:
//     if (c == 'R') yc -= delta;
//   where delta is a number indicating how far the object
//     will travel for each hit of the arrow key
// )

#include "gfx.h"
#include <stdlib.h>

int main()
{
  gfx_open(600, 400, "example");

  float xc = 100, yc = 200;

  while(1) {
    gfx_clear();
    char c = ' ';

    gfx_circle(xc, yc, 25); 

    gfx_flush();

    if(gfx_event_waiting())
      c = gfx_wait();

    if (c == 'R') yc--;   // up arrow
    if (c == 'T') yc++;   // down arrow
    if (c == 'Q') xc--;   // left arrow
    if (c == 'S') xc++;   // right arrow
    
    if (c == 'q') break;

    usleep(1000);

  }

  return 0; 
}

