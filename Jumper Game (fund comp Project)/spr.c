// spr.c
// gfx_text() can only display strings
// to display a number, you can 'build' a string with sprintf
// this example shows a counter that is continuously updated
//
#include <stdio.h>

#include "gfx.h"

int main()
{
  int wd = 400, ht = 300;

  gfx_open(wd, ht, "My window"); 

  char str[15];  
  int n = 100;

  while(1) {
    gfx_clear();

    sprintf(str,"counter: %d", n);
    gfx_text(250, 100, str);

    gfx_flush();  

    n++;

    if(gfx_event_waiting())
      if(gfx_wait() == 'q') 
        break;

    usleep(100000);
  }

  return 0;
}

