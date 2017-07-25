#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// vector struct
typedef struct { double x, y, z; } v3;

v3 v_add(v3 a, v3 b) { return (v3) { a.x + b.x, a.y + b.y, a.z + b.z }; }
v3 v_sub(v3 a, v3 b) { return (v3) { a.x - b.x, a.y - b.y, a.z - b.z }; }
v3 v_mul(v3 a, double b) { return (v3) { a.x * b, a.y * b, a.z * b }; }
double v_dot(v3 a, v3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
double v_sqr(v3 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
double v_len(v3 a) { return sqrt(v_sqr(a)); }
v3 v_crs(v3 a, v3 b) { 
  return (v3) { a.y * b.z - a.z * b.y, 
                a.z * b.x - a.x * b.z, 
                a.x * b.y - a.y * b.x 
  }; 
}
v3 v_nor(v3 a) { return v_mul(a, 1.0 / v_len(a)); }

void printv(v3 v) { printf("%f, %f, %f", v.x, v.y, v.z); }