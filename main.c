#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;
  struct matrix *a;
  struct matrix *edges;
  clear_screen(s);
  a = new_matrix(4, 4);
  printf("Created new 4 x 1 matrix\n");
  edges = new_matrix(4, 1);
  printf("Testing add_point\n");
  add_point(edges, 1, 2, 3);
  add_point(edges, 500, 500, 7);
  printf("--------------------\n");
  printf("Testing add_edge\n");
  add_edge(edges, 0, 0, 3, 500, 60, 7);
  print_matrix(edges);
  
  printf("--------------------\n");
  printf("Testing identity matrix\n");
  ident(a);
  print_matrix(a);
  a->m[0][3] = 2;
  a->m[1][3] = 2;
  a->m[2][3] = 2;
  printf("Changed last col to test matrix multi\n");
  print_matrix(a);
  
  printf("--------------------\n");
  printf("Testing multiplying matrices");
  matrix_mult(a, edges);
  print_matrix(edges);
  
  draw_lines(edges, s, c);
  display(s);
  free_matrix(a);
  free_matrix(edges);
}
