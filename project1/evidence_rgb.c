#include "raytracer.h"
int main()
{
  //test rgb_new
  rgb *c1 = rgb_new(1.0, 1.0, 1.0);
  rgb *c2 = rgb_new(0.0, 0.0, 0.0);
  rgb *c3 = rgb_new(0.5, 0.5, 0.5);
  rgb_print(c1);
  rgb_print(c2);
  rgb_print(c3);
  rgb_print_bytes(c1);
  rgb_print_bytes(c2);
  rgb_print_bytes(c3);
  //test rgb_dup
  rgb *c4 = rgb_dup(c1);
  rgb_free(c1);
  rgb_print(c4);
  rgb_print_bytes(c4);
  c1 = rgb_dup(c4);
  //test rgb_module
  rgb *c5 = rgb_modulate(c1, c3);
  rgb *c6 = rgb_modulate(c2, c3);
  rgb_print(c5);
  rgb_print(c6);
  rgb_print_bytes(c5);
  rgb_print_bytes(c6);
  //test rgb_scale
  rgb *c7 = rgb_scale(0.7, c1);
  rgb *c8 = rgb_scale(0.25, c3);
  rgb_print(c7);
  rgb_print(c8);
  rgb_print_bytes(c7);
  rgb_print_bytes(c8);
  //test rgb_add
  printf("%s\n", "testing rgb_add");
  rgb *c9 = rgb_add(c1, c2);
  rgb *c10 = rgb_add(c3, c8);
  rgb *c11 = rgb_add(c1, c3);
  rgb *c12 = rgb_add(c8, c7);
  rgb_print(c9);
  rgb_print(c10);
  rgb_print(c11);
  rgb_print(c12);
  rgb_print_bytes(c9);
  rgb_print_bytes(c10);
  rgb_print_bytes(c11);
  rgb_print_bytes(c12);
  //test rgb_tos
  printf("%s", rgb_tos(c1));
  printf("%s", rgb_tos(c2));
  printf("%s", rgb_tos(c3));
  //test rgb_printbytes
  rgb_print_bytes(rgb_new(1.0, 1.0, 0));

  printf("%s\n", "VALGRIND TESTING");
  rgb_free(c1);
  rgb_free(c2);
  rgb_free(c3);
  rgb_free(c4);
  rgb_free(c5);
  rgb_free(c6);
  rgb_free(c7);
  rgb_free(c8);
  rgb_free(c9);
  rgb_free(c10);
}
