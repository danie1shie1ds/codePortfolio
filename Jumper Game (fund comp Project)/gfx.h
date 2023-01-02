// A simple graphics library for CSE 20311 
// Originally created by Prof. Doug Thain
// Modified and augmented by Prof. Ramzi Bualuan
// Last edit: Nov 14 2021

#ifndef GFX_H
#define GFX_H

#include <X11/Xlib.h>

// Open a new graphics window. 
void gfx_open( int width, int height, const char *title );

// Flush all previous output to the window. 
void gfx_flush();

// Change the current drawing color. 
void gfx_color( int red, int green, int blue );

// Clear the graphics window to the background color. 
void gfx_clear();

// Change the current background color. 
void gfx_clear_color( int red, int green, int blue );

// Check to see if an event is waiting. 
int gfx_event_waiting();

// Wait for the user to press a key or mouse button. 
char gfx_wait();

// Return the X and Y coordinates of the last event. 
int gfx_xpos();
int gfx_ypos();

// Return the X and Y dimensions of the screen (monitor). 
int gfx_xsize();
int gfx_ysize();

// Draw a point at (x,y) 
void gfx_point( int x, int y );

// Draw a line from (x1,y1) to (x2,y2) 
void gfx_line( int x1, int y1, int x2, int y2 );

// Draw a circle centered at (xc,yc) with radius r 
void gfx_circle( int xc, int yc, int r );

// Display a string at (x,y) 
void gfx_text( int x, int y , const char *text );

#endif

