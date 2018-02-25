#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if(points->cols == points->lastcol){
    grow_matrix(points, points->lastcol * 2);
    printf("Matrix is full. Growing matrix.\n");
  }
  printf("Adding (%0.2f, %0.2f, %0.2f)\n", x, y, z);
  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;
  points->lastcol += 1;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  for(int col = 0; col + 1 < points->lastcol; col += 2){
    draw_line(points->m[0][col], points->m[1][col], points->m[0][col+1], points->m[1][col+1], s, c);
  }
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  printf("Drawing line from (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
  int octant = 0;

  if(x0 > x1){
    int temp = x0;
    x0 = x1;
    x1 = temp;
    temp = y0;
    y0 = y1;
    y1 = temp;
  }
  
  int A = y1 - y0; int B = x0 - x1;
  //printf("A: %d B: %d\n", A, B);
  int x = x0; int y = y0; int d;

  if( A > 0){ // top
    if( A + B > 0 ){ octant = 2; } //means slope is > 1
    else { octant = 1; }
  }
  else{//assuming plot left to right, meaning negative slope is negative change in y
    if ( A < B ){ octant = 7; } //means slope is < -1
    else { octant = 8; }
  }

  //printf("slope: %f\n", -1.0 * A / B);
  //printf("octant: %d\n", octant);
  
  switch (octant)
    {
    case 1:
      d = 2 * A + B;
      while (x < x1){
	plot(s, c, x, y);
	x ++;
	if (d > 0){
	  y ++;
	  d += 2 * B;
	}
	d += 2 * A;
      } 
      break;
    case 2:
      d = A + 2 * B;
      while (x < x1 || y < y1){ //horizontal case
	plot(s, c, x, y);
	y ++;
	if (d < 0){
	  x ++;
	  d += 2 * A;
	}
	d += 2 * B;
      } 
      break;
    case 7:
      d = A - 2 * B;
      while (x < x1){
	plot(s, c, x, y);
	y --;
	if (d > 0){
	  x ++;
	  d += 2 * A;
	}
	d -= 2 * B;
      }
      break;
    case 8:
      d = 2 * A - B;
      while (x < x1){
	plot(s, c, x, y);
	x ++;
	if (d < 0){
	  y --;
	  d -= 2 * B;
	}
	d += 2 * A;
      } 
      break;
    }

}
