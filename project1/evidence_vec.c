#include "raytracer.h"


int main()
{
  //test vec_new
  vec *v1 = vec_new(-1.0, -1.0, -1.0);
  vec *v2 = vec_new(10.0, 10.0, 10.0);
  vec *v3 = vec_new(3.0, 4.0, 5.0);
  vec_print(v1);
  vec_print(v2);
  vec_print(v3);
  //test vec_dup
  vec *v4 =  vec_dup(v3);
  vec_print(v4);
  vec_free(v3);
  vec_print(v4);
  v3 = vec_new(3.0, 4.0, 5.0);
  //test vec_add
  vec *v5 = vec_add(v1, v2);
  vec *v6 = vec_add(v1, v3);
  vec_print(v5);
  vec_print(v6);
  //test vec_neg
  vec *v7 = vec_neg(v1);
  vec *v8 = vec_neg(v3);
  vec_print(v7);
  vec_print(v8);
  //test vec_scale
  vec *v9 = vec_scale(10, v1);
  vec *v10 = vec_scale(-1, v1);
  vec_print(v9);
  vec_print(v10);
  //test vec_dot
  printf("%lf\n", vec_dot(v1, v2));
  printf("%lf\n", vec_dot(v2, v3));
  printf("%lf\n", vec_dot(v3, v4));

  //test vec_mag
  printf("%lf\n", vec_mag(v1));
  printf("%lf\n", vec_mag(v2));
  printf("%lf\n", vec_mag(v3));
  //test vec_norm
  printf("%lf\n", vec_mag(vec_norm(v1)));
  printf("%lf\n", vec_mag(vec_norm(v2)));
  printf("%lf\n", vec_mag(vec_norm(v3)));
  //test vec_tos
  printf("%s\n", vec_tos(v1));
  printf("%s\n", vec_tos(v2));
  printf("%s\n", vec_tos(v3));

  printf("%s\n", "VALGRIND TESTING");
  vec_free(v1);
  vec_free(v2);
  vec_free(v3);
  vec_free(v4);
  vec_free(v5);
  vec_free(v6);
  vec_free(v7);
  vec_free(v8);
  vec_free(v9);
  vec_free(v10);
}
